#include "myEditor.h"
#include <QMouseEvent>
MyEditor::MyEditor(QWidget *parent) : QWidget(parent), shapeCount(0), currentShape(nullptr), isDragging(false)
{};


MyEditor::~MyEditor() {
    delete currentShape;
    for (int i = 0; i < shapeCount; i++) {
        delete pcshape[i];
    }
};

void MyEditor::setCurrentShape(Shape *shape) {
    delete currentShape;
    currentShape = shape;
}

void MyEditor::clearCanvas() {
    for (int i = 0; i < shapeCount; i++) {
        delete pcshape[i];
        pcshape[i] = nullptr;
    }
    shapeCount = 0;
    redrawCanvas();
}

void MyEditor::redrawCanvas() {
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    for (int i = 0; i < shapeCount; i++)
    {
        if (pcshape[i])
        {
            pcshape[i]->show(painter);
        }
    }
    update();
}

void MyEditor::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton && currentShape != nullptr)
    {
        if (shapeCount >= N)
            return;

        startPt = event->pos();
        endPt = event->pos();
        isDragging = true;

        if (typeid(*currentShape) == typeid(PointShape))
        {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
            shapeCount++;
            isDragging = false;
            redrawCanvas();
        }
    }
}

void MyEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        endPt = event->pos();
        update();
    }
}

void MyEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;
        endPt = event->pos();

        if (currentShape && shapeCount < N)
        {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
            shapeCount++;
            redrawCanvas();
        }
    }
}

void MyEditor::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    pixmap = QPixmap(size());
    redrawCanvas();
}


void MyEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    painter.drawPixmap(0, 0, pixmap);

    if (isDragging && currentShape)
    {
        currentShape->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
        currentShape->rubber(painter);
    }
}