#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
class QImage;
class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);
    //0 for R,1 for G,2 for B
    static float average(QImage& img,int rgb);
    //0 for R,1 for G,2 for B
    static void count(QImage& img,int*& p,int rgb);
signals:

public slots:
};

#endif // STATISTICS_H
