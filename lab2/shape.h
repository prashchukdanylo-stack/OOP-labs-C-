#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QRect>
#include <QPoint>

class Shape
{
protected:
    long xs1, ys1, xs2, ys2;

public:
    Shape();
    virtual ~Shape() = default;

    void set(long x1, long y1, long x2, long y2);
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

class LineShape : public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
};

class RectShape : public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
};

class EllipseShape : public Shape
{
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
};

#endif