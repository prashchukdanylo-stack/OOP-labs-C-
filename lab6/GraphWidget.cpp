#include "GraphWidget.h"
#include <QPainter>
#include <algorithm>

GraphWidget::GraphWidget(const QVector<Point> &data, QWidget *parent) 
    : pointsData(data), QWidget(parent) {}

void GraphWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int margin = 50;

    painter.fillRect(rect(), Qt::white);

    if (pointsData.isEmpty()) return;

    QVector<Point> sortedData = pointsData;
    std::sort(sortedData.begin(), sortedData.end(), [](const Point &a, const Point &b) {
        return a.x < b.x;
    });

    int minX = sortedData.first().x;
    int maxX = sortedData.last().x;
    
    int minY = sortedData.first().y;
    int maxY = sortedData.first().y;
    for (const auto &p : sortedData) {
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    if (minX == maxX) maxX += 1;
    if (minY == maxY) maxY += 1;

    double plotWidth = w - 2 * margin;
    double plotHeight = h - 2 * margin;

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(margin, margin, margin, h - margin);         
    painter.drawLine(margin, h - margin, w - margin, h - margin); 

    painter.drawText(w - margin + 10, h - margin + 5, "X");
    painter.drawText(margin - 10, margin - 10, "Y");

    QVector<QPointF> screenPoints;
    for (const auto &p : sortedData) {
        double xCoord = margin + static_cast<double>(p.x - minX) / (maxX - minX) * plotWidth;
        double yCoord = h - margin - static_cast<double>(p.y - minY) / (maxY - minY) * plotHeight;
        screenPoints.append(QPointF(xCoord, yCoord));

        painter.setBrush(Qt::red);
        painter.drawEllipse(QPointF(xCoord, yCoord), 4, 4);

        painter.setPen(Qt::darkGray);
        painter.drawText(xCoord - 12, h - margin + 18, QString::number(p.x));
        painter.drawText(margin - 38, yCoord + 4, QString::number(p.y));
    }
    painter.setPen(QPen(Qt::blue, 2));
    
    for (int i = 0; i < screenPoints.size() - 1; ++i) {
        painter.drawLine(screenPoints[i], screenPoints[i + 1]);
    }
}

void GraphWidget::setPoints(const QVector<Point> &points) {
    pointsData = points; 
    update();         
}