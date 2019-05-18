/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *addCurveAction;
    QAction *delCurveAction;
    QAction *exitAction;
    QWidget *centralWidget;
    QListWidget *curveList;
    QCustomPlot *customPlot;
    QLineEdit *edit;
    QTextBrowser *invariants;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuRhbdst;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(826, 766);
        addCurveAction = new QAction(MainWindow);
        addCurveAction->setObjectName(QStringLiteral("addCurveAction"));
        delCurveAction = new QAction(MainWindow);
        delCurveAction->setObjectName(QStringLiteral("delCurveAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        curveList = new QListWidget(centralWidget);
        curveList->setObjectName(QStringLiteral("curveList"));
        curveList->setGeometry(QRect(9, 9, 200, 600));
        curveList->setMinimumSize(QSize(200, 100));
        curveList->setMaximumSize(QSize(200, 600));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(215, 9, 600, 600));
        edit = new QLineEdit(centralWidget);
        edit->setObjectName(QStringLiteral("edit"));
        edit->setGeometry(QRect(9, 620, 806, 31));
        edit->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(8);
        edit->setFont(font);
        invariants = new QTextBrowser(centralWidget);
        invariants->setObjectName(QStringLiteral("invariants"));
        invariants->setGeometry(QRect(9, 660, 806, 61));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 826, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuRhbdst = new QMenu(menuBar);
        menuRhbdst->setObjectName(QStringLiteral("menuRhbdst"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuRhbdst->menuAction());
        menu->addAction(exitAction);
        menuRhbdst->addAction(addCurveAction);
        menuRhbdst->addSeparator();
        menuRhbdst->addAction(delCurveAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\232\321\200\320\270\320\262\321\213\320\265 \320\262\321\202\320\276\321\200\320\276\320\263\320\276 \320\277\320\276\321\200\321\217\320\264\320\272\320\260", nullptr));
        addCurveAction->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\321\202\320\270\321\214 \320\272\321\200\320\270\320\262\321\203\321\216", nullptr));
        delCurveAction->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\321\203\321\216 \320\272\321\200\320\270\320\262\321\203\321\216", nullptr));
        exitAction->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        edit->setInputMask(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menuRhbdst->setTitle(QApplication::translate("MainWindow", "\320\232\321\200\320\270\320\262\321\213\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
