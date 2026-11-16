#include "Object2Window.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QClipboard>
#include <QRandomGenerator>
#include <QApplication>

Object2Window::Object2Window(int nPoint, int xMin, int xMax, int yMin, int yMax, QWidget *parent) 
    : QMainWindow(parent) {
    setWindowTitle("Object2 - Генератор пар (x, y)");
    resize(450, 320);
    move(530, 100);
    
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    auto *table = new QTableWidget(this);
    table->setRowCount(nPoint);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"X (int)", "Y (int)"});

    QString clipboardText = "";

    for (int i = 0; i < nPoint; ++i) {
        int x = QRandomGenerator::global()->bounded(xMin, xMax + 1);
        int y = QRandomGenerator::global()->bounded(yMin, yMax + 1);

        table->setItem(i, 0, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(y)));

        clipboardText += QString("%1 %2\n").arg(x).arg(y);
    }

    layout->addWidget(table);
    setCentralWidget(central);

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(clipboardText);
}