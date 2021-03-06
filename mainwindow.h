#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTableWidget"
#include "turingmachine.h"
#include "QThread"
#include "plot.h"
#include "demomachine.h"


#include "QFileDialog"
#include "QFile"
#include <QStringList>
#include <QTextCodec>
#include <QTextStream>
#include "qprogressbar.h"
#include "qcoreapplication.h"

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
    void saveFile(QTableWidget *table);
    void openFile(QTableWidget *table);


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

    void on_single_open_triggered();

    void on_single_save_triggered();

    void on_multi_open_triggered();

    void on_multi_save_triggered();

    void writeLine(QString line, QTextEdit *edit);

    void end();

    void printNotFound();

    void on_demoStart_clicked();

    void addToPlot(double x, double y, Plot *plot);

    void on_demoStart_2_clicked();

    void upProgress(int progress, QProgressBar *bar);

    void printLog(QString line);


private:
    Ui::MainWindow *ui;
    TuringMachine tur1;
    TuringMachine tur2;
    DemoMachine *demo1 = new DemoMachine(1);
    DemoMachine *demo2 = new DemoMachine(2);
    QThread thread1;
    QThread thread2;
    QThread thread3;
    QThread thread4;
    Plot *plot;
    Plot *plot_2;
};

#endif // MAINWINDOW_H
