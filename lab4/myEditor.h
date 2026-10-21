#ifndef MYEDITOR_H
#define MYEDITOR_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include "shape.h"

class MyEditor : public QWidget
{
    Q_OBJECT
public:
    MyEditor(QWidget *parent = nullptr);
    ~MyEditor();

    void setCurrentShape(Shape *shape);
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void redrawCanvas();
    void resizeEvent(QResizeEvent *event) override;

    bool isDragging;
    QPoint startPt;
    QPoint endPt;

    static const int N = 117;
    Shape *currentShape;
    Shape *pcshape[N] = {nullptr};
    int shapeCount;
    QPixmap pixmap;
};

#endif