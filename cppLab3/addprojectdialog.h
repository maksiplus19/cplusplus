#ifndef ADDPROJECTDIALOG_H
#define ADDPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class addProjectDialog;
}

class addProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addProjectDialog(QWidget *parent = 0);
    QString name;
    ~addProjectDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addProjectDialog *ui;
};

#endif // ADDPROJECTDIALOG_H
