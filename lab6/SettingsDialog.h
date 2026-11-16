#pragma once

#include <QDialog>
#include <QSpinBox>

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    QSpinBox *spinNPoint;
    QSpinBox *spinXMin, *spinXMax;
    QSpinBox *spinYMin, *spinYMax;

    explicit SettingsDialog(QWidget *parent = nullptr);
};