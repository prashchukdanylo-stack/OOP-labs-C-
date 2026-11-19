#pragma once

#include <QMainWindow>
#include <QTableWidget>

class Object2Window : public QMainWindow {
    Q_OBJECT

public:
    explicit Object2Window(int nPoint, int xMin, int xMax, int yMin, int yMax, QWidget *parent = nullptr);
    void updateParams(int nPoint, int xMin, int xMax, int yMin, int yMax);

private:
    void generatePoints(int nPoint, int xMin, int xMax, int yMin, int yMax);

    QTableWidget *table = nullptr;
};