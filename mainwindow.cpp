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

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));

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
    double ilosc_prostokatow = czas/krok;

    for (int i=0; i<ilosc_prostokatow; ++i)
    {
      x.append(krok * i);


      y1.append(qSin(i*(czas*0.5*3.14159/ilosc_prostokatow)));      //SINUS


      //i > 100 ? y1.append(2) : y1.append(0);  //STEP

      //wyjscie
      y0.append(trapez1[i]);

      //calkowanie metoda prostokatow
      x1.append(x1[i] + krok * x2[i]);
      x2.append(x2[i] + krok * (- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)));

      //metoda trapezow na podstawie powyzszej metody prostokatow
      trapez1.append(trapez1[i] + krok*(x2[i]+x2[i+1])*0.5);
      trapez2.append(trapez2[i] + krok*((- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)) + (- b*x2[i+1] - A*tanh(a*x1[i+1]) + pow(y1[i+1], 3)))*0.5);

    }

    ///////////////////////////////////////////////
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
    ///////////////////////////////////////////////
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
    double ilosc_prostokatow = czas/krok;

    for (int i=0; i<ilosc_prostokatow; ++i)
    {
      x.append(krok * i);

      switch (ksztalt) {
      case 1:
          y1.append(qSin(i*(czas*0.5*3.14159/ilosc_prostokatow)));                          //SINUS
          break;
      case 2:
          if(qSin(i*(czas*0.5*3.14159/ilosc_prostokatow))>=0)
              y1.append(1);                                                                 //SQUARE
          else y1.append(-1);
          break;
      default:
          y1.append(2/3.14159*asin(qSin(i*(czas*0.5*3.14159/ilosc_prostokatow))));          //TRIANGLE
          break;
      }



      //i > 100 ? y1.append(2) : y1.append(0);  //STEP

      y0.append(trapez1[i]);

      x1.append(x1[i] + krok * x2[i]);
      x2.append(x2[i] + krok * (- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)));

      trapez1.append(trapez1[i] + krok*(x2[i]+x2[i+1])*0.5);
      trapez2.append(trapez2[i] + krok*((- b*x2[i] - A*tanh(a*x1[i]) + pow(y1[i], 3)) + (- b*x2[i+1] - A*tanh(a*x1[i+1]) + pow(y1[i+1], 3)))*0.5);

    }


    ui->customPlot->graph(0)->setData(x, y0);
    ui->customPlot->graph(1)->setData(x, y1);

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);

    ui->customPlot->replot();

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

void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    czas = ui->horizontalSlider_2->value();
}

void MainWindow::on_doubleSpinBox_b_valueChanged(double arg1)
{
    b = arg1;
}

void MainWindow::on_doubleSpinBox_A_valueChanged(double arg1)
{
    A = arg1;
}

void MainWindow::on_doubleSpinBox_a_valueChanged(double arg1)
{
    a = arg1;
}
