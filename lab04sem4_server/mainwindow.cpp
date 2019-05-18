#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::LocalHost, 33333) && server_status==0)
    {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        ui->textBrowser->append(tcpServer->errorString());
    }
    else
    {
        server_status=1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textBrowser->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }
}

MainWindow::~MainWindow()
{
    if(server_status==1)
    {
        foreach(int i,SClients.keys())
        {
            qDebug() << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        tcpServer->close();
        ui->textBrowser->append(QString::fromUtf8("Сервер остановлен!"));
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status=0;
    }

    delete ui;
}

void MainWindow::newuser()
{
    if(server_status==1)
    {
        QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        SClients[idusersocs]=clientSocket;
        connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));
    }
}

void MainWindow::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QDataStream os(clientSocket);
    matrix m(4);

    os >> m;
    qDebug() << m.get_matrix();
    ui->textBrowser->append("\n");

    for (int i = 0; i < m.size(); ++i)
    {
        QString str;
        for (int j = 0; j<m.size(); ++j)
        {
            str.append(" " + QString::number(m.at(i, j)));
        }
        ui->textBrowser->append(str);
        str = "";
    }

    if (m.isSorted())
    {
        int sumBefore = m.sum();
        m.replace();
        int sumAfter = m.sum();
        os << sumBefore - sumAfter;
        ui->textBrowser->append("Изменение суммы " + QString::number(sumBefore - sumAfter));
    }
    else
    {
        os << 0;
    }
}

