#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("measure_db");
    db.setUserName("user1");
    db.setPassword("user1");

    if (!db.open())
    {
        exit(1);
    }
    query = QSqlQuery(db);

    model = new QSqlRelationalTableModel(this);
    model->setTable("mes_table");
    model->select();
    ui->TV_table->setModel(model);

    relation = QSqlRelation("city_table", "city_id", "city_name");
    model->setRelation(1, relation);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->TV_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot->legend->setVisible(true);
    ui->plot->legend->setBrush(QBrush(QColor(255, 255, 255, 150)));
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
    ui->plot->yAxis->setRange(0, 30);
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

bool MainWindow::load_file(QString fname)
{
//    INSERT INTO `measuring_table` (`temperature`, `date`, `city_table_city_id`) VALUES ('21,5', '01 июл 2010', '2');
//    C:\Qt\Projects\lab03sem4\f
    if (fname.isEmpty()) return true;
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QString data = QString(file.readAll());
    file.close();

    QStringList l = data.split("\r\n");
    for(QString el: l)
    {
        // температура, дата, id города
        QStringList rec = el.split(',');
        if (rec.size() != 2)
        {
#ifdef DEBUG
            qDebug() << "Wrong record ";
            for (auto r: rec)
            {
                qDebug() << r;
            }
#endif
            continue;
        }

        query.prepare("INSERT INTO `mes_table` (temperature, city_table_city_id) VALUES (?, ?)");
#ifdef DEBUG
        qDebug() << rec;
#endif
        query.addBindValue(rec[0]);
        query.addBindValue(rec[1]);
        bool exec = query.exec();

        QSqlError err = query.lastError();
#ifdef DEBUG
        qDebug() << err.driverText() << err.text();
#endif

        if (!exec) return false;
    }
    model->select();
    return true;
}

void MainWindow::on_BT_load_file_clicked()
{
    if (!load_file(ui->LE_file_name->text()))
    {
        QMessageBox::information(this, "Ошибка", "Проиошла ошибка при загрузке файла");
    }
}

void MainWindow::on_BT_save_clicked()
{
#ifdef DEBUG
    qDebug() << model->lastError().text();
#endif
    model->submitAll();
    model->select();
#ifdef DEBUG
    qDebug() << model->lastError().text();
#endif
}

void MainWindow::on_BT_edit_mode_clicked(bool checked)
{
#ifdef DEBUG
    qDebug() << "Before: " << model->lastError().text();
#endif
    if (checked)
    {
        model->setRelation(1, QSqlRelation());
        model->select();
        ui->TV_table->setEditTriggers(QAbstractItemView::DoubleClicked  |
                                      QAbstractItemView::EditKeyPressed |
                                      QAbstractItemView::AnyKeyPressed  );
    }
    else
    {
        model->submitAll();
        model->setRelation(1, relation);
        model->select();
        ui->TV_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
#ifdef DEBUG
    qDebug() << "After: " << model->lastError().text();
#endif
}

void MainWindow::on_draw_graph_clicked()
{
    data.clear();
    ui->plot->clearGraphs();
    QVector<QString> city_name;
    if (model->filter().isEmpty())
        query.exec("SELECT * FROM `city_table`");
    else
    {
        QString s = "SELECT * FROM `city_table` WHERE city_id="+model->filter().split('=')[1];
        query.exec(s);
        qDebug() << query.lastError().text();
    }
    while(query.next())
    {
        city_name.push_back(query.value(1).toString());
        data.push_back(QVector<measure>());
    }
    for (int i = 1; i <= data.size(); ++i)
    {
        query.exec("SELECT * FROM `mes_table` INNER JOIN `city_table` ON city_table_city_id=city_table.city_id "
                   "WHERE city_table.city_name='" + city_name[i-1] + "'");
        while (query.next())
        {
            data[i-1].push_back(measure(query.value(0).toDouble(), i, city_name[i-1]));
        }
    }

    for (int i = 1; i <= data.size(); ++i)
    {
        if (data[i-1].isEmpty()) continue;

        QColor color(QColor::colorNames()[rand() % QColor::colorNames().size()]);
        color.setAlpha(100);
        QBrush brush(color);
        color.setAlpha(255);
        QPen pen(color);
        pen.setWidth(2);

        ui->plot->addGraph();
        ui->plot->graph(i-1)->setName(data[i-1].first().get_name());
        ui->plot->graph(i-1)->setPen(pen);
        ui->plot->graph(i-1)->setBrush(brush);

        int dots_count = data[i-1].size();
        QVector<QCPGraphData> dots(dots_count);
        for (int j = 0; j < dots_count; ++j)
        {
            dots[j].key = j+1;
            dots[j].value = data[i-1][j].get_temp();
#ifdef DEBUG
            qDebug() << dots[j].value;
#endif
        }
        ui->plot->graph(i-1)->data()->set(dots, true);
    }
    ui->plot->rescaleAxes(true);
    ui->plot->yAxis->rescale();
    ui->plot->xAxis->rescale();
    ui->plot->replot();
}

void MainWindow::on_add_filter_clicked()
{
#ifdef DEBUG
    qDebug() << model->filter();
#endif
    model->setFilter("city_table_city_id="+QString::number(ui->SB_city_id_filter->value()));
}

void MainWindow::on_pushButton_clicked()
{
#ifdef DEBUG
    qDebug() << model->filter();
#endif
    model->setFilter("");
}
