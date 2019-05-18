#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "QList"
#include "QDebug"
#include "memory"
#include "QColor"
#include "QColorDialog"

#include "figure.h"
#include "ellipse.h"
#include "square.h"
#include "rhomb.h"

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
    void on_scale_spinBox_valueChanged(int arg1);

    void on_add_ellips_clicked();

    void on_del_last_clicked();

    void on_move_button_clicked();

    void on_rhomb_radioButton_toggled(bool checked);

    void on_sqsare_radioButton_toggled(bool checked);

    void on_ellips_radioButton_toggled(bool checked);

    void draw_ellipse();
    void draw_square();
    void draw_rhomb();

private:
    int scale;
    QSize scene_size;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<std::shared_ptr<figure>> figures;
    QPen grid_pen = QPen(QColor(0, 0, 0, 10));

    void draw_chords();
    void draw_grid();
};

#endif // MAINWINDOW_H
