#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


#include "turingmachine.h"
#include "QDebug"
TuringMachine tur1(1);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
} 

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_addState_clicked() {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void MainWindow::on_deleteState_clicked() {
    if(ui->tableWidget->rowCount() > 1) {
        ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
    }
}

void MainWindow::on_save_clicked() {
    if(tur1.checkTable(ui->tableWidget)) {
      tur1.saveCommands(ui->tableWidget);
    } else {
        QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }

}

void MainWindow::on_step_clicked() {
    if(tur1.isReady()) {
        QVector <QString> lines = {ui->edit1->toPlainText(), ui->edit2->toPlainText(), ui->edit3->toPlainText()};
        lines = tur1.step(lines);
        ui->edit1->clear();
        ui->edit2->clear();
        ui->edit3->clear();
        ui->edit1->setText(lines[0]);
        ui->edit2->setText(lines[1]);
        ui->edit3->setText(lines[2]);
    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }

}

void MainWindow::on_start_clicked() {
    if(tur1.isReady()) {

    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }
}

void MainWindow::on_test_clicked() {
}
