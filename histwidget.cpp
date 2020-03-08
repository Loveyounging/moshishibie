#include "histwidget.h"
#include "statistics.h"


HistWidget::HistWidget(QImage& img,Type type,QWidget *parent) : QWidget(parent)
{
    pr = pg = pb = nullptr;
    switch (type) {
    case GRAY:
        pr = new int[256];
        break;
    case RGB:
        pr = new int[256];
        pg = new int[256];
        pb = new int[256];
        break;
    }
    Statistics::count(img,pr,0);
    Statistics::count(img,pg,1);
    Statistics::count(img,pb,2);
}

HistWidget::~HistWidget()
{
    if(pr != nullptr)delete[] pr;
    pr = nullptr;
    if(pg != nullptr)delete[] pg;
    pg = nullptr;
    if(pb != nullptr)delete[] pb;
    pb = nullptr;
}



void HistWidget::paintEvent(QPaintEvent *event)
{

}
