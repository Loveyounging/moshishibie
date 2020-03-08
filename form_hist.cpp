#include "form_hist.h"
#include "ui_form_hist.h"
#include "statistics.h"
#include <QPainter>
#include <QMouseEvent>

Form_Hist::Form_Hist(QImage& img,Type type,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Hist)
{
    ui->setupUi(this);
    currentIndexOfTable = 0;
    isShowPos = false;
    pr = pg = pb = nullptr;
    m_size = img.height() * img.width();
    m_type = type;
    switch (type) {
    case GRAY:
        ui->PB_b->setEnabled(false);
        ui->PB_r->setEnabled(false);
        ui->PB_g->setEnabled(false);
        pr = new int[256];
        Statistics::count(img,pr,0);
        break;
    case RGB:
        pr = new int[256];
        pg = new int[256];
        pb = new int[256];
        Statistics::count(img,pr,0);
        Statistics::count(img,pg,1);
        Statistics::count(img,pb,2);
        break;
    }
    m_maxB = m_maxG = m_maxR = 0;
    for(int i = 0; i < 256;i++){
        m_maxR = m_maxR > pr[i] ? m_maxR: pr[i];
    }
    if(pg != nullptr && pb != nullptr){
        for(int i = 0; i < 256;i++){
            m_maxG = m_maxG > pg[i] ? m_maxG: pg[i];
            m_maxB = m_maxB > pb[i] ? m_maxB: pb[i];
        }
    }
    this->setMouseTracking(true);
}

Form_Hist::~Form_Hist()
{
    delete ui;
    if(pr != nullptr)delete[] pr;
    pr = nullptr;
    if(pg != nullptr)delete[] pg;
    pg = nullptr;
    if(pb != nullptr)delete[] pb;
    pb = nullptr;
}

void Form_Hist::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    const int STEPX = 2;
    const int XBegin = 64;
    const int YBegin = 430;
    switch (currentIndexOfTable) {
    case 0:
        if(m_type == GRAY)
        {
            const float STEPY = 300 / float(m_maxR);
            for(int i = 0 ; i < 256 ; i++){
                int length = pr[i] * STEPY;
                painter.drawLine(XBegin + i * 2, YBegin , XBegin + i * 2,YBegin - length);
                painter.drawLine(XBegin + i * 2 + 1, YBegin , XBegin + i * 2 + 1,YBegin - length);
            }
            if(isShowPos){
                painter.setPen(QColor(34,34,221));
                painter.drawText(cursorx,cursory,QString::number(cursorx / 2 - 32) + "," + QString::number(pr[cursorx / 2 - 32]));
            }
         }else if(m_type == RGB){
            int max = m_maxR > m_maxG ? m_maxR : m_maxG;
            max = max > m_maxB ? max : m_maxB;
            const float STEPY = 300 / float(max);
            painter.setPen(QColor(255,0,0));
            for(int i = 0; i < 255; i ++){
                int length1 = pr[i] * STEPY;
                int length2 = pr[i+1] * STEPY;
                painter.drawLine(i * STEPX + XBegin,YBegin - length1,(i + 1 ) * STEPX + XBegin,YBegin - length2);
            }
            painter.setPen(QColor(0,255,0));
            for(int i = 0; i < 255; i ++){
                int length1 = pg[i] * STEPY;
                int length2 = pg[i+1] * STEPY;
                painter.drawLine(i * STEPX + XBegin,YBegin - length1,(i + 1 ) * STEPX + XBegin,YBegin - length2);
            }
            painter.setPen(QColor(0,0,255));
            for(int i = 0; i < 255; i ++){
                int length1 = pb[i] * STEPY;
                int length2 = pb[i+1] * STEPY;
                painter.drawLine(i * STEPX + XBegin,YBegin - length1,(i + 1 ) * STEPX + XBegin,YBegin - length2);
            }


        }
        break;
    case 1:
    {
        const float STEPY = 300 / float(m_maxR);
        painter.setPen(QColor(255,0,0));
        for(int i = 0 ; i < 256 ; i++){
            int length = pr[i] * STEPY;
            painter.drawLine(XBegin + i * 2, YBegin , XBegin + i * 2,YBegin - length);
            painter.drawLine(XBegin + i * 2 + 1, YBegin , XBegin + i * 2 + 1,YBegin - length);
        }
        if(isShowPos){
            painter.setPen(QColor(0,0,0));
            painter.drawText(cursorx,cursory,QString::number(cursorx / 2 - 32) + "," + QString::number(pr[cursorx / 2 - 32]));
        }
    }
        break;
    case 2:
    {
        const float STEPY = 300 / float(m_maxG);
        painter.setPen(QColor(0,255,0));
        for(int i = 0 ; i < 256 ; i++){
            int length = pg[i] * STEPY;
            painter.drawLine(XBegin + i * 2, YBegin , XBegin + i * 2,YBegin - length);
            painter.drawLine(XBegin + i * 2 + 1, YBegin , XBegin + i * 2 + 1,YBegin - length);
        }
        if(isShowPos){
            painter.setPen(QColor(0,0,0));
            painter.drawText(cursorx,cursory,QString::number(cursorx / 2 - 32) + "," + QString::number(pg[cursorx / 2 - 32]));
        }
    }
        break;
    case 3:
    {
        const float STEPY = 300 / float(m_maxB);
        painter.setPen(QColor(0,0,255));
        for(int i = 0 ; i < 256 ; i++){
            int length = pb[i] * STEPY;
            painter.drawLine(XBegin + i * 2, YBegin , XBegin + i * 2,YBegin - length);
            painter.drawLine(XBegin + i * 2 + 1, YBegin , XBegin + i * 2 + 1,YBegin - length);
        }
        if(isShowPos){
            painter.setPen(QColor(0,0,0));
            painter.drawText(cursorx,cursory,QString::number(cursorx / 2 - 32) + "," + QString::number(pb[cursorx / 2 - 32]));
        }
    }
        break;
    }

}

void Form_Hist::mouseMoveEvent(QMouseEvent *event)
{
    if(event->x() <= 576 && event->x() >= 64 && event->y() <= 430 && event->y() >= 130)
    {
        showPos(event->x(),event->y());
        this->repaint();
    }
    else isShowPos = false;
}

void Form_Hist::showPos(int x, int y)
{
    cursorx = x;
    cursory = y;
    isShowPos = true;
}



void Form_Hist::on_PB_rgb_clicked()
{
    currentIndexOfTable = 0;
    this->repaint();
}

void Form_Hist::on_PB_r_clicked()
{
    currentIndexOfTable = 1;
    this->repaint();
}

void Form_Hist::on_PB_g_clicked()
{
    currentIndexOfTable = 2;
    this->repaint();
}

void Form_Hist::on_PB_b_clicked()
{
    currentIndexOfTable = 3;
    this->repaint();
}
