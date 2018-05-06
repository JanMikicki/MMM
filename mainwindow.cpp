#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

double b=1,A=1,a=1;
int ksztalt = 1;
int krok_ms = 25;
int czas = 12;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // add two new graphs and set their look:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x, y0, y1;
    QVector<double> x1;
    QVector<double> x2;
    QVector<double> trapez1;
    QVector<double> trapez2;
    x1.append(0);
    x2.append(0);
    trapez1.append(0);
    trapez2.append(0);
    y1.append(0);

    double krok = krok_ms * 0.001;

    for (int i=0; i<551; ++i)
    {
      x.append(krok * i);


      y1.append(qSin(i*(4*3.14159/251)));      //SINUS


      //i > 100 ? y1.append(2) : y1.append(0);  //STEP

      y0.append(trapez1[i]);

      x1.append(x1[i] + krok * x2[i]);
      x2.append(x2[i] + krok * (- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)));

      trapez1.append(trapez1[i] + krok*(x2[i]+x2[i+1])*0.5);
      trapez2.append(trapez2[i] + krok*((- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)) + (- b*x2[i+1] - A*tanh(a*x1[i+1]) + pow(y1[i+1], 3)))*0.5);

    }

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(x, y0);
    ui->customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    b=arg1;
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    A=arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    a=arg1;
}

void MainWindow::on_pushButton_clicked()
{

    QVector<double> x, y0, y1;
    QVector<double> x1;
    QVector<double> x2;
    QVector<double> trapez1;
    QVector<double> trapez2;
    x1.append(0);
    x2.append(0);
    trapez1.append(0);
    trapez2.append(0);
    y1.append(0);

    double krok = krok_ms * 0.001;

    for (int i=0; i<551; ++i)
    {
      x.append(krok * i);

      switch (ksztalt) {
      case 1:
          y1.append(qSin(i*(4*3.14159/251)));                          //SINUS
          break;
      case 2:
          if(qSin(i*(4*3.14159/251))>=0)
              y1.append(1);                                            //SQUARE
          else y1.append(-1);
          break;
      default:
          y1.append(2/3.14159*asin(qSin(i*(4*3.14159/251))));          //TRIANGLE
          break;
      }



      //i > 100 ? y1.append(2) : y1.append(0);  //STEP

      y0.append(trapez1[i]);

      x1.append(x1[i] + krok * x2[i]);
      x2.append(x2[i] + krok * (- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)));

      trapez1.append(trapez1[i] + krok*(x2[i]+x2[i+1])*0.5);
      trapez2.append(trapez2[i] + krok*((- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)) + (- b*x2[i+1] - A*tanh(a*x1[i+1]) + pow(y1[i+1], 3)))*0.5);

    }

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(x, y0);
    ui->customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->replot();
    // Note: we could have also just called ui->customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{
    ksztalt = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    ksztalt = 2;
}

void MainWindow::on_radioButton_3_clicked()
{
    ksztalt = 3;
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    krok_ms = ui->horizontalSlider->value();
}
