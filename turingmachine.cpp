#include "turingmachine.h"
#include "QDebug"

int TuringMachine::getCountTapes() {
    return this->countTapes;
}

int TuringMachine::getState() {
    return this->state;
}

int TuringMachine::getPosition() {
    return this->position;
}

TuringMachine::TuringMachine(int countTapes) {
    this->state = 1;
    this->countTapes = countTapes;
    this->ready = false;
}

bool TuringMachine::isReady() {
    return this->ready;
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

void TuringMachine::addCommand(int numberState, QTableWidget *table, int row){
    QString read = table->item(row, 0)->text();
    QString write = table->item(row, 1)->text();
    QString direction = table->item(row, 2)->text();
    QString nextState = table->item(row, 3)->text();
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
        value += lines[i][this->position];
    }

    Command *command = this->states[this->state]->getCommand(value);

    value = command->getWrite();
    this->state = command->getNextState().toInt();

    for(int i = 0; i < lines.size(); i++) {
        lines[i][this->position] = value[i];
    }
    return lines;
}


