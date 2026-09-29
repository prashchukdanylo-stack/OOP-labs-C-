
#include "shape.h"
#include <cmath>
#include <QPen>
#include <QColor>

Shape::Shape() : xs1(0), ys1(0), xs2(0), ys2(0) {}

void Shape::set(long x1, long y1, long x2, long y2)
{
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
}

void Shape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
}

void PointShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(xs1, ys1);
}
Shape *PointShape::clone() const { return new PointShape(*this); }


void LineShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawLine(xs1, ys1, xs2, ys2);
}
void LineShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLine(xs1, ys1, xs2, ys2);
}
Shape *LineShape::clone() const { return new LineShape(*this); }


void RectShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(QColor(255, 165, 0)); 
    QRect rect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.drawRect(rect.normalized());
}
void RectShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    QRect previewRect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.drawRect(previewRect.normalized());
}
Shape *RectShape::clone() const { return new RectShape(*this); }

void EllipseShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(Qt::white);
    int rx = std::abs(xs2 - xs1);
    int ry = std::abs(ys2 - ys1);
    painter.drawEllipse(QPoint(xs1, ys1), rx, ry);
}
void EllipseShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    int rx = std::abs(xs2 - xs1);
    int ry = std::abs(ys2 - ys1);
    painter.drawEllipse(QPoint(xs1, ys1), rx, ry);
}
Shape *EllipseShape::clone() const { return new EllipseShape(*this); }