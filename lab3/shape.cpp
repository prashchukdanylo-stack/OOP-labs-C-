
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
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
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
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter.drawLine(xs1, ys1, xs2, ys2);
}
Shape *LineShape::clone() const { return new LineShape(*this); }


void RectShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(QColor(128, 128, 128)); 
    //changes
    int dx = std::abs(xs2 - xs1);
    int dy = std::abs(ys2 - ys1);
    QRect previewRect(xs1 - dx, ys1 - dy, 2 * dx, 2 * dy);
    painter.drawRect(previewRect.normalized());
}
void RectShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);

    //changes
    int dx = std::abs(xs2 - xs1);
    int dy = std::abs(ys2 - ys1);
    QRect previewRect(xs1 - dx, ys1 - dy, 2 * dx, 2 * dy);

    painter.drawRect(previewRect.normalized());
}
Shape *RectShape::clone() const { return new RectShape(*this); }

void EllipseShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);

    QRect previewRect(QPoint(xs1,ys1), QPoint(xs2,ys2));
    painter.drawEllipse(previewRect.normalized());
}
void EllipseShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    QRect previewRect(QPoint(xs1,ys1), QPoint(xs2,ys2));
    painter.drawEllipse(previewRect.normalized());
}
Shape *EllipseShape::clone() const { return new EllipseShape(*this); }