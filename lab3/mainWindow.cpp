#include "mainWindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QActionGroup>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Lab 3");
    resize(640, 480);

    QMenuBar *menu = menuBar();
    QMenu *menuFile = menu->addMenu("&Файл");
    QAction *fileAction = menuFile->addAction("Очистити");

    toolBar = addToolBar("Панель фігур");
    toolBar->setMovable(false);

    QActionGroup *shapeGroup = new QActionGroup(this);
    shapeGroup->setExclusive(true);

    QAction *toolbarPoint = new QAction(QIcon(":icons/point.png"), "Крапка", this);
    toolbarPoint->setCheckable(true);
    toolbarPoint->setToolTip("Інструмент: Крапка");

    QAction *toolbarLine = new QAction(QIcon(":icons/line.png"), "Лінія", this);
    toolbarLine->setCheckable(true);
    toolbarLine->setToolTip("Інструмент: Лінія");

    QAction *toolbarRect = new QAction(QIcon(":icons/rectangle.png"), "Прямокутник", this);
    toolbarRect->setCheckable(true);
    toolbarRect->setToolTip("Інструмент: Прямокутник (від центру)");

    QAction *toolbarEllipse = new QAction(QIcon(":icons/ellipse.png"), "Еліпс", this);
    toolbarEllipse->setCheckable(true);
    toolbarEllipse->setToolTip("Інструмент: Еліпс");

    shapeGroup->addAction(toolbarPoint);
    shapeGroup->addAction(toolbarLine);
    shapeGroup->addAction(toolbarRect);
    shapeGroup->addAction(toolbarEllipse);

    toolBar->addAction(toolbarPoint);
    toolBar->addAction(toolbarLine);
    toolBar->addAction(toolbarRect);
    toolBar->addAction(toolbarEllipse);

    QMenu *menuObjects = menu->addMenu("&Обʼєкти");
    menuObjects->addAction(toolbarPoint);
    menuObjects->addAction(toolbarLine);
    menuObjects->addAction(toolbarRect);
    menuObjects->addAction(toolbarEllipse);

    QMenu *menuInfo = menu->addMenu("&Довідка");
    QAction *infoAction = menuInfo->addAction("Довідкова інформація");

    connect(fileAction, &QAction::triggered, this, [this]()
            {
        for (int i = 0; i < shapeCount; i++) {
        delete pcshape[i];
        pcshape[i] = nullptr;
    }
    shapeCount = 0;
    redrawCanvas(); });

    connect(infoAction, &QAction::triggered, this, [this]()
            { QMessageBox::information(this, "Довідка",
                                       "Лабораторна робота №3 «Розробка інтерфейсу користувача».<br>"
                                       "Варіант: 17<br>"
                                       "Автор: Пращук Данило Павлович ІМ-52"); });

    connect(shapeGroup, &QActionGroup::triggered, this, &MainWindow::onNotify);

    toolbarPoint->setChecked(true);
    onNotify(toolbarPoint);
}

MainWindow::~MainWindow()
{
    delete currentShape;
    for (int i = 0; i < shapeCount; i++)
    {
        delete pcshape[i];
    }
}

void MainWindow::onNotify(QAction *action)
{
    delete currentShape;
    currentShape = nullptr;

    if (action->text() == "Крапка")
    {
        currentShape = new PointShape();
        setWindowTitle("Lab 3 - Крапка");
    }
    else if (action->text() == "Лінія")
    {
        currentShape = new LineShape();
        setWindowTitle("Lab 3 - Лінія");
    }
    else if (action->text() == "Прямокутник")
    {
        currentShape = new RectShape();
        setWindowTitle("Lab 3 - Прямокутник");
    }
    else if (action->text() == "Еліпс")
    {
        currentShape = new EllipseShape();
        setWindowTitle("Lab 3 - Еліпс");
    }
}

void MainWindow::redrawCanvas()
{
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    int topOffset = menuBar()->height() + toolBar->height();
    painter.setClipRect(0, topOffset, width(), height() - topOffset);

    for (int i = 0; i < shapeCount; i++)
    {
        if (pcshape[i])
        {
            pcshape[i]->show(painter);
        }
    }
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int topOffset = menuBar()->height() + toolBar->height();
    if (event->pos().y() < topOffset)
        return;

    if (event->button() == Qt::LeftButton && currentShape != nullptr)
    {
        if (shapeCount >= N)
            return;

        startPt = event->pos();
        endPt = event->pos();
        isDragging = true;

        if (dynamic_cast<PointShape *>(currentShape))
        {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
            shapeCount++;
            isDragging = false;
            redrawCanvas();
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    pixmap = QPixmap(size());
    redrawCanvas();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;
        endPt = event->pos();

        if (currentShape && shapeCount < N)
        {
            pcshape[shapeCount] = currentShape->clone();
            pcshape[shapeCount]->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
            shapeCount++;
            redrawCanvas();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    int topOffset = menuBar()->height() + toolBar->height();
    QRect drawingArea(0, topOffset, width(), height() - topOffset);
    painter.setClipRect(drawingArea);

    painter.drawPixmap(0, 0, pixmap);

    if (isDragging && currentShape)
    {
        currentShape->set(startPt.x(), startPt.y(), endPt.x(), endPt.y());
        currentShape->rubber(painter);
    }
}