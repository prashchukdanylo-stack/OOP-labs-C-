#include "module1.h"
#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


namespace {
    class SliderDialog : public QDialog {
        public: 
        SliderDialog(QWidget *parent = nullptr, int initialValue = 50) : 
        QDialog(parent), currentValue(initialValue)
        {
        setWindowTitle("Вибір числа (Варіант 1)");
        setModal(true);

        auto *mainLayout = new QVBoxLayout(this);

        valueLabel = new QLabel(QString::number(currentValue), this);
        valueLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(valueLabel);

        slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(1, 100);
        slider->setValue(currentValue);
        mainLayout->addWidget(slider);

        auto *btnLayout = new QHBoxLayout();
        auto *btnOk = new QPushButton("Так", this);
        auto *btnCancel = new QPushButton("Відміна", this);
        btnLayout->addWidget(btnOk);
        btnLayout->addWidget(btnCancel);
        mainLayout->addLayout(btnLayout);

        connect(slider, &QSlider::valueChanged, this, [this](int val) {
            currentValue = val;
            valueLabel->setText(QString::number(val));
        });

        connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
        connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    };

    int getValue() {return currentValue;};

    private:
        QSlider *slider;
        QLabel *valueLabel;
        int currentValue;
    };
};

int mod1Func(QWidget *parent, int *pValue) {
    int startVal = (pValue && *pValue  >= 1 && *pValue <= 100) ? *pValue : 50;
    SliderDialog dlg(parent, startVal);

    if (dlg.exec() == QDialog::Accepted) {
        if (pValue) {
            *pValue = dlg.getValue();
        }
        return 1;
    }
    return 0;
}