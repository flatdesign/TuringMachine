#ifndef DEMOMACHINE_H
#define DEMOMACHINE_H

#include "windows.h"
#include "qobject.h"
#include "turingmachine.h"
#include "plot.h"
#include "qprogressbar.h"

class DemoMachine : public TuringMachine {
Q_OBJECT
public:
    DemoMachine(int tapes);
    QVector<QString> combinations(int size);
    void start();
    bool step();
    void setLength(int length);
    void setPlot(Plot *plot);
    void setProgressBar(QProgressBar* progress);
private:
    QVector<QString> words;
    QProgressBar* progress;
    int tapes;
    QString currentWord;
    int length;
    Plot* plot;
public slots:    
     void runAlgorithm();
signals:
     void stop();
     void print(double x, double y, Plot* plot);
     void upProgress(int value, QProgressBar *bar);
};

#endif // DEMOMACHINE_H
