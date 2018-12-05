#ifndef COMMAND_H
#define COMMAND_H
#include "QString"


class Command
{
private:
    QString read;
    QString write;
    QString direction;
    QString nextState;
public:
    Command(QString read, QString write, QString direction, QString nextState);
    QString getDirection();
    QString getWrite();
    QString getRead();
    QString getNextState();
};

#endif // COMMAND_H
