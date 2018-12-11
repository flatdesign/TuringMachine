#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include "state.h"
#include "QTableWidget"
#include "QTextEdit"
#include "QObject"
#include "QMessageBox"


class TuringMachine : public QObject {
    Q_OBJECT
private:
    bool ready;
    int state;
    QVector<int> positions;
    QVector<QTextEdit*> tapes;
    QMap<int, State*> states;
public:
    explicit TuringMachine(QObject *parent = 0);
    int getState();
    bool isReady();
    void addCommand(int numberState, QTableWidget *table,  int row);
    void saveCommands(QTableWidget *table);
    void setNotReady();
    void reset();
    void addTapes(QVector<QTextEdit*> tapes);
public slots:
     bool step();
     void start();
signals:
     void end();
     void writeLine(QString line, QTextEdit *edit);
};

#endif // TURINGMACHINE_H
