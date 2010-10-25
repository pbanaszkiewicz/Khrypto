/*  This file is part of Khrypto.

    Khrypto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Khrypto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Khrypto.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ciphers.h"
#include "rsa.h"
#include "rsa_files.h"
#include <QFileDialog>
#include <QFile>


// TODO:
// - update translation
// - make clever status_message acting due to error or success
// - make threads


/* MainWindow::MainWindow(QWidget)
 * constructor of the Khrypto's main window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    // settings
    // hide redundant objects -> keys loading etc.
    rsa_pub.length = 0;
    rsa_priv.length = 0;

    // enable what needed
    ui->cbAction->setEnabled(true);
    ui->tInput->setEnabled(true);
    ui->tOutput->setEnabled(true);
    ui->sbKey->setEnabled(true);
    ui->tOutput->setReadOnly(true);
    ui->gbRSA->setDisabled(true);
    ui->gbRSA->hide();
    ui->btnSave->setDisabled(true);

    // slots
    connect( ui->btnCode, SIGNAL(clicked()), this, SLOT(code()) );
    connect( ui->cbMethod,SIGNAL(currentIndexChanged(int)), this, SLOT(method_changed(int)) );
    connect( ui->cbAction,SIGNAL(currentIndexChanged(int)), this, SLOT(action_changed(int)) );
    connect( ui->tOutput, SIGNAL(textChanged()), this, SLOT(output_textbox_changed()) );
    connect( ui->btnLoad, SIGNAL(clicked()), this, SLOT(load_file()) );
    connect( ui->btnSave, SIGNAL(clicked()), this, SLOT(save_file()) );
    connect( ui->btnGenerateRSAKey, SIGNAL(clicked()), this, SLOT(generate_RSA_key()) );
    connect( ui->btnRSALoad1,SIGNAL(clicked()),this,SLOT(load_rsa_pub()) );
    connect( ui->btnRSASave1,SIGNAL(clicked()),this,SLOT(save_rsa_pub()) );
    connect( ui->btnRSALoad2,SIGNAL(clicked()),this,SLOT(load_rsa_priv()) );
    connect( ui->btnRSASave2,SIGNAL(clicked()),this,SLOT(save_rsa_priv()) );
    connect( ui->actionGenerate_random_key,SIGNAL(triggered()),this,SLOT(generate_random_key()) );

    
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    status_message(tr("Welcome to Khrypto."), 4);
}


/* void MainWindow::code()
 * @btnCode.clicked()
 * generates cipher or turns cipher into primary form
 */
void MainWindow::code() {
    QString result;

    if (ui->tInput->toPlainText().length()==0) {
        status_message(tr("You should enter any text to the input box"));
        return;
    }

    if (ui->cbAction->currentIndex()==0) {
        //encrypting
        status_message(tr("Encrypting, please wait"));

        switch (ui->cbMethod->currentIndex()) {
        case 0: //caesar cipher
            result = caesar(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 1: //płot
            result = fence(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 2: //XOR
            result = XOR(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 3: //RSA
            {
                if (rsa_pub.length == 0) {
                    status_message(tr("You must first specify the public key"));
                    break;
                }

                list<string> cipher;

                string message = ui->tInput->toPlainText().toLocal8Bit().constData();
                RSA_encrypt(message, cipher, rsa_pub);

                list<string>::iterator iter;
                QTextStream t(&result);
                for (iter=cipher.begin(); iter!=cipher.end(); iter++) {
                    t << (*iter).c_str() << "\n";
                }
                break;
            }
        case 4: //Huffman
            result = "";
            break;
        }
    } else {
        //decrypting
        status_message(tr("Decrypting, please wait"));

        switch (ui->cbMethod->currentIndex()) {
        case 0: //caesar cipher
            result = caesar_undo(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 1: //płot
            result = fence_undo(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 2: //XOR
            result = XOR(ui->tInput->toPlainText(), ui->sbKey->value());
            break;
        case 3: //RSA
            {
                if (rsa_priv.length == 0) {
                    status_message(tr("You must first specify the private key"));
                    break;
                }

                QString text = ui->tInput->toPlainText();
                QStringList L = text.split('\n', QString::SkipEmptyParts);
                list<string> cipher;
                for (int i=0; i<L.size(); i++) {
                    cipher.push_back( string(L.at(i).toLocal8Bit().constData()) );
                }

                string message;
                RSA_decrypt(message, cipher, rsa_priv);
                result = message.c_str();
                break;
            }
        case 4: //Huffman
            result = "";
            break;
        }
    }
    ui->tOutput->setPlainText(result);

    clear_status_message();
}


/* void MainWindow::method_changed(int)
 * @cbMethod.currentIndexChanged(int)
 * (en|dis)ables inputs or boxes according to the method used (RSA, Caezar etc)
 */
void MainWindow::method_changed(int index) {
    ui->cbAction->setEnabled(true);
    ui->sbKey->setEnabled(true);
    ui->actionGenerate_random_key->setEnabled(true);
    ui->gbRSA->setDisabled(true);
    ui->gbRSA->hide();
    if (index==3) { //RSA
        ui->sbKey->setDisabled(true);
        ui->actionGenerate_random_key->setDisabled(true);
        ui->gbRSA->setEnabled(true);
        ui->gbRSA->show();
    }
}


/* void MainWindow::action_changed(int)
 * @cbAction.currentIndexChanged(int)
 * changes text on the Encrypt/Decrypt button
 */
void MainWindow::action_changed(int index) {
    switch (index) {
    case 0:
        ui->btnCode->setText(tr("Encrypt"));
        break;
    case 1:
        ui->btnCode->setText(tr("Decrypt"));
        break;
    }
}


/* void MainWindow::output_textbox_changed()
 * @tOutput.textChanged()
 * enables or disables the save button
 */
void MainWindow::output_textbox_changed() {
    if (ui->tOutput->toPlainText().size() != 0) {
        ui->btnSave->setEnabled(true);
    } else {
        ui->btnSave->setDisabled(true);
    }
}


/* void MainWindow::load_file()
 * @btnLoad.clicked()
 * opens dialog to pick the file which will be loaded as input text
 */
void MainWindow::load_file() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        QFile file( file_names[0] );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            status_message(tr("Error: cannot open the file ") + file_names[0]);
            return;
        }

        ui->tInput->clear();
        ui->tInput->setPlainText( QString( file.readAll() ) );
        status_message(tr("Loaded file ") + file_names[0]);

        file.close();
    }
}


/* void MainWindow::save_file()
 * @btnSave.clicked()
 * opens dialog to save the file with output contents
 */
void MainWindow::save_file() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        QFile file( file_names[0] );
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            status_message(tr("Error: cannot open the file ") + file_names[0]);
            return;
        }

        QByteArray ar;
        ar.append( ui->tOutput->toPlainText() );
        file.write(ar);

        file.close();
        status_message(tr("Saved to file ") + file_names[0]);
    }
}


