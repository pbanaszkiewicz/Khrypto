#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ciphers.h"
#include "rsa.h"
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //settings
    //schowaj co zbędne -> ładowanie kluczy etc

    //odblokuj co trzeba
    ui->cbAction->setEnabled(true);
    ui->tInput->setEnabled(true);
    ui->tOutput->setEnabled(true);
    ui->sbKey->setEnabled(true);
    ui->tOutput->setReadOnly(true);
    ui->gbRSA->setDisabled(true);
    ui->gbRSA->hide();
    ui->btnSave->setDisabled(true);

    //slots
    connect( ui->btnCode, SIGNAL(clicked()), this, SLOT(code()) );
    connect( ui->cbMethod,SIGNAL(currentIndexChanged(int)), this, SLOT(method_changed(int)));
    connect( ui->cbAction,SIGNAL(currentIndexChanged(int)), this, SLOT(action_changed(int)));
    connect( ui->tOutput, SIGNAL(textChanged()), this, SLOT(output_textbox_changed()));
    connect( ui->btnLoad, SIGNAL(clicked()), this, SLOT(load_file()));
    connect( ui->btnSave, SIGNAL(clicked()), this, SLOT(save_file()));
    
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    status_message(tr("Witaj w programie Khrypto."));
}

void MainWindow::code() {
    QString result;

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
            Primes r;
            result = "";
            break;}
        case 4: //MD5
            result = "";
            break;
        case 5: //DES
            result = "";
            break;
        case 6: //Huffman
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
            result = "";
            break;
        case 4: //MD5
            result = "";
            break;
        case 5: //DES
            result = "";
            break;
        case 6: //Huffman
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
    if (index==4) {
        ui->cbAction->setCurrentIndex(0);
        ui->cbAction->setDisabled(true);
        ui->sbKey->setDisabled(true);
    } else if (index==3) {
        ui->sbKey->setDisabled(true);
        ui->gbRSA->setEnabled(true);
        ui->gbRSA->show();
    }
}

void MainWindow::action_changed(int index) {
    // TODO: change this to the switch statement
    if (index==0) {
        ui->btnCode->setText(tr("Zaszyfruj"));
    } else if (index==1) {
        ui->btnCode->setText(tr("Odszyfruj"));
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
    dialog.setNameFilter(tr("Dokumenty tekstowe (*.txt);;Wszystkie pliki (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        QFile file( file_names[0] );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // TODO: wyświetlanie błędu na StatusBarze (osobna funkcja)
            status_message(tr("Błąd: nie można otworzyć pliku ") + file_names[0]);
            return;
        }

        ui->tInput->clear();
        ui->tInput->setPlainText( QString( file.readAll() ) );
        status_message(tr("Załadowano plik ") + file_names[0]);

        file.close();
    }
}

void MainWindow::save_file() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Dokumenty tekstowe (*.txt);;Wszystkie pliki (*.*)"));

    QStringList file_names;
    if (dialog.exec()) {
        file_names = dialog.selectedFiles();

        QFile file( file_names[0] );
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // TODO: wyświetlanie błędu na StatusBarze (osobna funkcja)
            status_message(tr("Błąd: nie można otworzyć pliku ") + file_names[0]);
            return;
        }

        QByteArray ar;
        ar.append( ui->tOutput->toPlainText() );
        file.write(ar);

        file.close();
        status_message(tr("Zapisano do pliku ") + file_names[0]);
    }
}

void MainWindow::status_message(QString text) {
    status_message( text, 10000);
}
void MainWindow::status_message(QString text, int time) {
    if (ui->statusBar->currentMessage().size() != 0) ui->statusBar->clearMessage();

    ui->statusBar->showMessage( text, time );
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
