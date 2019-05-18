#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    xRange = QPair<double, double>(0, 0);
    yRange = QPair<double, double>(0, 0);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    ui->customPlot->clearGraphs();
//    delete_curveVector();
    QString fileName = QFileDialog::getOpenFileName(this,
                                           QString::fromUtf8("Открыть файл"),
                                           QDir::currentPath(),
                                           "Текст (*.txt);;Все файлы (*.*)");
    if (fileName=="") return;

    QFile file(fileName);
    file.open(QFile::ReadOnly);
    if (!file.isOpen()) return;

    ui->customPlot->clearGraphs();

    QTextStream stream(&file);
    QString str;

    QVector<double> X, Y;

    int dotsCount = 0;

    const QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssDisc);

    bool isOK = true;;

    while (!file.atEnd())
    {
        QString line = file.readLine();
        qDebug() << line;
        int countPoint = line.toInt(&isOK);
        if (isOK)
        {
            if (countPoint == 20)
            {
                qDebug() << countPoint;
            }
            QVector<QCPCurveData> curveData(countPoint);
            for (int i=0;i<countPoint;++i)
            {
                str = file.readLine();
                qDebug() << str;
                QStringList slist = str.split(' ', QString::SkipEmptyParts);
                if (slist.size()!=2)
                {
                    QMessageBox::warning(this, "Ошибка", "Не верное количество точек");

                    ui->customPlot->clearGraphs();
                    ui->customPlot->replot();
                    return;
                }

                bool convert = true;
                double x = slist[0].toDouble(&convert);
                if (!convert)
                {
                    QMessageBox::warning(this, "Ошибка", "Не корректная запись");

                    ui->customPlot->clearGraphs();
                    ui->customPlot->replot();
                    return;
                }

                convert = true;
                double y = slist[1].toDouble(&convert);
                if (!convert)
                {
                    QMessageBox::warning(this, "Ошибка", "Не корректная запись");

                    ui->customPlot->clearGraphs();
                    ui->customPlot->replot();
                    return;
                }

                curveData[i] = QCPCurveData(i, x, y);
            }

            QCPCurve *curve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
            curveVector.append(curve);
            curve->setScatterStyle(style);

            curve->data()->set(curveData, true);

            ui->customPlot->replot();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Не корректная запись");

            ui->customPlot->clearGraphs();
            ui->customPlot->replot();
            return;
        }

    }

    file.close();

    xRange = QPair<double, double>(ui->customPlot->xAxis->range().lower, ui->customPlot->xAxis->range().upper);
    yRange = QPair<double, double>(ui->customPlot->yAxis->range().lower, ui->customPlot->yAxis->range().upper);
}

void MainWindow::plotRepaint(int delta)
{
    ui->customPlot->xAxis->setRange(xRange.first - delta * plotShift,
                                    xRange.second + delta * plotShift);
    ui->customPlot->yAxis->setRange(yRange.first - delta * plotShift,
                                    yRange.second + delta * plotShift);
    ui->customPlot->replot();

    xRange = QPair<double, double>(ui->customPlot->xAxis->range().lower, ui->customPlot->xAxis->range().upper);
    yRange = QPair<double, double>(ui->customPlot->yAxis->range().lower, ui->customPlot->yAxis->range().upper);
}

void MainWindow::plotScaling(double scale)
{
    ui->customPlot->xAxis->setRange(xRange.first * scale, xRange.second * scale);
    ui->customPlot->yAxis->setRange(yRange.first * scale, yRange.second * scale);
    ui->customPlot->replot();
}

void MainWindow::delete_curveVector()
{
    for (int i=0; i<curveVector.size(); ++i)
    {
        delete curveVector[i];
    }
    curveVector.resize(0);
}
