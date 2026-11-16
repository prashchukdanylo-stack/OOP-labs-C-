#include "Object3Window.h"
#include "GraphWidget.h"
#include <QClipboard>
#include <QStringList>
#include <QApplication>

Object3Window::Object3Window(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Object3 - Графік функції y = f(x) (Варіант 0)");
    resize(650, 480);
    move(1000, 100);
    
    QClipboard *clipboard = QApplication::clipboard();
    QString text = clipboard->text();

    QVector<Point> data;
    QStringList lines = text.split("\n", Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 2) {
            bool ok1, ok2;
            int x = parts[0].toInt(&ok1);
            int y = parts[1].toInt(&ok2);
            if (ok1 && ok2) {
                data.append({x, y});
            }
        }
    }

    if (data.isEmpty()) {
        data = {{0, 10}, {10, 45}, {20, 20}, {30, 80}, {40, 50}, {50, 95}};
    }

    auto *graph = new GraphWidget(data, this);
    setCentralWidget(graph);
}