#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEBUG

#include <QMainWindow>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QString"
#include "QFile"
#include "QDebug"
#include "QMessageBox"
#include "QVector"
#include "QList"
#include "QSqlRelationalTableModel"

#include "measure.h"

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
    void on_BT_load_file_clicked();

    void on_BT_save_clicked();

    void on_BT_edit_mode_clicked(bool checked);

    void on_draw_graph_clicked();

    void on_add_filter_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel* model;
    QSqlRelation relation;
    QSqlQuery query;

    QVector<QVector<measure>> data;

    bool load_file(QString fname);
};

#endif // MAINWINDOW_H
