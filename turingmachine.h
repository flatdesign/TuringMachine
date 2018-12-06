#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include "state.h"
#include "QTableWidget"
#include "QTextEdit"


class TuringMachine{
private:
    bool ready;
    int state;
    QVector<int> positions;
    int countTapes;
    QMap<int, State*> states;
public:
    TuringMachine(int countTapes);
    int getState();
    void addCommand(int numberState, QTableWidget *table,  int row);
    bool saveCommands(QTableWidget *table);
    bool isReady();
    void setNotReady();
    bool checkTable(QTableWidget *table);
    void reset();
    QVector<QString> step(QVector<QString> lines);
    QVector<QString> changePosition(QVector<QString> lines, Command *command);
};

#endif // TURINGMACHINE_H
