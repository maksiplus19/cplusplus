#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAbstractItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems | QCP::iSelectPlottables);
    ui->curveList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->curveList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_menu(const QPoint)));
    cpCurve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_edit_editingFinished()
{
    if (ui->curveList->count()) ui->curveList->currentItem()->setData(Qt::DisplayRole, QVariant(ui->edit->text()));
    std::vector<Curve::curveStruct> vector;
    QString str = ui->edit->text();
    if (str.indexOf('=')<0 || str.indexOf('=') == str.size()-1) return;
    QString for_parse = "";
    bool after_eq = false;
    for (int i=0;i<str.size();++i)
    {
        if (str.at(i) == '*') continue;
        if (str.at(i) == 'x' || str.at(i) == 'y' || str.at(i).isDigit() || str.at(i) == '^')
        {
            for_parse += str.at(i);
        }
        else if (str.at(i) == '=' || str.at(i) == '-' || str.at(i) == '+')
            {
                Curve::curveStruct curve = get_curve_struct(for_parse);

                QChar c = 0;
                if (str.at(i) != '=') c = str.at(i);
                if (curve.arg == "f")
                    curve;
                if (after_eq)
                    curve.coef *= -1;

                vector.push_back(curve);

                for_parse = "";
                if (c != 0) for_parse += c;
                if (str.at(i) == '=') after_eq = true;
            }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Не известный символ");
            return;
        }
    }

    if (! for_parse.isEmpty()) {
        Curve::curveStruct curve = get_curve_struct(for_parse);
        if (after_eq) curve.coef *= -1;
        vector.push_back(curve);
    }

    double a11 = 0, a12 = 0, a13 = 0, a22 = 0, a23 = 0, a33 = 0;
    for(auto curve: vector)
    {
        if (curve.arg == 'f') a33 += curve.coef;
        else
            if (curve.arg == "x")
            {
                if (curve.deg == 1) a13 += curve.coef;
                else if (curve.deg == 2) a11 += curve.coef;
                else
                {
                    std::string s = "Unkown degree " + std::to_string(curve.deg);
                    throw std::runtime_error(s.c_str());
                }
            }
            else
                if (curve.arg == "y")
                {
                    if (curve.deg == 1) a23 += curve.coef;
                    else if (curve.deg == 2) a22 += curve.coef;
                    else
                    {
                        std::string s = "Unkown degree " + std::to_string(curve.deg);
                        throw std::runtime_error(s.c_str());
                    }
                }
                else
                    if (curve.arg == "xy" || curve.arg == "yx")
                    {
                        if (curve.deg == 1) a12 += curve.coef;
                        else
                        {
                            std::string s = "Unkown degree " + std::to_string(curve.deg);
                            throw std::runtime_error(s.c_str());
                        }
                    }
        else
        {
            std::string s = "Unkown arg " + curve.arg.toStdString();
            throw std::runtime_error(s.c_str());
        }
    }
    curve = CurveSO(a11, a12, a13, a22, a23, a33, ui->edit->text());
    auto p = curve.count(ui->customPlot->xAxis->range().lower,
                              ui->customPlot->xAxis->range().upper, 0.01);

    cpCurve->setName(curve.get_name());
    qDebug() << curve.get_type();
    cpCurve->setData(p.first, p.second);
    ui->customPlot->replot();

    auto map = curve.get_invariants();
    ui->invariants->clear();
    ui->invariants->append(QString().fromStdString("<b>Delta</b> = " + std::to_string(map["delta"]) + " <b>D</b> = " + std::to_string(map["D"]) +
            " <b>I</b> = " + std::to_string(map["I"]) + " <b>B</b> = " + std::to_string(map["B"])));
}

void MainWindow::on_exitAction_triggered()
{
    this->close();
}

Curve::curveStruct MainWindow::get_curve_struct(QString s)
{
    Curve::curveStruct curve;
    curve.coef=0;
    curve.arg="";
    curve.deg=0;
    bool isMinus = false;
    if (s[0]=='-')
    {
        isMinus = true;
        s.remove(0,1);
    }
    if (s[0]=='+') s.remove(0,1);
    int index = s.indexOf("xy");
    if (index < 0) index = s.indexOf("yx");
    if (index >= 0) curve.arg = "xy";
    if (index < 0) index = s.indexOf('x');
    if (index < 0) index = s.indexOf('y');
    if (index < 0)
    {
        curve.coef = s.toDouble();
        curve.deg = 0;
        curve.arg = 'f';
        qDebug() << "struct = " << curve.coef << curve.arg << '^' << curve.deg;
        return curve;
    }
    if (curve.arg.isEmpty()) curve.arg = s.at(index);
    QString arg = curve.arg;
    bool ok = true;
    double coef = s.split(arg)[0].toDouble(&ok);
    if (!index) coef = 1;
    else if (!ok)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка преобразования числа коэффицента\n" + s +
                             "Коэффицент будет равен 1");
        return curve;
    }
    ok = true;
    double deg;
    if (curve.arg != "xy" && s.split('^').size()!=1)
        deg = s.split(QString(arg)+"^")[1].toInt(&ok);
    else
        deg = 1;
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка преобразования числа степени\n" + s + "Степень будет равна 1");
        deg = 1;
    }
    curve.coef = isMinus ? -coef: coef;
    curve.deg = deg>2 ? 2 : deg;
    qDebug() << "struct = " << curve.coef << curve.arg << '^' << curve.deg;
    return curve;
}

void MainWindow::on_addCurveAction_triggered()
{
    if (curve)
        proj_map.insert(std::pair<QString, CurveSO>(curve.get_name(), curve));
    QListWidgetItem *item = new QListWidgetItem(QString(" "));
    ui->curveList->addItem(item);
    ui->curveList->setCurrentItem(item);
}

void MainWindow::on_curveList_itemClicked(QListWidgetItem *item)
{
    ui->edit->setText(item->data(Qt::DisplayRole).toString());
    on_edit_editingFinished();
}

void MainWindow::on_delCurveAction_triggered()
{
    if (! ui->curveList->count()) return;
    QString item = ui->curveList->currentItem()->data(Qt::DisplayRole).toString();
    delete ui->curveList->currentItem();
    if (ui->curveList->count()) ui->curveList->setCurrentRow(0);
}

void MainWindow::show_menu(const QPoint pos)
{
    QMenu menu(this);
    menu.addAction(ui->addCurveAction);
    menu.addAction(ui->delCurveAction);
    menu.exec(ui->curveList->mapToGlobal(pos));
}

void MainWindow::on_curveList_itemChanged(QListWidgetItem *item)
{
    ui->edit->setText(item->data(Qt::DisplayRole).toString());
    on_edit_editingFinished();
}
