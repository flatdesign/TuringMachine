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

    void on_addState_clicked();

    void on_deleteState_clicked();

    void on_save_clicked();

    void on_test_clicked();

    void on_step_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
