#include "module2.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace
{

    class TextDialog : public QDialog
    {
    public:
        TextDialog(QWidget *parent = nullptr, const QString &initialText = "") : QDialog(parent)
        {
            setWindowTitle("Введення тексту (0 варіант)");
            setModal(true);
            auto *mainLayout = new QVBoxLayout(this);
            lineEdit = new QLineEdit(this);
            lineEdit->setText(initialText);
            lineEdit->setPlaceholderText("Введфть текст");
            mainLayout->addWidget(lineEdit);

            auto *btnLayout = new QHBoxLayout();
            auto *btnOk = new QPushButton("Так", this);
            auto *btnCancel = new QPushButton("Відміна", this);
            btnLayout->addWidget(btnOk);
            btnLayout->addWidget(btnCancel);
            mainLayout->addLayout(btnLayout);

            connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
            connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
        };
        QString getText() {return lineEdit->text();};

    private:
        QLineEdit *lineEdit;
    };

};

int mod2Func(QWidget *parent, QString *pText) {
    TextDialog dlg(parent, pText ? *pText : QString());

    if (dlg.exec() == QDialog::Accepted) {
        if (pText) {
            *pText = dlg.getText();
        }
        return 1;
    }
    return 0;
};