#include "turingmachine.h"
#include "QDebug"
#include "QTimer"
#include "windows.h"

TuringMachine::TuringMachine(QObject *parent) : QObject(parent){
    this->state = 1;
    this->ready = false;
}

int TuringMachine::getState() {
    return this->state;
}

bool TuringMachine::isReady() {
    return this->ready;
}

void TuringMachine::setNotReady() {
  this->ready = false;
}

void TuringMachine::reset() {
    for(int i; i < this->tapes.size(); i++) {
        this->positions[i] = 0;
    }
    this->state = 1;
    this->ready = false;
}

void TuringMachine::addTapes(QVector<QTextEdit *> tapes) {
   this->tapes = tapes;
    for(int i = 0; i < tapes.size(); i++) {
        this->positions.push_back(0);
    }
}

void TuringMachine::addCommand(int numberState, QTableWidget *table, int row){
    QString read = table->item(row, 1)->text();
    QString write = table->item(row, 2)->text();
    QString direction = table->item(row, 3)->text();
    QString nextState = table->item(row, 4)->text();
    this->states[numberState]->addCommand(read, write, direction, nextState);
}

void TuringMachine::saveCommands(QTableWidget *table){
    for(int i = 0; i < table->rowCount(); i++) {
        int numberState = table->item(i, 0)->text().toInt();
        if(!this->states.contains(numberState)) {
            this->states[numberState] = new State();
        }
        this->addCommand(numberState, table, i);
    };
    this->ready = true;
}

bool TuringMachine::step() {
    QVector<QString> lines;
    lines.resize(this->tapes.size());
    for(int i = 0; i < this->tapes.size(); i++) {       // Считали массив строк
        lines[i] = this->tapes[i]->toPlainText();
    }

    QString value;
    for(int i = 0; i < lines.size(); i++) {         // Считали команду
        if(lines[i][this->positions[i]] == '\x0')
           lines[i][this->positions[i]] = '_';
        value += lines[i][this->positions[i]];
    }

    Command *command = this->states[this->state]->getCommand(value);

    value = command->getWrite();                    // Получили команду

    for(int i = 0; i < lines.size(); i++) {         // Записали нужные сиволы в строки
        lines[i][this->positions[i]] = value[i];
    }

    QString key = command->getDirection();      // Меням позицию
    for(int i = 0; i < lines.size(); i++) {
        switch(key[i].unicode()) {
            case 60: {
                if(this->positions[i] == 0) {
                   lines[i].insert(0, '_');
                } else {
                    this->positions[i]--;
                }
                break;
            }
            case 62: {
                if(++this->positions[i] == lines[i].length())
                   lines[i].push_back('_');
                break;
            }
            default: {
                break;
            }

        }
    }

    for(int i = 0; i < this->tapes.size(); i++) {     // Записываем строки в edit
        QTextEdit *edit = this->tapes[i];
        emit this->writeLine(lines[i], edit);
    }

    this->state = command->getNextState().toInt();
    if(this->state == 0) {
        return false;
    }
    return true;
}

void TuringMachine::start() {
    bool key;
    do {
      key = this->step();
      Sleep(150);
    } while (key);
    emit this->end();
}



