
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
    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
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
    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
    painter.drawLine(xs1, ys1, xs2, ys2);
}
Shape *LineShape::clone() const { return new LineShape(*this); }


void RectShape::show(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(getBrush()); 
    //changes
    int dx = std::abs(xs2 - xs1);
    int dy = std::abs(ys2 - ys1);
    QRect previewRect(xs1 - dx, ys1 - dy, 2 * dx, 2 * dy);
    painter.drawRect(previewRect.normalized());
}
void RectShape::rubber(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
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
    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    QRect previewRect(QPoint(xs1,ys1), QPoint(xs2,ys2));
    painter.drawEllipse(previewRect.normalized());
}
Shape *EllipseShape::clone() const { return new EllipseShape(*this); }


LineDotsShape::LineDotsShape() : LineShape(), EllipseShape() {}
LineDotsShape::LineDotsShape(const LineDotsShape &other): Shape(other), LineShape(other), EllipseShape(other) {}

void LineDotsShape::set(long x1, long y1, long x2, long y2) {
    LineShape::set(x1, y1, x2, y2);
    EllipseShape::set(x1, y1, x2, y2);
}

void LineDotsShape::show(QPainter &painter) {
    LineShape::show(painter);
    int savedX1 = xs1, savedY1 = ys1, savedX2 = xs2, savedY2 = ys2;


    int rx = 6;
    int ry = 6;
    EllipseShape::set(savedX1 -rx, savedY1 - ry, savedX1 + rx, savedY1 + ry);
    EllipseShape::show(painter);

    EllipseShape::set(savedX2 - rx, savedY2 - ry, savedX2 + rx, savedY2 + ry);
    EllipseShape::show(painter);

    LineShape::set(savedX1, savedY1, savedX2, savedY2);
}

void LineDotsShape::rubber(QPainter &painter) {
    LineShape::rubber(painter);

    long savedX1 = xs1, savedY1 = ys1, savedX2 = xs2, savedY2 = ys2;

    int rx = 6;
    int ry = 6;
    EllipseShape::set(savedX1 -rx, savedY1 - ry, savedX1 + rx, savedY1 + ry);
    EllipseShape::show(painter);

    EllipseShape::set(savedX2 - rx, savedY2 - ry, savedX2 + rx, savedY2 + ry);
    EllipseShape::show(painter);

    LineShape::set(savedX1, savedY1, savedX2, savedY2);
}

Shape *LineDotsShape::clone() const { return new LineDotsShape(*this); }



CubeShape::CubeShape() : RectShape(), LineShape() {}
CubeShape::CubeShape(const CubeShape &other) : Shape(other), RectShape(other), LineShape(other) {}

void CubeShape::set(long x1, long y1, long x2, long y2) {
    RectShape::set(x1, y1, x2, y2);
    LineShape::set(x1, y1, x2, y2);
}

void CubeShape::show(QPainter &painter) {

    long origX1 = xs1, origY1 = ys1, origX2 = xs2, origY2 = ys2;

    int dx = std::abs(origX2 - origX1);
    int dy = std::abs(origY2 - origY1);
    
    long fx1 = origX1 - dx;
    long fy1 = origY1 - dy;
    long fx2 = origX1 + dx;
    long fy2 = origY1 + dy;

    int shiftX = dx / 2;
    int shiftY = dy / 2;

    long bx1 = fx1 + shiftX;
    long by1 = fy1 + shiftY;
    long bx2 = fx2 + shiftX;
    long by2 = fy2 + shiftY;

    RectShape::set(origX1, origY1, origX2, origY2);
    RectShape::show(painter);

    long bCenterX = (bx1 + bx2) / 2;
    long bCenterY = (by1 + by2) / 2;
    long bRadiusX = std::abs(bx2 - bx1) / 2;
    long bRadiusY = std::abs(by2 - by1) / 2;
    RectShape::set(bCenterX, bCenterY, bCenterX + bRadiusX, bCenterY + bRadiusY);
    RectShape::show(painter);

    LineShape::set(fx1, fy1, bx1, by1);
    LineShape::show(painter);

    LineShape::set(fx2, fy1, bx2, by1);
    LineShape::show(painter);

    LineShape::set(fx1, fy2, bx1, by2);
    LineShape::show(painter);

    LineShape::set(fx2, fy2, bx2, by2);
    LineShape::show(painter);

    RectShape::set(origX1, origY1, origX2, origY2);
    LineShape::set(origX1, origY1, origX2, origY2);
}

void CubeShape::rubber(QPainter &painter) {
    long origX1 = xs1, origY1 = ys1, origX2 = xs2, origY2 = ys2;

    int dx = std::abs(origX2 - origX1);
    int dy = std::abs(origY2 - origY1);
    
    long fx1 = origX1 - dx;
    long fy1 = origY1 - dy;
    long fx2 = origX1 + dx;
    long fy2 = origY1 + dy;

    int shiftX = dx / 2;
    int shiftY = dy / 2;

    long bx1 = fx1 + shiftX;
    long by1 = fy1 + shiftY;
    long bx2 = fx2 + shiftX;
    long by2 = fy2 + shiftY;

    RectShape::set(origX1, origY1, origX2, origY2);
    RectShape::rubber(painter);

    long bCenterX = (bx1 + bx2) / 2;
    long bCenterY = (by1 + by2) / 2;
    long bRadiusX = std::abs(bx2 - bx1) / 2;
    long bRadiusY = std::abs(by2 - by1) / 2;
    RectShape::set(bCenterX, bCenterY, bCenterX + bRadiusX, bCenterY + bRadiusY);
    RectShape::rubber(painter);

    LineShape::set(fx1, fy1, bx1, by1);
    LineShape::rubber(painter);

    LineShape::set(fx2, fy1, bx2, by1);
    LineShape::rubber(painter);

    LineShape::set(fx1, fy2, bx1, by2);
    LineShape::rubber(painter);

    LineShape::set(fx2, fy2, bx2, by2);
    LineShape::rubber(painter);

    RectShape::set(origX1, origY1, origX2, origY2);
    LineShape::set(origX1, origY1, origX2, origY2);
}

Shape *CubeShape::clone() const { return new CubeShape(*this); }
