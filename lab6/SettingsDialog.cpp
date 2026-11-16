#include "SettingsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Параметри генерації (Варіант 0)");
    resize(320, 220);
    move(100, 400);

    auto *layout = new QFormLayout(this);
    
    spinNPoint = new QSpinBox(this);
    spinNPoint->setRange(2, 100);
    spinNPoint->setValue(10);

    spinXMin = new QSpinBox(this);
    spinXMin->setRange(-500, 500);
    spinXMin->setValue(0);

    spinXMax = new QSpinBox(this);
    spinXMax->setRange(-500, 500);
    spinXMax->setValue(50);

    spinYMin = new QSpinBox(this);
    spinYMin->setRange(-500, 500);
    spinYMin->setValue(0);

    spinYMax = new QSpinBox(this);
    spinYMax->setRange(-500, 500);
    spinYMax->setValue(100);

    layout->addRow("Кількість точок (nPoint):", spinNPoint);
    layout->addRow("X мінімум (xMin):", spinXMin);
    layout->addRow("X максимум (xMax):", spinXMax);
    layout->addRow("Y мінімум (yMin):", spinYMin);
    layout->addRow("Y максимум (yMax):", spinYMax);

    auto *btnLayout = new QHBoxLayout();
    auto *btnOk = new QPushButton("Виконати", this);
    auto *btnCancel = new QPushButton("Скасувати", this);
    btnOk->setDefault(true);

    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);
    layout->addRow(btnLayout);

    connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}