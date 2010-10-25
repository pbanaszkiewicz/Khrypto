/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Oct 25 18:35:53 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGenerate_random_key;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *gbSettings;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cbMethod;
    QLabel *label_2;
    QComboBox *cbAction;
    QLabel *label_3;
    QSpinBox *sbKey;
    QGroupBox *gbRSA;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnGenerateRSAKey;
    QComboBox *cbKeyLenghts;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QPushButton *btnRSALoad1;
    QPushButton *btnRSASave1;
    QPlainTextEdit *eRSAPublic;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QPushButton *btnRSALoad2;
    QPushButton *btnRSASave2;
    QPlainTextEdit *eRSAPrivate;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *LInput;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLoad;
    QPlainTextEdit *tInput;
    QPushButton *btnCode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LOutput;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSave;
    QPlainTextEdit *tOutput;
    QMenuBar *menuBar;
    QMenu *menuApplication;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(674, 687);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionGenerate_random_key = new QAction(MainWindow);
        actionGenerate_random_key->setObjectName(QString::fromUtf8("actionGenerate_random_key"));
        actionGenerate_random_key->setEnabled(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gbSettings = new QGroupBox(centralWidget);
        gbSettings->setObjectName(QString::fromUtf8("gbSettings"));
        verticalLayout_3 = new QVBoxLayout(gbSettings);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(gbSettings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbMethod = new QComboBox(gbSettings);
        cbMethod->setObjectName(QString::fromUtf8("cbMethod"));

        gridLayout->addWidget(cbMethod, 0, 1, 1, 1);

        label_2 = new QLabel(gbSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        cbAction = new QComboBox(gbSettings);
        cbAction->setObjectName(QString::fromUtf8("cbAction"));
        cbAction->setEnabled(false);

        gridLayout->addWidget(cbAction, 1, 1, 1, 1);

        label_3 = new QLabel(gbSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        sbKey = new QSpinBox(gbSettings);
        sbKey->setObjectName(QString::fromUtf8("sbKey"));
        sbKey->setEnabled(false);
        sbKey->setMinimum(-65356);
        sbKey->setMaximum(65356);
        sbKey->setValue(3);

        gridLayout->addWidget(sbKey, 2, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);

        verticalLayout_3->addLayout(gridLayout);

        gbRSA = new QGroupBox(gbSettings);
        gbRSA->setObjectName(QString::fromUtf8("gbRSA"));
        verticalLayout_2 = new QVBoxLayout(gbRSA);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btnGenerateRSAKey = new QPushButton(gbRSA);
        btnGenerateRSAKey->setObjectName(QString::fromUtf8("btnGenerateRSAKey"));

        horizontalLayout_6->addWidget(btnGenerateRSAKey);

        cbKeyLenghts = new QComboBox(gbRSA);
        cbKeyLenghts->setObjectName(QString::fromUtf8("cbKeyLenghts"));

        horizontalLayout_6->addWidget(cbKeyLenghts);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(gbRSA);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        btnRSALoad1 = new QPushButton(gbRSA);
        btnRSALoad1->setObjectName(QString::fromUtf8("btnRSALoad1"));

        horizontalLayout_5->addWidget(btnRSALoad1);

        btnRSASave1 = new QPushButton(gbRSA);
        btnRSASave1->setObjectName(QString::fromUtf8("btnRSASave1"));

        horizontalLayout_5->addWidget(btnRSASave1);


        verticalLayout_2->addLayout(horizontalLayout_5);

        eRSAPublic = new QPlainTextEdit(gbRSA);
        eRSAPublic->setObjectName(QString::fromUtf8("eRSAPublic"));
        eRSAPublic->setReadOnly(true);

        verticalLayout_2->addWidget(eRSAPublic);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(gbRSA);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        btnRSALoad2 = new QPushButton(gbRSA);
        btnRSALoad2->setObjectName(QString::fromUtf8("btnRSALoad2"));

        horizontalLayout_4->addWidget(btnRSALoad2);

        btnRSASave2 = new QPushButton(gbRSA);
        btnRSASave2->setObjectName(QString::fromUtf8("btnRSASave2"));

        horizontalLayout_4->addWidget(btnRSASave2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        eRSAPrivate = new QPlainTextEdit(gbRSA);
        eRSAPrivate->setObjectName(QString::fromUtf8("eRSAPrivate"));
        eRSAPrivate->setReadOnly(true);

        verticalLayout_2->addWidget(eRSAPrivate);


        verticalLayout_3->addWidget(gbRSA);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout_3->setStretch(0, 1);

        horizontalLayout_3->addWidget(gbSettings);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        LInput = new QLabel(centralWidget);
        LInput->setObjectName(QString::fromUtf8("LInput"));

        horizontalLayout->addWidget(LInput);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));

        horizontalLayout->addWidget(btnLoad);


        verticalLayout->addLayout(horizontalLayout);

        tInput = new QPlainTextEdit(centralWidget);
        tInput->setObjectName(QString::fromUtf8("tInput"));
        tInput->setEnabled(false);

        verticalLayout->addWidget(tInput);

        btnCode = new QPushButton(centralWidget);
        btnCode->setObjectName(QString::fromUtf8("btnCode"));

        verticalLayout->addWidget(btnCode);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        LOutput = new QLabel(centralWidget);
        LOutput->setObjectName(QString::fromUtf8("LOutput"));

        horizontalLayout_2->addWidget(LOutput);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnSave = new QPushButton(centralWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_2->addWidget(btnSave);


        verticalLayout->addLayout(horizontalLayout_2);

        tOutput = new QPlainTextEdit(centralWidget);
        tOutput->setObjectName(QString::fromUtf8("tOutput"));
        tOutput->setEnabled(false);

        verticalLayout->addWidget(tOutput);


        horizontalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 674, 23));
        menuApplication = new QMenu(menuBar);
        menuApplication->setObjectName(QString::fromUtf8("menuApplication"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuApplication->menuAction());
        menuApplication->addAction(actionGenerate_random_key);
        menuApplication->addSeparator();
        menuApplication->addAction(actionExit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        cbMethod->setCurrentIndex(0);
        cbKeyLenghts->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Khrypto", 0, QApplication::UnicodeUTF8));
        actionGenerate_random_key->setText(QApplication::translate("MainWindow", "&Generate random key", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        gbSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Method", 0, QApplication::UnicodeUTF8));
        cbMethod->clear();
        cbMethod->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Caezar Cipher", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Fence", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "XOR", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "RSA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Huffman", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "Action", 0, QApplication::UnicodeUTF8));
        cbAction->clear();
        cbAction->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Encrypting", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Decrypting", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("MainWindow", "Key", 0, QApplication::UnicodeUTF8));
        gbRSA->setTitle(QApplication::translate("MainWindow", "RSA", 0, QApplication::UnicodeUTF8));
        btnGenerateRSAKey->setText(QApplication::translate("MainWindow", "Generate key", 0, QApplication::UnicodeUTF8));
        cbKeyLenghts->clear();
        cbKeyLenghts->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "512 bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1024 bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2048 bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4096 bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "8192 bits", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("MainWindow", "Public key:", 0, QApplication::UnicodeUTF8));
        btnRSALoad1->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        btnRSASave1->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Private key:", 0, QApplication::UnicodeUTF8));
        btnRSALoad2->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        btnRSASave2->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        LInput->setText(QApplication::translate("MainWindow", "Input text:", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MainWindow", "Load from file", 0, QApplication::UnicodeUTF8));
        btnCode->setText(QApplication::translate("MainWindow", "Encrypt", 0, QApplication::UnicodeUTF8));
        LOutput->setText(QApplication::translate("MainWindow", "Output text:", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MainWindow", "Save to file", 0, QApplication::UnicodeUTF8));
        menuApplication->setTitle(QApplication::translate("MainWindow", "&Application", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
