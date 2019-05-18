#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "binary_tree.h"

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
    void on_add_button_clicked();

    void on_pushButton_clicked();

    void on_count_button_clicked();

    void on_rand_button_clicked();

private:
    Ui::MainWindow *ui;
    binary_tree<int> tree;
};

#endif // MAINWINDOW_H
