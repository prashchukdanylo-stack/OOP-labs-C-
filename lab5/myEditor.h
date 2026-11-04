#ifndef MYEDITOR_H
#define MYEDITOR_H


#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include "shape.h"
#include <functional>

class MyEditor : public QWidget {
    Q_OBJECT

    private:
        static MyEditor* instance;
        MyEditor(QWidget *parent = nullptr);
        MyEditor(const MyEditor&) = delete;
        MyEditor& operator=(const MyEditor&) = delete;
        ~MyEditor();
        std::function<void()> onShapesChangedCallback;
    public:
        //сінглтон
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

        int getShapeCount() const { return shapeCount;}
        Shape* getShape(int index) const {
            if (index >=0 && index < shapeCount) {
                return pcshape[index];
            }
            return nullptr;
        }
        void saveToFile(const QString& filename);
        void loadFromFile(const QString& filename);
        void selectShapeByIndex(int index);
        void setOnShapesChangedCallback(std::function<void()> callback) {
            onShapesChangedCallback = callback;
        };
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