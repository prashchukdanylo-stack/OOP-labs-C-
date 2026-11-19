#include "Object2Window.h"
#include <QVBoxLayout>
#include <QClipboard>
#include <QRandomGenerator>
#include <QApplication>
#include <QTableWidgetItem>
#include <algorithm>

Object2Window::Object2Window(int nPoint, int xMin, int xMax, int yMin, int yMax, QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Object2 - Генератор пар (x, y)");
    resize(450, 320);
    move(530, 100);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"X (int)", "Y (int)"});

    layout->addWidget(table);
    setCentralWidget(central);

    generatePoints(nPoint, xMin, xMax, yMin, yMax);
}

void Object2Window::generatePoints(int nPoint, int xMin, int xMax, int yMin, int yMax) {
    if (nPoint < 0) nPoint = 0;
    if (xMin > xMax) std::swap(xMin, xMax);
    if (yMin > yMax) std::swap(yMin, yMax);

    table->clearContents();
    table->setRowCount(nPoint);

    QString clipboardText;

    for (int i = 0; i < nPoint; ++i) {
        int x = QRandomGenerator::global()->bounded(xMin, xMax + 1);
        int y = QRandomGenerator::global()->bounded(yMin, yMax + 1);

        table->setItem(i, 0, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(y)));

        clipboardText += QString("%1 %2\n").arg(x).arg(y);
    }

    QApplication::clipboard()->setText(clipboardText);
}

void Object2Window::updateParams(int nPoint, int xMin, int xMax, int yMin, int yMax) {
    generatePoints(nPoint, xMin, xMax, yMin, yMax);
}