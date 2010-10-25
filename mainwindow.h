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
    void clear_status_message();
    RSA_PUBLIC rsa_pub;
    RSA_PRIVATE rsa_priv;
    void present_rsa_public();
    void present_rsa_private();

private slots:
    void code(); //btnCode.clicked()
    void method_changed(int); //cbMethod.currentIndexChanged(int)
    void output_textbox_changed(); //tOutput.textChanged()
    void save_file(); //btnSave.clicked()
    void load_file(); //btnLoad.clicked()
    void action_changed(int); //cbAction.currentIndexChanged(int)
    void generate_RSA_key(); //btnGenerateRSAKey.clicked()
    void load_rsa_pub(); //btnRSALoad1.clicked()
    void save_rsa_pub(); //btnRSASave1.clicked()
    void load_rsa_priv(); //btnRSALoad2.clicked()
    void save_rsa_priv(); //btnRSASave2.clicked()
    void generate_random_key(); //

};

#endif // MAINWINDOW_H
