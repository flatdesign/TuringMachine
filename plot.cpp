#include "plot.h"

Plot::Plot(QCustomPlot *plot) {
    this->plot = plot;
    this->plot->addGraph();
    this->plot->xAxis->setRange(0, 40);
    this->plot->yAxis->setRange(0, 600);
    this->plot->replot();
}

void Plot::addPoint(double x, double y) {
    this->x.push_back(x);
    this->y.push_back(y);
}

void Plot::paint() {
    this->plot->graph(0)->setData(this->x, this->y);
    this->plot->replot();
}
