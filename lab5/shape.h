#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QBrush>
#include <QColor>

enum ShapeType {
    ShapePoint,
    ShapeLine,
    ShapeRect,
    ShapeEllipse,
    ShapeLineDots,
    ShapeCube
};

class Shape {
protected:
    long xs1, ys1, xs2, ys2;
    bool isSelected = false;

public:
    Shape();
    virtual ~Shape() = default;

    virtual void setSelected(bool selected) { isSelected = selected; }
    virtual void set(long x1, long y1, long x2, long y2);
    
    virtual void show(QPainter &painter) = 0;
    virtual void rubber(QPainter &painter);
    virtual Shape* clone() const = 0;
    
    virtual QString getInfo() const = 0;
    virtual void createFromInfo(const QString& info) = 0;
    virtual QString getCoordinates() const = 0;
    virtual QString getShapeName() const = 0;
};

class PointShape : public Shape {
public:
    void show(QPainter &painter) override;
    Shape* clone() const override;
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Крапка"; }
};

class LineShape : virtual public Shape {
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Лінія"; }
};

class RectShape : virtual public Shape {
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    
    virtual QBrush getBrush() {
        return QColor(128, 128, 128);
    }
    
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Прямокутник"; }
};

class EllipseShape : virtual public Shape {
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Еліпс"; }
};

class LineDotsShape : public LineShape, public EllipseShape {
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Лінія з кругами"; }
};

class CubeShape : public LineShape, public RectShape {
public:
    void show(QPainter &painter) override;
    void rubber(QPainter &painter) override;
    Shape* clone() const override;
    
    QBrush getBrush() override { return Qt::NoBrush; }
    
    QString getInfo() const override;
    void createFromInfo(const QString& info) override;
    QString getCoordinates() const override;
    QString getShapeName() const override { return "Куб"; }
};

#endif // SHAPE_H