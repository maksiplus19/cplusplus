#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _socket = new QTcpSocket(this);

    connect(_socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
    connect(_socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    _socket->connectToHost(QHostAddress::LocalHost, 33333);
}

MainWindow::~MainWindow()
{
    _socket->close();
    delete ui;
}

void MainWindow::onSocketReadyRead()
{
    QDataStream in(_socket);
    matrix res(4);
    in >> res;
    ui->textBrowser->append("Новая матрица ");
    ui->textBrowser->append(res);
}

void MainWindow::on_sendBT_clicked()
{
    matrix m(4);
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
        {
            QSpinBox* spin = this->findChild<QSpinBox*>("m"+QString::number(i)+QString::number(j));
            m.set(i-1, j-1, spin->value());
        }
    }
    qDebug() << m.get_matrix();
    QDataStream out(_socket);
    out << m;
}
