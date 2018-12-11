#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTableWidget"
#include "turingmachine.h"
#include "QThread"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checkTable(QTableWidget *table);


private slots:
    void on_addState_1_clicked();

    void on_deleteState_1_clicked();

    void on_save_1_clicked();

    void on_step_1_clicked();

    void on_start_1_clicked();

    void on_addState_2_clicked();

    void on_deleteState_2_clicked();

    void on_save_2_clicked();

    void on_step_2_clicked();

    void on_start_2_clicked();

    void writeLine(QString line, QTextEdit *edit);

private:
    Ui::MainWindow *ui;
    TuringMachine tur1;
    TuringMachine tur2;
    QThread thread1;
    QThread thread2;
};

#endif // MAINWINDOW_H
