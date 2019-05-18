/********************************************************************************
** Form generated from reading UI file 'addprojectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROJECTDIALOG_H
#define UI_ADDPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addProjectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addProjectDialog)
    {
        if (addProjectDialog->objectName().isEmpty())
            addProjectDialog->setObjectName(QStringLiteral("addProjectDialog"));
        addProjectDialog->resize(233, 101);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addProjectDialog->sizePolicy().hasHeightForWidth());
        addProjectDialog->setSizePolicy(sizePolicy);
        addProjectDialog->setMaximumSize(QSize(233, 101));
        verticalLayout = new QVBoxLayout(addProjectDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(addProjectDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(addProjectDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(addProjectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(addProjectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), addProjectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), addProjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(addProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *addProjectDialog)
    {
        addProjectDialog->setWindowTitle(QApplication::translate("addProjectDialog", "\320\235\320\276\320\262\321\213\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        label->setText(QApplication::translate("addProjectDialog", "\320\222\320\222\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addProjectDialog: public Ui_addProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROJECTDIALOG_H
