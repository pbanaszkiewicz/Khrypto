#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ciphers.h"
#include "rsa.h"
#include "rsa_files.h"
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    // settings
    // hide redundant objects -> keys loading etc.

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

    
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    status_message(tr("Welcome to Khrypto."), 4);
}

void MainWindow::code() {
    QString result;

    //if (ui->tInput->blockCount()==1)
    //    return;

    if (ui->cbAction->currentIndex()==0) {
        //encrypting
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
}

void MainWindow::method_changed(int index) {
    // TODO: change this to switch statement
    ui->cbAction->setEnabled(true);
    ui->sbKey->setEnabled(true);
    ui->gbRSA->setDisabled(true);
    ui->gbRSA->hide();
    if (index==3) {
        ui->sbKey->setDisabled(true);
        ui->gbRSA->setEnabled(true);
        ui->gbRSA->show();
    }
}

void MainWindow::action_changed(int index) {
    // TODO: change this to the switch statement
    if (index==0) {
        ui->btnCode->setText(tr("Encrypt"));
    } else if (index==1) {
        ui->btnCode->setText(tr("Decrypt"));
    }
}

void MainWindow::output_textbox_changed() {
    if (ui->tOutput->toPlainText().size() != 0) {
        ui->btnSave->setEnabled(true);
    } else {
        ui->btnSave->setDisabled(true);
    }
}

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

void MainWindow::status_message(QString text) {
    status_message( text, 10000);
}

void MainWindow::status_message(QString text, int time) {
    if (ui->statusBar->currentMessage().size() != 0) ui->statusBar->clearMessage();

    ui->statusBar->showMessage( text, time );
}

void MainWindow::generate_RSA_key() {
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

    //  length || n  || e
    //  length || p  || q  || dP || dQ || qInv
    QString pub_s, priv_s;
    QTextStream pub(&pub_s), priv(&priv_s);

    pub << rsa_pub.length
        << "\n\n" << mpz_get_str(NULL, 16, rsa_pub.n)
        << "\n\n" << mpz_get_str(NULL, 10, rsa_pub.e);
    priv << rsa_priv.length
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.p)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.q)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.dP)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.dQ)
         << "\n\n" << mpz_get_str(NULL, 16, rsa_priv.qInv);

    ui->eRSAPublic->clear();
    ui->eRSAPrivate->clear();
    ui->eRSAPublic->setPlainText(pub_s);
    ui->eRSAPrivate->setPlainText(priv_s);
}

void MainWindow::load_rsa_pub() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        rsa_pub = load_public_key( file_names[0] );

        //  length || n  || e
        QString pub_s;
        QTextStream pub(&pub_s);

        pub << rsa_pub.length
            << "\n\n" << mpz_get_str(NULL, 16, rsa_pub.n)
            << "\n\n" << mpz_get_str(NULL, 10, rsa_pub.e);

        ui->eRSAPublic->clear();
        ui->eRSAPublic->setPlainText(pub_s);
        status_message(tr("Key loaded from file ") + file_names[0]);
    }
}

void MainWindow::save_rsa_pub() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        save_public_key(rsa_pub, file_names[0]);
        status_message(tr("Key saved to file ") + file_names[0]);
    }
}

void MainWindow::load_rsa_priv() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        rsa_priv = load_private_key( file_names[0] );

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
        status_message(tr("Key loaded from file ") + file_names[0]);
    }
}

void MainWindow::save_rsa_priv() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text documents (*.txt);;All files (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        save_private_key(rsa_priv, file_names[0]);
        status_message(tr("Key saved to file ") + file_names[0]);
    }
}

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
