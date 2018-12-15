#ifndef PLOT_H
#define PLOT_H

#include "qcustomplot.h"
#include "QVector"


class Plot
{

public:
    Plot(QCustomPlot *plot);
    void addPoint(double x, double y);
    void paint();
private:
    QVector<double> x, y;
    QCustomPlot *plot;
};

#endif // PLOT_H
