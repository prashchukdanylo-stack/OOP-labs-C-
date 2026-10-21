#include "mainWindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QActionGroup>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Lab 4");
    resize(640, 480);

    editor = new MyEditor(this);
    setCentralWidget(editor);


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
    toolbarPoint->setData(ShapePoint);
    QAction *toolbarLine = new QAction(QIcon(":icons/line.png"), "Лінія", this);
    toolbarLine->setCheckable(true);
    toolbarLine->setToolTip("Інструмент: Лінія");
    toolbarLine->setData(ShapeLine);

    QAction *toolbarRect = new QAction(QIcon(":icons/rectangle.png"), "Прямокутник", this);
    toolbarRect->setCheckable(true);
    toolbarRect->setToolTip("Інструмент: Прямокутник (від центру)");
    toolbarRect->setData(ShapeRect);

    QAction *toolbarEllipse = new QAction(QIcon(":icons/ellipse.png"), "Еліпс", this);
    toolbarEllipse->setCheckable(true);
    toolbarEllipse->setToolTip("Інструмент: Еліпс");
    toolbarEllipse->setData(ShapeEllipse);

    QAction *toolbarLineDots = new QAction(QIcon(":icons/linedots.png"), "Лінія з крапками", this);
    toolbarLineDots->setCheckable(true);
    toolbarLineDots->setToolTip("Інструмент: Лінія з крапками");
    toolbarLineDots->setData(ShapeLineDots);


    QAction *toolbarCube = new QAction(QIcon(":icons/cube.png"), "Каркас куба", this);
    toolbarCube->setCheckable(true);
    toolbarCube->setToolTip("Інструмент: Каркас куба");
    toolbarCube->setData(ShapeCube);


    shapeGroup->addAction(toolbarPoint);
    shapeGroup->addAction(toolbarLine);
    shapeGroup->addAction(toolbarRect);
    shapeGroup->addAction(toolbarEllipse);
    shapeGroup->addAction(toolbarLineDots);
    shapeGroup->addAction(toolbarCube);

    toolBar->addAction(toolbarPoint);
    toolBar->addAction(toolbarLine);
    toolBar->addAction(toolbarRect);
    toolBar->addAction(toolbarEllipse);
    toolBar->addAction(toolbarLineDots);
    toolBar->addAction(toolbarCube);

    QMenu *menuObjects = menu->addMenu("&Обʼєкти");
    menuObjects->addAction(toolbarPoint);
    menuObjects->addAction(toolbarLine);
    menuObjects->addAction(toolbarRect);
    menuObjects->addAction(toolbarEllipse);
    menuObjects->addAction(toolbarLineDots);
    menuObjects->addAction(toolbarCube);

    QMenu *menuInfo = menu->addMenu("&Довідка");
    QAction *infoAction = menuInfo->addAction("Довідкова інформація");

    connect(fileAction, &QAction::triggered, editor, &MyEditor::clearCanvas);

    connect(infoAction, &QAction::triggered, this, [this]()
            { QMessageBox::information(this, "Довідка",
    "Лабораторна робота №4 «Вдосконалення структури коду графічного редактора об’єктів».<br>"
                                       "Варіант: 16<br>"
                                       "Автор: Пращук Данило Павлович ІМ-52"); });

    connect(shapeGroup, &QActionGroup::triggered, this, &MainWindow::onNotify);

    toolbarPoint->setChecked(true);
    onNotify(toolbarPoint);
}

MainWindow::~MainWindow()
{
    delete editor;
}

void MainWindow::onNotify(QAction *action)
{

    int shapeType = action->data().toInt();
    switch (shapeType)
    {   
        case ShapePoint:
            editor->setCurrentShape(new PointShape());
            setWindowTitle("Lab 4 - Крапка");
            break;
        
        case ShapeLine:
            editor->setCurrentShape(new LineShape());
            setWindowTitle("Lab 4 - Лінія");
            break;
        
        case ShapeRect:
        editor->setCurrentShape(new RectShape());
        setWindowTitle("Lab 4 - Прямокутник");
        break;
        
        case ShapeEllipse:
        editor->setCurrentShape(new EllipseShape());
        setWindowTitle("Lab 4 - Еліпс");
        break;

        case ShapeLineDots:
        editor->setCurrentShape(new LineDotsShape());
        setWindowTitle("Lab 4 - Лінія з крапками");
        break;

        case ShapeCube:
        editor->setCurrentShape(new CubeShape());
        setWindowTitle("Lab 4 - Каркас куба");
        break;

        default:
            break;
    }
}
