#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void code(); //btnCode.clicked()
    void method_changed(int); //cbMethod.currentIndexChanged(int)
    void output_textbox_changed(); //tOutput.textChanged()
    void save_file(); //btnSave.clicked()
    void load_file(); //btnLoad.clicked()
    void action_changed(int); //cbAction.currentIndexChanged(int)
};

#endif // MAINWINDOW_H
