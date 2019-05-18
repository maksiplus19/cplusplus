#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_button_clicked()
{
    int n = ui->add_spin->value();
    tree.add(n);
    ui->textBrowser->append("Добавлено " + QString::number(n));
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    for (auto el : tree.all())
    {
        str.append(" " + QString::number(el));
    }
    ui->textBrowser->append(str);
}

void MainWindow::on_count_button_clicked()
{
    QString str = "<p>\"Считалка\"<\p>";
    for (auto el : tree.counting(ui->count_spin->value()))
    {
        str.append(" " + QString::number(el));
    }
    ui->textBrowser->append(str);
}

void MainWindow::on_rand_button_clicked()
{
    int n = ui->rand_spin->value();
    for (int i = 0; i<n; ++i)
    {
        tree.add(rand() % 1000);
    }
}
