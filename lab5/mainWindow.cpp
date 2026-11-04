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
    QAction *saveAction = menuFile->addAction("Зберегти у файл");
    QAction *loadAction = menuFile->addAction("Завантажити з файлу");

    toolBar = addToolBar("Панель фігур");
    toolBar->setMovable(false);

    QMenu *menuObjects = menu->addMenu("&Обʼєкти");
    QActionGroup *shapeGroup = new QActionGroup(this);
    shapeGroup->setExclusive(true);

    struct ToolInfo {
        QString iconPath;
        QString name;
        QString toolTip;
        int shapeType;
    };

    const QList<ToolInfo> tools = {
        {":icons/point.png",      "Крапка",         "Інструмент: Крапка",                     ShapePoint},
        {":icons/line.png",       "Лінія",          "Інструмент: Лінія",                      ShapeLine},
        {":icons/rectangle.png",  "Прямокутник",    "Інструмент: Прямокутник (від центру)",   ShapeRect},
        {":icons/ellipse.png",    "Еліпс",          "Інструмент: Еліпс",                      ShapeEllipse},
        {":icons/linedots.png",   "Лінія з крапками","Інструмент: Лінія з крапками",          ShapeLineDots},
        {":icons/cube.png",       "Каркас куба",    "Інструмент: Каркас куба",                ShapeCube}
    };

    QAction *defaultAction = nullptr;

    for (const auto &info : tools) {
        QAction *action = new QAction(QIcon(info.iconPath), info.name, this);
        action->setCheckable(true);
        action->setToolTip(info.toolTip);
        action->setData(info.shapeType);

        shapeGroup->addAction(action);
        toolBar->addAction(action);
        menuObjects->addAction(action);

        if (info.shapeType == ShapePoint) {
            defaultAction = action;
        }
    }

    QMenu *menuInfo = menu->addMenu("&Довідка");
    QAction *infoAction = menuInfo->addAction("Довідкова інформація");

    
    connect(fileAction, &QAction::triggered, editor, &MyEditor::clearCanvas);

    connect(saveAction, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Зберегти файл", "", "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            editor->saveToFile(fileName);
        }
    });

    connect(loadAction, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Відкрити файл", "", "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            editor->loadFromFile(fileName);
        }
    });

    connect(tableAction, &QAction::triggered, this, [this]() {
        if (!tableWindow) {
            tableWindow = new MyTableWindow(this);
        }

        tableWindow->setOnRowSelectedCallback([this](int index) {
            editor->selectShapeByIndex(index);
        });

        editor->setOnShapesChangedCallback([this]() {
            if (tableWindow) {
                tableWindow->updateTableData();
            }
        });

        tableWindow->show();
        tableWindow->raise();
        tableWindow->activateWindow();
    });

    connect(infoAction, &QAction::triggered, this, [this]() {
        QMessageBox::information(this, "Довідка",
                                   "Лабораторна робота №5 «Розробка багатовіконного інтерфейсу користувача для графічного редактора об’єктів».<br>"
                                   "Варіант: 16<br>"
                                   "Автор: Пращук Данило Павлович ІМ-52");
    });

    connect(shapeGroup, &QActionGroup::triggered, this, &MainWindow::onNotify);

    if (defaultAction) {
        defaultAction->setChecked(true);
        onNotify(defaultAction);
    }
}

MainWindow::~MainWindow()
{
    MyEditor::destroyInstance();
}

void MainWindow::onNotify(QAction *action)
{
    int shapeType = action->data().toInt();
    QString shapeName;
    Shape* newShape = nullptr;

    switch (shapeType)
    {
    case ShapePoint:
        newShape = new PointShape();
        shapeName = "Крапка";
        break;
    case ShapeLine:
        newShape = new LineShape();
        shapeName = "Лінія";
        break;
    case ShapeRect:
        newShape = new RectShape();
        shapeName = "Прямокутник";
        break;
    case ShapeEllipse:
        newShape = new EllipseShape();
        shapeName = "Еліпс";
        break;
    case ShapeLineDots:
        newShape = new LineDotsShape();
        shapeName = "Лінія з крапками";
        break;
    case ShapeCube:
        newShape = new CubeShape();
        shapeName = "Каркас куба";
        break;
    default:
        break;
    }

    if (newShape) {
        editor->setCurrentShape(newShape);
        setWindowTitle("Lab 5 - " + shapeName);
    }
}