#ifndef MYEDITOR_H
#define MYEDITOR_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <functional>
#include "shape.h"

class MyEditor : public QWidget {
    Q_OBJECT

private:
    static MyEditor* instance;
    MyEditor(QWidget *parent = nullptr);
    MyEditor(const MyEditor&) = delete;
    MyEditor& operator=(const MyEditor&) = delete;
    ~MyEditor();

    static const int N = 117;
    Shape *pcshape[N] = {nullptr};
    int shapeCount;
    Shape *currentShape;

    QPixmap pixmap;
    bool isDragging;
    QPoint startPt;
    QPoint endPt;

    std::function<void()> onShapesChangedCallback;

    Shape* createShapeByType(const QString &type);

public:
    static MyEditor* getInstance(QWidget *parent = nullptr) {
        if (!instance) {
            instance = new MyEditor(parent);
        }
        return instance;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }

    void setCurrentShape(Shape *shape);
    void clearCanvas();

    int getShapeCount() const { return shapeCount; }
    
    Shape* getShape(int index) const {
        if (index >= 0 && index < shapeCount) {
            return pcshape[index];
        }
        return nullptr;
    }

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);
    void selectShapeByIndex(int index);

    void setOnShapesChangedCallback(std::function<void()> callback) {
        onShapesChangedCallback = callback;
    }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void redrawCanvas();
};

#endif