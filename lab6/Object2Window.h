#pragma once

#include <QMainWindow>

class Object2Window : public QMainWindow {
    Q_OBJECT
public:
    Object2Window(int nPoint, int xMin, int xMax, int yMin, int yMax, QWidget *parent = nullptr);
};