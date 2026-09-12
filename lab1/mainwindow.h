#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QString>


class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *event) override;
    private slots:
        void onActionWork1();
        void onActionWork2();
    private:
        int work1Number = -1;
        QString work2Text;
};


#endif