#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <map>
#include <QString>
#include <QDialog>
#include <QAbstractItemModel>


#include "qcustomplot.h"
#include "curveso.h"
#include "addprojectdialog.h"
//#include "projectmodel.h"

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
    void on_edit_editingFinished();

    void on_exitAction_triggered();

    void on_addCurveAction_triggered();

    void on_curveList_itemClicked(QListWidgetItem *item);

    void on_delCurveAction_triggered();

    void show_menu(const QPoint);

    void on_curveList_itemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    addProjectDialog *addDialog;
    std::map<QString, CurveSO> proj_map;
//    ProjectModel *projectModel;
    QCPCurve *cpCurve;
    CurveSO curve;

    Curve::curveStruct get_curve_struct(QString);
};

#endif // MAINWINDOW_H
