#pragma once

#include <QMainWindow>
#include <QVector>

class GraphWidget;

class Object3Window : public QMainWindow {
    Q_OBJECT

public:
    explicit Object3Window(QWidget *parent = nullptr);

public slots:
    void refreshFromClipboard();

private:
    GraphWidget *graph = nullptr;
};