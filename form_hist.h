#ifndef FORM_HIST_H
#define FORM_HIST_H

#include <QWidget>

enum Type{GRAY,RGB};

namespace Ui {
class Form_Hist;
}

class Form_Hist : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Hist(QImage& img,Type type = RGB,QWidget *parent = nullptr);
    ~Form_Hist();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void showPos(int x,int y);
private slots:
    void on_PB_rgb_clicked();

    void on_PB_r_clicked();

    void on_PB_g_clicked();

    void on_PB_b_clicked();

private:
    Ui::Form_Hist *ui;
private:
    int *pr,*pg,*pb;
    int m_size;
    int m_maxR,m_maxG,m_maxB;
    Type m_type;
    int currentIndexOfTable;
    bool isShowPos;
    int cursorx,cursory;
};

#endif // FORM_HIST_H
