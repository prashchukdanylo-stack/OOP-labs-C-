
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myEditor.h"
#include "myTable.h"

class QToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onNotify(QAction *action);
private: 
MyEditor *editor;
QToolBar *toolBar;
MyTableWindow* tableWindow = nullptr;
 
};

#endif