#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include "state.h"
#include "QTableWidget"
#include "QTextEdit"


class TuringMachine{
private:
    bool ready;
    int state;
    int position;
    int countTapes;
    QMap<int, State*> states;
public:
    TuringMachine(int countTapes);
    int getState();
    int getPosition();
    int getCountTapes();
    void addCommand(int numberState, QTableWidget *table,  int row);
    bool saveCommands(QTableWidget *table);
    bool isReady();
    bool checkTable(QTableWidget *table);
    QVector<QString> step(QVector<QString> lines);
};

#endif // TURINGMACHINE_H
