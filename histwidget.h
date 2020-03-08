#ifndef HISTWIDGET_H
#define HISTWIDGET_H

#include <QWidget>


enum Type{GRAY,RGB};

class HistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistWidget(QImage& img,Type type = RGB,QWidget *parent = nullptr);
    ~HistWidget();
protected:
    void paintEvent(QPaintEvent* event);
signals:

public slots:
private:
    int *pr,*pg,*pb;
};

#endif // HISTWIDGET_H
