#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
