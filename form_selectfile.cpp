#include "form_selectfile.h"
#include "ui_form_selectfile.h"

Form_SelectFile::Form_SelectFile(QStringList& list,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_SelectFile)
{
    ui->setupUi(this);
    ui->listWidget->addItems(list);
    ui->comboBox->addItem("GRAY");
    ui->comboBox->addItem("RBG");
}



void Form_SelectFile::getFilenameAndType(QStringList &list, QString &filename, bool &b)
{
    Form_SelectFile form(list);

}

Form_SelectFile::~Form_SelectFile()
{
    delete ui;
}

QString Form_SelectFile::getfilename()
{
    return ui->listWidget->currentItem()->text();
}

void Form_SelectFile::on_pushButton_clicked()
{

}

void Form_SelectFile::on_pushButton_2_clicked()
{

}