/* void MainWindow::status_message(QString)
 * shows message on the status bar
 */
void MainWindow::status_message(QString text) {
    status_message( text, 10000);
}


/* void MainWindow::status_message(QString, int)
 * shows message on the status bar but for specified time
 */
void MainWindow::status_message(QString text, int time) {
    if (ui->statusBar->currentMessage().size() != 0) ui->statusBar->clearMessage();

    ui->statusBar->showMessage( text, time );
}


/* void MainWindow::clear_status_message()
 * clears message on the status bar
 */
void MainWindow::clear_status_message() {
    ui->statusBar->clearMessage();
}


/* void MainWindow::present_rsa_public()
 * shows RSA Public Key in specified format in the textbox
 */
void MainWindow::present_rsa_public() {
    //  length || n  || e
    QString pub_s;
    QTextStream pub(&pub_s);

    pub << rsa_pub.length
        << "\n\n" << mpz_get_str(NULL, 16, rsa_pub.n)
        << "\n\n" << mpz_get_str(NULL, 10, rsa_pub.e);

    ui->eRSAPublic->clear();
    ui->eRSAPublic->setPlainText(pub_s);
}


/* void MainWindow::present_rsa_private()
 * shows RSA Private Key in specified format in the textbox
 */
void MainWindow::present_rsa_private() {
    //  length || p  || q  || dP || dQ || qInv
    QString priv_s;
    QTextStream priv(&priv_s);

    priv << rsa_priv.length
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.p)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.q)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.dP)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.dQ)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.qInv);

    ui->eRSAPrivate->clear();
    ui->eRSAPrivate->setPlainText(priv_s);
}


/* void MainWindow::generate_RSA_key()
 * @btnGenerateRSAKey.clicked()
 * this function generates specified RSA keys and presents them
 */
void MainWindow::generate_RSA_key() {
    status_message(tr("Generating RSA keys, please wait"));

    int length;
    switch (ui->cbKeyLenghts->currentIndex()) {
        case 1:
            length = 1024; break;
        case 2:
            length = 2048; break;
        case 3:
            length = 4096; break;
        case 4:
            length = 8192; break;
        default:
            length = 512; break;
    }

    key_generation(length, rsa_priv, rsa_pub);

    present_rsa_public();
    present_rsa_private();

    clear_status_message();
}


/* void MainWindow::load_rsa_pub()
 * @btnRSALoad1.clicked()
 * opens dialog to pick the file with RSA Public Key
 */
void MainWindow::load_rsa_pub() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        try {
            rsa_pub = load_public_key( file_names[0] );

            present_rsa_public();

            status_message(tr("Key loaded from file ") + file_names[0]);

        } catch (IOErrorException const & e) {
            status_message(tr("Cannot load key from file ") + file_names[0]);
        }
    }
}


/* void MainWindow::save_rsa_pub()
 * @btnRSASave1.clicked()
 * opens dialog to save the file with RSA Public Key
 */
void MainWindow::save_rsa_pub() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        try {
            save_public_key(rsa_pub, file_names[0]);
            status_message(tr("Key saved to file ") + file_names[0]);

        } catch (IOErrorException const & e) {
            status_message(tr("Cannot save key to file ") + file_names[0]);
        }

    }
}


/* void MainWindow::load_rsa_priv()
 * @btnRSALoad2.clicked()
 * opens dialog to pick the file with RSA Private Key
 */
void MainWindow::load_rsa_priv() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        try {
            rsa_priv = load_private_key( file_names[0] );

            present_rsa_private();

            status_message(tr("Key loaded from file ") + file_names[0]);

        } catch (IOErrorException const & e) {
            status_message(tr("Cannot load key from file ") + file_names[0]);
        }
    }
}


/* void MainWindow::save_rsa_priv()
 * @btnRSASave2.clicked()
 * opens dialog to save the file with RSA Private Key
 */
void MainWindow::save_rsa_priv() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        try {
            save_private_key(rsa_priv, file_names[0]);
            status_message(tr("Key saved to file ") + file_names[0]);
        } catch (IOErrorException const & e) {
            status_message(tr("Cannot save key to file ") + file_names[0]);
        }
    }
}


/* void MainWindow::generate_random_key()
 * @actionGenerate_random_key.triggered()
 * generates any random key
 */
void MainWindow::generate_random_key() {
    ui->sbKey->setValue( rand() % ui->sbKey->maximum() );
}


/* MainWindow::~MainWindow()
 * Khrypto's main window destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
