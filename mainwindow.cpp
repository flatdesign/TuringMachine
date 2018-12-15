#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
        QVector<QTextEdit*> tapes1 = {ui->edit_1};
        QVector<QTextEdit*> tapes2 = {ui->edit_2, ui->edit_3};
        tur1.addTapes(tapes1);
        tur2.addTapes(tapes2);

        // Потоки
        connect(&thread1, SIGNAL(started()), &tur1, SLOT(start()));
        connect(&tur1, SIGNAL(end()), &thread1, SLOT(terminate()));
        connect(&thread2, SIGNAL(started()), &tur2, SLOT(start()));
        connect(&tur2, SIGNAL(end()), &thread2, SLOT(terminate()));

        // Замена строк в edit
        connect(&tur1, SIGNAL(writeLine(QString,QTextEdit*)), this, SLOT(writeLine(QString,QTextEdit*)));
        connect(&tur2, SIGNAL(writeLine(QString,QTextEdit*)), this, SLOT(writeLine(QString,QTextEdit*)));

        // Алгоритм завершен
        connect(&tur1, SIGNAL(complete()), this, SLOT(printEnd()));
        connect(&tur2, SIGNAL(complete()), this, SLOT(printEnd()));

        // Команда не найдена
        connect(&tur1, SIGNAL(commandNotFound()), this, SLOT(printNotFound()));
        connect(&tur2, SIGNAL(commandNotFound()), this, SLOT(printNotFound()));

        // Графики
        this->plot = new Plot(ui->plot);
        this->plot_2 = new Plot(ui->plot_2);

    }

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::checkTable(QTableWidget *table) {   // Проверка таблицы на пустые ячейки
    for(int i = 0; i < table->rowCount(); i++) {
        for (int j = 0; j < table->columnCount(); j++) {
            if(table->item(i, j) == 0) {
                return false;
            } else {
               if(table->item(i, j)->text() == "") {
                   return false;
               }
            }
        }
    }

    return true;
}

void MainWindow::saveFile(QTableWidget *table) {
    if(this->checkTable(table)) {
        QFile file;
        QString fileName = QFileDialog::getOpenFileName(this, "Сохранение таблицы", "D://");
        file.setFileName(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            for(int i = 0; i < table->rowCount(); i++) {
                for(int j = 0; j < table->columnCount(); j++) {
                    out << table->item(i, j)->text() + "\r\n";
                }
            }
            file.close();
        } else {
            QMessageBox::warning(0, "Предупреждение", "Файл не удалось сохранить");
        }
    } else {
       QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }
}

void MainWindow::openFile(QTableWidget *table) {
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(this, "Открытие таблицы", "D://");
    file.setFileName(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        table->setRowCount(0);
        int row = 0;
        while(!file.atEnd()) {
            table->insertRow(table->rowCount());
            for(int i = 0; i < 5; i++) {
                QString str = QString::fromUtf8(file.readLine());
                table->setItem(row, i, new QTableWidgetItem(str.left(str.length() - 2)));
            }
            row++;
        }
        file.close();
    } else {
        QMessageBox::warning(0, "Предупреждение", "Файл не удалось открыть");
    }
}





void MainWindow::writeLine(QString line, QTextEdit *edit) {     // Замена строки после шага МТ
    edit->clear();
    edit->setText(line);
}

void MainWindow::printEnd() {
    QMessageBox::information(0, "Операция выполнена", "МТ закночила выполнять ваш алгоритм");
    this->plot->addPoint(20, this->tur1.getSteps());
    this->plot->addPoint(30, this->tur1.getSteps());
    this->plot->paint();
    qDebug() << QString::number(this->tur1.getSteps());
    this->tur1.refreshSteps();
}

void MainWindow::printNotFound() {
    QMessageBox::warning(0, "Ошибка", "Данная команда не найдена");
}

void MainWindow::on_addState_1_clicked() {                      // Добавление строки
    ui->tableWidget_1->insertRow(ui->tableWidget_1->rowCount());
    tur1.setNotReady();
}

void MainWindow::on_deleteState_1_clicked() {                   // Удаление строки
    if(ui->tableWidget_1->rowCount() > 1) {
        ui->tableWidget_1->removeRow(ui->tableWidget_1->rowCount() - 1);
        tur1.setNotReady();
    }
}

void MainWindow::on_save_1_clicked() {                  // Занесение команд в МТ
    if(this->checkTable(ui->tableWidget_1)) {
      tur1.saveCommands(ui->tableWidget_1);
    } else {
        QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }

}

void MainWindow::on_step_1_clicked() {               // Шаг МТ
    if(tur1.isReady()) {
        if(!tur1.step())
            tur1.reset();
    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }

}

void MainWindow::on_start_1_clicked() {              // Запуск МТ
    if(tur1.isReady()) {
        tur1.moveToThread(&thread1);
        thread1.start();
    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }
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
    if(this->checkTable(ui->tableWidget_2)) {
      tur2.saveCommands(ui->tableWidget_2);
    } else {
        QMessageBox::warning(0, "Предупреждение", "Заполните все ячейки!");
    }

}

void MainWindow::on_step_2_clicked() {
    if(tur2.isReady()) {
        if(!tur2.step())
            tur2.reset();
    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }

}

void MainWindow::on_start_2_clicked() {
    if(tur2.isReady()) {
        tur2.moveToThread(&thread2);
        thread2.start();
    } else {
       QMessageBox::warning(0, "Предупреждение", "Сохраните команды Машины Тьюринга");
    }
}

void MainWindow::on_single_save_triggered() {
    this->saveFile(ui->tableWidget_1);
}

void MainWindow::on_single_open_triggered() {
    this->openFile(ui->tableWidget_1);
}

void MainWindow::on_multi_open_triggered() {
    this->openFile(ui->tableWidget_2);
}

void MainWindow::on_multi_save_triggered() {
    this->saveFile(ui->tableWidget_2);
}
