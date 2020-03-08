#include "statistics.h"

#include <QImage>
#include <QDebug>

Statistics::Statistics(QObject *parent) : QObject(parent)
{

}

float Statistics::average(QImage &img, int rgb)
{
    if(rgb > 2 || rgb < 0)return 0.0;
    int step = 4;
    int sum = 0;
    int size = img.width() * img.height();
    for(int i = 0; i < size; i++ ){
        sum += img.bits()[step * i];
    }
    qDebug() << float(sum) / float(size);
    return float(sum) / float(size);
}

void Statistics::count(QImage &img, int *&p, int rgb)
{
    for( int i = 0; i < 256; i++){
        p[i] = 0;
    }
    int height = img.height();
    int width = img.width();
    switch (rgb) {
    case 0:
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                p[qRed(img.pixel(x,y))]++;
            }
        }
        break;
    case 1:
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                p[qGreen(img.pixel(x,y))]++;
            }
        }
        break;
    case 2:
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                p[qBlue(img.pixel(x,y))]++;
            }
        }
        break;
    }
    for( int i = 0; i < 256; i++){
        qDebug() << i << ":" << p[i];
    }
}

