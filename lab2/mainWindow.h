
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "shape.h"

class QPaintEvent;
class QMouseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
 
private: 
 bool isDragging = false;
 QPoint startPt;
 QPoint endPt;
 QActionGroup *shapeGroup = nullptr;

 static const int N = 116;
 Shape* currentShape = nullptr;
 Shape *pcshape[N] = {nullptr};
 int shapeCount = 0;
};

#endif