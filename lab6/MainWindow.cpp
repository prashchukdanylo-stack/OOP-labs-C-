#include "MainWindow.h"
#include "SettingsDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Lab6 - Менеджер (Варіант 0)");
    resize(400, 200);
    move(100,100);

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    auto *btnStart = new QPushButton("Ввести параметри та запустити систему", this);
    layout->addWidget(btnStart);

    setCentralWidget(centralWidget);

    procObject2 = new QProcess(this);
    procObject3 = new QProcess(this);

    connect(btnStart, &QPushButton::clicked, this, &MainWindow::onStartWorkflow);
}

MainWindow::~MainWindow() {
    if (procObject2->state() == QProcess::Running) {
        procObject2->terminate();
        procObject2->waitForFinished(1000);
    }
    if (procObject3->state() == QProcess::Running) {
        procObject3->terminate();
        procObject3->waitForFinished(1000);
    }
}

void MainWindow::onStartWorkflow() {
    SettingsDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;

    if (procObject2->state() == QProcess::NotRunning) {
        procObject2->start("./Object2");
    }
    if (procObject3->state() == QProcess::NotRunning) {
        procObject3->start("./Object3");
    }

    int nPoint = dlg.spinNPoint->value();
    int xMin = dlg.spinXMin->value();
    int xMax = dlg.spinXMax->value();
    int yMin = dlg.spinYMin->value();
    int yMax = dlg.spinYMax->value();

    QByteArray args = QString("%1 %2 %3 %4 %5\n").arg(nPoint).arg(xMin).arg(xMax).arg(yMin).arg(yMax).toUtf8();

    if (procObject2->state() == QProcess::Running) {
        procObject2->write(args);
    }

}