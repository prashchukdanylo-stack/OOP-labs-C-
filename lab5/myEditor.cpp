#include "myEditor.h"
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MyEditor* MyEditor::instance = nullptr;

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

void MyEditor::saveToFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    for (int i = 0; i < shapeCount; i++) {
        if (pcshape[i]) {
            out << pcshape[i]->getInfo() << '\n';
        }
    }
    file.close();
}

void MyEditor::loadFromFile(const QString& filename) {
    QFile file (filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    clearCanvas();
    QTextStream in(&file);
    while(!in.atEnd() && shapeCount < N) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        QStringList parts = line.split(' ');
        QString type = parts[0];

        Shape* newShape = nullptr;
        if (type == "Rect") {
            newShape = new RectShape();
        } else if (type == "Line") {
            newShape = new LineShape();
        } else if (type == "Ellipse") {
            newShape = new EllipseShape();
        } else if (type == "Point") {
            newShape = new PointShape();
        } else if (type == "LineDots") {
            newShape = new LineDotsShape();
        } else if (type == "Cube") {
            newShape = new CubeShape();
        }

        if (newShape) {
            newShape->createFromInfo(line);
            pcshape[shapeCount] = newShape;
            shapeCount++;
        }
    }
    file.close();
    redrawCanvas();
}

void MyEditor::selectShapeByIndex(int index) {
    for (int i =0; i < shapeCount; i++) {
        if (pcshape[i]) {
            pcshape[i] -> setSelected(i == index);
        }
    }
    redrawCanvas();
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

    {
        QPainter painter(&pixmap);

        for (int i = 0; i < shapeCount; i++) {
            if (pcshape[i]) {
                pcshape[i]->show(painter);
            }
        }
    }

    if (onShapesChangedCallback) {
        onShapesChangedCallback();
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