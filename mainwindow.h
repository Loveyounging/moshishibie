#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void openImage(const QString& str);
private slots:
    void on_PB_open_clicked();

    void on_PB_hist_clicked();

    void on_PB_yuzhifa_clicked();

    void addWidget(QWidget* w);
private:
    Ui::MainWindow *ui;
    QStringList m_file;
    QVector<QWidget*> m_pwidget;
};

#endif // MAINWINDOW_H
