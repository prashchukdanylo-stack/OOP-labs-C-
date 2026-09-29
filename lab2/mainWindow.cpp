#include "mainWindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Laba 2");
    resize(640, 480);

    QMenuBar *menu = menuBar();
    QMenu *menuFile = menu->addMenu("&Файл");
    QAction *fileAction = menuFile->addAction("про файл");
    QObject::connect(fileAction, &QAction::triggered, [this]()
                     { QMessageBox::information(this, "File", "Це файл другої лабораторної з ооп, де потрібно створити базовий графічний редактор"); });

    QMenu *menuObjects = menu->addMenu("&Обʼєкти");
    QAction *action1 = menuObjects->addAction("Крапка");
    QAction *action2 = menuObjects->addAction("Лінія");
    QAction *action3 = menuObjects->addAction("Прямокутник");
    QAction *action4 = menuObjects->addAction("Еліпс");
    QMenu *menuInfo = menu->addMenu("&Довідка");
    QAction *infoAction = menuInfo->addAction("довідкова інформація");
    QObject::connect(infoAction, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "Довідка","Лабораторна робота №2 «Розробка графічного редактора об’єктів».<br>Базовий графічний редактор<br>Варіант: 16<br>Автор: Пращук Данило Павлович ІМ-52");
    });
    shapeGroup = new QActionGroup(this);
    shapeGroup->setExclusive(true);

    for (QAction *act : {action1, action2, action3, action4})
    {
        act->setCheckable(true);
        shapeGroup->addAction(act);
    }

    connect(action1, &QAction::triggered, this, [this]()
            { delete currentShape;
              currentShape = new PointShape(); });
    connect(action2, &QAction::triggered, this, [this]()
            { delete currentShape;
              currentShape = new LineShape(); });
    connect(action3, &QAction::triggered, this, [this]()
            {
        delete currentShape;
              currentShape = new RectShape(); });
    connect(action4, &QAction::triggered, this, [this]()
            {
        delete currentShape;
              currentShape = new EllipseShape(); });
}

MainWindow::~MainWindow()
{
    delete currentShape;
    for (int i = 0; i < shapeCount; i++)
    {
        delete pcshape[i];
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().y() < menuBar()->height())
        return;

    if (event->button() == Qt::LeftButton && currentShape != nullptr)
    {
        if (shapeCount >= N)
            return;

        startPt = event->pos();
        endPt = event->pos();
        isDragging = true;

        if (dynamic_cast<PointShape*>(currentShape))
        {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
            shapeCount++;
            isDragging = false;
            update();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        endPt = event->pos();
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;
        endPt = event->pos();

        if (currentShape && shapeCount < N) {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
            shapeCount++;
            update();
        }
      
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    int menuHeght = menuBar()->height();

    QRect drawingArea(0, menuHeght, width(), height() - menuHeght);
    painter.setClipRect(drawingArea);

    for (int i = 0; i < shapeCount; i++)
    {
        if (pcshape[i])
        {
            pcshape[i]->show(painter);
        }
    }

    if (isDragging && currentShape)
    {
        currentShape->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
        currentShape->rubber(painter);
    }
}