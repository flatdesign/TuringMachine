#include "turingmachine.h"
#include "QDebug"

int TuringMachine::getState() {
    return this->state;
}

TuringMachine::TuringMachine(int countTapes) {
    this->state = 1;
    this->countTapes = countTapes;
    this->ready = false;
    for(int i = 0; i < countTapes; i++) {
        this->positions.push_back(0);
    }
}

bool TuringMachine::isReady() {
    return this->ready;
}

void TuringMachine::setNotReady() {
  this->ready = false;
}

bool TuringMachine::checkTable(QTableWidget *table) {
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

void TuringMachine::reset() {
    for(int i; i < this->countTapes; i++) {
        this->positions[i] = 0;
    }
    this->state = 1;
}

void TuringMachine::addCommand(int numberState, QTableWidget *table, int row){
    QString read = table->item(row, 1)->text();
    QString write = table->item(row, 2)->text();
    QString direction = table->item(row, 3)->text();
    QString nextState = table->item(row, 4)->text();
    this->states[numberState]->addCommand(read, write, direction, nextState);
}

bool TuringMachine::saveCommands(QTableWidget *table){
    for(int i = 0; i < table->rowCount(); i++) {
        int numberState = table->item(i, 0)->text().toInt();
        if(!this->states.contains(numberState)) {
            this->states[numberState] = new State();
        }
        this->addCommand(numberState, table, i);
    };
    this->ready = true;
    return true;
}

QVector<QString> TuringMachine::step(QVector<QString> lines) {
    QString value;
    for(int i = 0; i < lines.size(); i++) {
        value += lines[i][this->positions[i]];
    }

    Command *command = this->states[this->state]->getCommand(value);

    value = command->getWrite();
    this->state = command->getNextState().toInt();

    for(int i = 0; i < lines.size(); i++) {
        lines[i][this->positions[i]] = value[i];
    }

    return this->changePosition(lines, command);
}

QVector<QString> TuringMachine::changePosition(QVector<QString> lines, Command *command) {
    QString key = command->getDirection();
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
    return lines;
}


