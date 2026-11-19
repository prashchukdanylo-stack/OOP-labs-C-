#pragma once

#include <QWidget>
#include <QVector>

struct Point {
    int x;
    int y;
};

class GraphWidget : public QWidget {
    Q_OBJECT
    QVector<Point> pointsData;

public:
    GraphWidget(const QVector<Point> &data, QWidget *parent = nullptr);
    void setPoints(const QVector<Point> &points);

    
protected:
    void paintEvent(QPaintEvent *event) override;
    
};