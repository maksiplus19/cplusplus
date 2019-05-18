#include "addprojectdialog.h"
#include "ui_addprojectdialog.h"

addProjectDialog::addProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addProjectDialog)
{
    ui->setupUi(this);
    this->name = "";
}

addProjectDialog::~addProjectDialog()
{
    delete ui;
}

void addProjectDialog::on_buttonBox_accepted()
{
    this->name = this->ui->lineEdit->text();
}
