#include "command.h"

Command::Command(QString read, QString write, QString direction, QString nextState){
    this->read = read;
    this->write = write;
    this->direction = direction;
    this->nextState = nextState;
}

QString Command::getWrite() {
    return this->write;
}

QString Command::getRead() {
    return this->read;
}

QString Command::getNextState() {
    return this->nextState;
}

QString Command::getDirection() {
    return this->direction;
}
