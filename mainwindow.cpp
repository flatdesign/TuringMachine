#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QThread"

#include "turingmachine.h"
#include "QDebug"

TuringMachine tur1(1);
TuringMachine tur2(3);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
} 

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_addState_2_clicked() {
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    tur2.setNotReady();
}

void MainWindow::on_deleteState_2_clicked() {
    if(ui->tableWidget_2->rowCount() > 1) {
        ui->tableWidget_2->removeRow(ui->tableWidget_2->rowCount() - 1);
        tur2.setNotReady();
    }
}

void MainWindow::on_save_2_clicked() {
    if(tur2.checkTable(ui->tableWidget_2)) {
      tur2.saveCommands(ui->tableWidget_2);
    } else {
        QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }

}

void MainWindow::on_step_2_clicked() {
    if(tur2.isReady()) {
        if(tur2.getState() != 0) {
            QVector <QString> lines = {ui->edit_2->toPlainText(), ui->edit_3->toPlainText(), ui->edit_4->toPlainText()};
            lines = tur2.step(lines);
            ui->edit_2->clear();
            ui->edit_3->clear();
            ui->edit_4->clear();
            ui->edit_2->setText(lines[0]);
            ui->edit_3->setText(lines[1]);
            ui->edit_4->setText(lines[2]);
        } else {
            QMessageBox::information(0, "Успех", "МТ закночила выполнять ваш алгоритм");
            tur2.reset();
        }

    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }

}

void MainWindow::on_start_2_clicked() {
    if(tur2.isReady()) {

    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }
}


void MainWindow::on_addState_1_clicked() {
    ui->tableWidget_1->insertRow(ui->tableWidget_1->rowCount());
    tur1.setNotReady();
}

void MainWindow::on_deleteState_1_clicked() {
    if(ui->tableWidget_1->rowCount() > 1) {
        ui->tableWidget_1->removeRow(ui->tableWidget_1->rowCount() - 1);
        tur1.setNotReady();
    }
}

void MainWindow::on_save_1_clicked() {
    if(tur1.checkTable(ui->tableWidget_1)) {
      tur1.saveCommands(ui->tableWidget_1);
    } else {
        QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }

}

void MainWindow::on_step_1_clicked() {
    if(tur1.isReady()) {
        if(tur1.getState() != 0) {
            QVector <QString> lines = {ui->edit_1->toPlainText()};
            lines = tur1.step(lines);
            ui->edit_1->clear();
            ui->edit_1->setText(lines[0]);
        } else {
            QMessageBox::information(0, "Успех", "МТ закночила выполнять ваш алгоритм");
            tur1.reset();
        }

    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }

}

void MainWindow::on_start_1_clicked() {
    if(tur1.isReady()) {

    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }
}
