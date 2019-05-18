#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTcpSocket"
#include "QString"
#include "myclient.h"
#include "QHostAddress"
#include "QBitArray"
#include "QDataStream"
#include "matrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket* _socket;
    quint16 _blockSize;
    QString _name;
//    QMatrix4x4 matrix;

private slots:
    void onSocketReadyRead();
    void on_sendBT_clicked();
};

#endif // MAINWINDOW_H
