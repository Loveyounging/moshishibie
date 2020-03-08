#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statistics.h"


#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include "form_threshold.h"
#include "form_hist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->RB_GRAY->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    for(auto i = m_pwidget.begin(); i != m_pwidget.end();){
        auto j = i;
        i++;
        delete j;
    }
}

void MainWindow::openImage(const QString &str)
{
    QLabel* p = new QLabel();
    QImage pimg = QImage(str);
    qDebug() << pimg.format();
    p->setPixmap(QPixmap::fromImage(pimg));
    m_pwidget.push_back(p);
    p->show();
}

void MainWindow::on_PB_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("open"),tr(""),"JPEG Files(*.jpg);;PNG Files(*.png)");
    if(filename == "")return;
    m_file.push_back(filename);
    ui->listWidget->addItem(m_file.back());
    qDebug() << m_file.back();
    openImage(m_file.back());
}

void MainWindow::on_PB_hist_clicked()
{
    if(m_file.empty() || ui->listWidget->currentItem() == nullptr)return;
    QImage img(ui->listWidget->currentItem()->text());
    m_pwidget.push_back(new Form_Hist(img,ui->RB_RGB->isChecked()? RGB : GRAY));
    m_pwidget.back()->show();
}

void MainWindow::on_PB_yuzhifa_clicked()
{
    if(m_file.empty() || ui->listWidget->currentItem() == nullptr)return;
    //QImage* origon = new QImage(ui->listWidget->currentItem()->text());
    //QImage* shift = new QImage(ui->listWidget->currentItem()->text());
    Form_Threshold* form = new Form_Threshold(ui->listWidget->currentItem()->text());
    connect(form,SIGNAL(sendLabel(QWidget*)),this,SLOT(addWidget(QWidget*)));
    m_pwidget.push_back(form);
    m_pwidget.back()->show();
    disconnect(form,SIGNAL(sendLabel(QWidget*)),this,SLOT(addWidget(QWidget*)));

}

void MainWindow::addWidget(QWidget *w)
{
    m_pwidget.push_back(w);
    m_pwidget.back()->show();
}
