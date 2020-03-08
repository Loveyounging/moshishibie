#include "form_threshold.h"
#include "ui_form_threshold.h"
#include <QImage>
#include <QLabel>


Form_Threshold::Form_Threshold(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Threshold)
{
    ui->setupUi(this);
    ui->spinBox->setRange(0,255);
    ui->spinBox->setValue(0);
    ui->spinBox->setSingleStep(1);
    b = false;
    m_porigon = new QImage(path);
    m_pshiftimg = new QImage(path);
}

Form_Threshold::~Form_Threshold()
{
    delete m_porigon;
    delete m_pshiftimg;
    delete ui;
}



//确认
void Form_Threshold::on_pushButton_clicked()
{
    int threshold = ui->spinBox->value();
    int height = m_pshiftimg->height();
    int width = m_pshiftimg->width();
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(qRed(m_porigon->pixel(x,y)) < threshold){
                m_pshiftimg->setPixel(x,y,0x000000);
            }else m_pshiftimg->setPixel(x,y,0xFFFFFF);
        }
    }
    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*m_pshiftimg));
    label->show();
    //emit sendLabel(label);
}

//取消
void Form_Threshold::on_pushButton_2_clicked()
{
    this->close();
}
