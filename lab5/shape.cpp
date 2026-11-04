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

// --- PointShape ---
void PointShape::show(QPainter &painter)
{   
    QPen pen(isSelected ? Qt::blue : Qt::black, 6, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);
    painter.drawPoint(xs1, ys1);
}

Shape *PointShape::clone() const { return new PointShape(*this); }

QString PointShape::getCoordinates() const {
    return QString("x: %1, y: %2").arg(xs1).arg(ys1);
}

QString PointShape::getInfo() const {
    return QString("Point %1 %2").arg(xs1).arg(ys1);
}

void PointShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 3 && parts[0] == "Point") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
    }
}

// --- LineShape ---
void LineShape::show(QPainter &painter)
{
    QPen pen(isSelected ? Qt::blue : Qt::black, 2, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(xs1, ys1, xs2, ys2);
}

void LineShape::rubber(QPainter &painter)
{
    Shape::rubber(painter);
    painter.drawLine(xs1, ys1, xs2, ys2);
}

Shape *LineShape::clone() const { return new LineShape(*this); }

QString LineShape::getCoordinates() const {
    return QString("(%1, %2) -> (%3, %4)").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

QString LineShape::getInfo() const {
    return QString("Line %1 %2 %3 %4").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

void LineShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 5 && parts[0] == "Line") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
        xs2 = parts[3].toLong();    
        ys2 = parts[4].toLong();
    }
}

// --- RectShape ---
void RectShape::show(QPainter &painter)
{
    QPen pen(isSelected ? Qt::blue : Qt::black, 2, Qt::SolidLine);
    painter.setPen(pen);
    painter.setBrush(getBrush()); 
    
    int dx = std::abs(xs2 - xs1);
    int dy = std::abs(ys2 - ys1);
    QRect previewRect(xs1 - dx, ys1 - dy, 2 * dx, 2 * dy);
    painter.drawRect(previewRect.normalized());
}

void RectShape::rubber(QPainter &painter)
{
    Shape::rubber(painter);
    
    int dx = std::abs(xs2 - xs1);
    int dy = std::abs(ys2 - ys1);
    QRect previewRect(xs1 - dx, ys1 - dy, 2 * dx, 2 * dy);

    painter.drawRect(previewRect.normalized());
}

Shape *RectShape::clone() const { return new RectShape(*this); }

QString RectShape::getCoordinates() const {
    return QString("(%1, %2) -> (%3, %4)").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

QString RectShape::getInfo() const {
    return QString("Rect %1 %2 %3 %4").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

void RectShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 5 && parts[0] == "Rect") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
        xs2 = parts[3].toLong();
        ys2 = parts[4].toLong();
    }
}

// --- EllipseShape ---
void EllipseShape::show(QPainter &painter)
{
    QPen pen(isSelected ? Qt::blue : Qt::black, 2, Qt::SolidLine);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    QRect previewRect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.drawEllipse(previewRect.normalized());
}

void EllipseShape::rubber(QPainter &painter)
{
    Shape::rubber(painter);
    QRect previewRect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.drawEllipse(previewRect.normalized());
}

Shape *EllipseShape::clone() const { return new EllipseShape(*this); }

QString EllipseShape::getCoordinates() const {
    return QString("(%1, %2) -> (%3, %4)").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

QString EllipseShape::getInfo() const {
    return QString("Ellipse %1 %2 %3 %4").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

void EllipseShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 5 && parts[0] == "Ellipse") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
        xs2 = parts[3].toLong();    
        ys2 = parts[4].toLong();
    }
}

// --- LineDotsShape ---
void LineDotsShape::show(QPainter &painter) {
    LineShape::show(painter);

    int rx = 6, ry = 6;
    EllipseShape dot1;
    dot1.set(xs1 - rx, ys1 - ry, xs1 + rx, ys1 + ry);
    dot1.show(painter);

    EllipseShape dot2;
    dot2.set(xs2 - rx, ys2 - ry, xs2 + rx, ys2 + ry);
    dot2.show(painter);
}

void LineDotsShape::rubber(QPainter &painter) {
    LineShape::rubber(painter);

    int rx = 6, ry = 6;
    EllipseShape dot1;
    dot1.set(xs1 - rx, ys1 - ry, xs1 + rx, ys1 + ry);
    dot1.rubber(painter);

    EllipseShape dot2;
    dot2.set(xs2 - rx, ys2 - ry, xs2 + rx, ys2 + ry);
    dot2.rubber(painter);
}

Shape *LineDotsShape::clone() const { return new LineDotsShape(*this); }

QString LineDotsShape::getCoordinates() const {
    return QString("(%1, %2) -> (%3, %4)").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

QString LineDotsShape::getInfo() const {
    return QString("LineDots %1 %2 %3 %4").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

void LineDotsShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 5 && parts[0] == "LineDots") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
        xs2 = parts[3].toLong();    
        ys2 = parts[4].toLong();
    }
}

// --- CubeShape ---
// --- CubeShape ---
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

QString CubeShape::getCoordinates() const {
    return QString("(%1, %2) -> (%3, %4)").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

QString CubeShape::getInfo() const {
    return QString("Cube %1 %2 %3 %4").arg(xs1).arg(ys1).arg(xs2).arg(ys2);
}

void CubeShape::createFromInfo(const QString& info) {
    QStringList parts = info.split(" ");
    if (parts.size() == 5 && parts[0] == "Cube") {
        xs1 = parts[1].toLong();
        ys1 = parts[2].toLong();
        xs2 = parts[3].toLong();    
        ys2 = parts[4].toLong();
    }
}