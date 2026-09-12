#include "mainwindow.h"
#include "module1.h"
#include "module2.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent) {
    setWindowTitle("Лаба 1 варіант 15");
    resize(600,400);

    QMenu *actionsMenu = menuBar()->addMenu("Дії");
    QAction *actWork1 = actionsMenu->addAction("Слайдер");
    QAction *actWork2 = actionsMenu->addAction("Текст");

    connect(actWork1, &QAction::triggered, this, &MainWindow::onActionWork1);
    connect(actWork2, &QAction::triggered, this, &MainWindow::onActionWork2);
}

void MainWindow::onActionWork1() {
    if (mod1Func(this, &work1Number) == 1) {
        update();
    }
}
void MainWindow::onActionWork2() {
    if (mod2Func(this, &work2Text) == 1) {
        update();
    }
}
void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setFont(QFont("Arial", 12));

    if (work1Number != -1) {
        QString text = QString("Результат слайдеру: %1").arg(work1Number);
        painter.drawText(30, 60, text);
    }
    if (!work2Text.isEmpty()) {
        QString text = QString("Результат тексту: %1").arg(work2Text);
        painter.drawText(30, 100, text);
    }
}
