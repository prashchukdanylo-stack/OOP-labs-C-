#pragma once

#include <QMainWindow>
#include <QProcess>

class MainWindow : public QMainWindow {
    Q_OBJECT
    QProcess *procObject2;
    QProcess *procObject3;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStartWorkflow();
};