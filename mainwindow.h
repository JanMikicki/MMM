#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    //void on_spinBox_valueChanged(int arg1);

    //void on_spinBox_2_valueChanged(int arg1);

    //void on_spinBox_3_valueChanged(int arg1);

    //void on_pushButton_released();

    //void on_pushButton_clicked(bool checked);

    //void on_pushButton_toggled(bool checked);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_2_sliderReleased();

    void on_doubleSpinBox_b_valueChanged(double arg1);

    void on_doubleSpinBox_A_valueChanged(double arg1);

    void on_doubleSpinBox_a_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
