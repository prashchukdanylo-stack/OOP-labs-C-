#include "myTable.h"
#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>

MyTableWindow::MyTableWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Таблиця об'єктів");
    resize(450, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"№", "Тип фігури", "Координати"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(tableWidget);

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    deleteButton = new QPushButton("Видалити", this);
    buttonLayout->addWidget(deleteButton);

    layout->addLayout(buttonLayout);
    connect(deleteButton, &QPushButton::clicked, this, [this](){
        if (!onDeleteRowCallback) return;
        int row = tableWidget->currentRow();
        if (row >= 0) {
            onDeleteRowCallback(row);
        }

    });

    connect(tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        if (!onRowSelectedCallback) return;

        QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();
        int row = selectedItems.isEmpty() ? -1 : tableWidget->row(selectedItems.first());
        onRowSelectedCallback(row);
    });
}

void MyTableWindow::updateTableData() {
    if (!getCountCallback || !getDataCallback) {
        tableWidget->setRowCount(0);
        return;
    }

    tableWidget->blockSignals(true);
    int count = getCountCallback();

    tableWidget->clearSelection();
    tableWidget->setRowCount(count);

    for (int i = 0; i < count; ++i) {
        QString name, coords;
        getDataCallback(i, name, coords);

        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));

            tableWidget->setItem(i, 1, new QTableWidgetItem(name));
            tableWidget->setItem(i, 2, new QTableWidgetItem(coords));
    }
    tableWidget->blockSignals(false);
}

void MyTableWindow::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    updateTableData();

    if (onRowSelectedCallback) {
        QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();
        int row = selectedItems.isEmpty() ? -1 : tableWidget->row(selectedItems.first());
        onRowSelectedCallback(row);
    }
}

void MyTableWindow::hideEvent(QHideEvent *event) {
    QDialog::hideEvent(event);
    if (onHiddenCallback) {
        onHiddenCallback();
    }
}