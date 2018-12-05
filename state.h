#ifndef STATE_H
#define STATE_H
#include "QMap"
#include "command.h"


class State {
private:
    QMap <QString, Command *> commands;
public:
    State();
    void addCommand(QString read, QString write, QString direction, QString nextState);
    Command* getCommand(QString command);
};

#endif // STATE_H
