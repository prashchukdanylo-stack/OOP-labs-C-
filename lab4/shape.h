#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QRect>
#include <QPoint>

enum ShapeType {
    ShapePoint,
    ShapeLine,
    ShapeRect,
    ShapeEllipse,
    ShapeLineDots,
    ShapeCube
};

class Shape
{
protected:
    long xs1, ys1, xs2, ys2;

public:
    Shape();
    virtual ~Shape() = default;

     virtual void set(long x1, long y1, long x2, long y2);
    virtual void show(QPainter &painter) = 0;
    virtual void rubber(QPainter &painter);
    virtual Shape* clone() const = 0;
};

class PointShape : public Shape
{
public:
    void show(QPainter &painter) override;
    Shape* clone() const override;
};

class LineShape : virtual public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
};

class RectShape : virtual public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    virtual QBrush getBrush() {
        return QColor(128,128,128);
    }
};

class EllipseShape : virtual public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
};

class LineDotsShape : public LineShape, public EllipseShape {
    public:

    LineDotsShape();
    LineDotsShape(const LineDotsShape &other);
        void set(long x1, long y1, long x2, long y2) override;
        void show(QPainter &painter) override;
        void rubber(QPainter &painter);
        Shape* clone() const override;

};

class CubeShape : public LineShape, public RectShape {
    public:
        CubeShape();
    CubeShape(const CubeShape &other);
        void set(long x1, long y1, long x2, long y2) override;
        void show(QPainter &painter) override;
        void rubber(QPainter &painter);
        Shape* clone() const override;
        QBrush getBrush() override { return Qt::NoBrush; }
};

#endif