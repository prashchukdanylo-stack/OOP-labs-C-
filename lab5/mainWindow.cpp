#include "mainWindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QActionGroup>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Lab 5");
    resize(640, 480);

    editor = MyEditor::getInstance(this);

    setCentralWidget(editor);

    QMenuBar *menu = menuBar();
    QMenu *menuFile = menu->addMenu("&Файл");
    QAction *fileAction = menuFile->addAction("Очистити");


    QAction *tableAction = menuFile->addAction("Таблиця фігур");
    toolBar = addToolBar("Панель фігур");
    toolBar->setMovable(false);

    QAction *saveAction = menuFile->addAction("Зберегти у файл");
    QAction *loadAction = menuFile->addAction("Завантажити з файлу");

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

    connect(saveAction, &QAction::triggered, this, [this]()
            {
    QString fileName = QFileDialog::getSaveFileName(this, "Зберегти файл", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        MyEditor::getInstance()->saveToFile(fileName);
    } });

    connect(loadAction, &QAction::triggered, this, [this]()
            {
    QString fileName = QFileDialog::getOpenFileName(this, "Відкрити файл", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        MyEditor::getInstance()->loadFromFile(fileName);
    } });

    connect(tableAction, &QAction::triggered, this, [this]()
            {
    if (!tableWindow) {
        tableWindow = new MyTableWindow(this);
    }

    tableWindow->setOnRowSelectedCallback([this](int index) {
        MyEditor::getInstance()->selectShapeByIndex(index);
    });

    MyEditor::getInstance()->setOnShapesChangedCallback([this]() {
        if (tableWindow) {
            tableWindow->updateTableData();
        }
    });

     tableWindow->show();
    tableWindow->raise();
    tableWindow->activateWindow(); });

    connect(infoAction, &QAction::triggered, this, [this]()
            { QMessageBox::information(this, "Довідка",
                                       "Лабораторна робота №5 «Розробка багатовіконного інтерфейсу користувача для графічного редактора об’єктів».<br>"
                                       "Варіант: 16<br>"
                                       "Автор: Пращук Данило Павлович ІМ-52"); });

    connect(shapeGroup, &QActionGroup::triggered, this, &MainWindow::onNotify);

    toolbarPoint->setChecked(true);
    onNotify(toolbarPoint);
}

MainWindow::~MainWindow()
{
    MyEditor::destroyInstance();
}

void MainWindow::onNotify(QAction *action)
{

    int shapeType = action->data().toInt();
    switch (shapeType)
    {
    case ShapePoint:
        editor->setCurrentShape(new PointShape());
        setWindowTitle("Lab 5 - Крапка");
        break;

    case ShapeLine:
        editor->setCurrentShape(new LineShape());
        setWindowTitle("Lab 5 - Лінія");
        break;

    case ShapeRect:
        editor->setCurrentShape(new RectShape());
        setWindowTitle("Lab 5 - Прямокутник");
        break;

    case ShapeEllipse:
        editor->setCurrentShape(new EllipseShape());
        setWindowTitle("Lab 5 - Еліпс");
        break;

    case ShapeLineDots:
        editor->setCurrentShape(new LineDotsShape());
        setWindowTitle("Lab 5 - Лінія з крапками");
        break;

    case ShapeCube:
        editor->setCurrentShape(new CubeShape());
        setWindowTitle("Lab 5 - Каркас куба");
        break;

    default:
        break;
    }
}
