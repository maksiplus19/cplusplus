#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
#include <QMessageBox>
#include "qcustomplot.h"

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
    void on_drawButton_clicked();

    void delete_curveVector();

private:
    Ui::MainWindow *ui;
    const double plotShift = 0.5;

    QPair<double, double> xRange, yRange;

    void plotRepaint(int delta = 1);
    void plotScaling(double scale);

    QVector<QCPCurve*> curveVector;
};

#endif // MAINWINDOW_H
