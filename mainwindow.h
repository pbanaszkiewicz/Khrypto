#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rsa.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void status_message(QString);
    void status_message(QString, int);
    RSA_PUBLIC rsa_pub;
    RSA_PRIVATE rsa_priv;

private slots:
    void code(); //btnCode.clicked()
    void method_changed(int); //cbMethod.currentIndexChanged(int)
    void output_textbox_changed(); //tOutput.textChanged()
    void save_file(); //btnSave.clicked()
    void load_file(); //btnLoad.clicked()
    void action_changed(int); //cbAction.currentIndexChanged(int)
    void generate_RSA_key(); //btnGenerateRSAKey.clicked()
};

#endif // MAINWINDOW_H
