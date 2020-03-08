#ifndef FORM_THRESHOLD_H
#define FORM_THRESHOLD_H

#include <QWidget>

namespace Ui {
class Form_Threshold;
}

class Form_Threshold : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Threshold(QString path,QWidget *parent = nullptr);
    ~Form_Threshold();


signals:
    void sendLabel(QWidget*);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form_Threshold *ui;
    QImage* m_porigon;
    QImage* m_pshiftimg;
    bool b;
};

#endif // FORM_THRESHOLD_H
