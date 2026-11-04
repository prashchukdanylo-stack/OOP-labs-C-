#include "myTable.h"
#include "myEditor.h"
#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>

MyTableWindow::MyTableWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Таблиця об'єктів");
    resize(450, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"№", "Тип фігури", "Координати"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(tableWidget);

    connect(tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        if (!onRowSelectedCallback) return;

        QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();
        int row = selectedItems.isEmpty() ? -1 : tableWidget->row(selectedItems.first());
        onRowSelectedCallback(row);
    });
}

void MyTableWindow::updateTableData() {
    MyEditor *editor = MyEditor::getInstance();
    if (!editor) {
        tableWidget->setRowCount(0);
        return;
    }

    tableWidget->blockSignals(true);
    int count = editor->getShapeCount();

    tableWidget->clearSelection();
    tableWidget->setRowCount(count);

    for (int i = 0; i < count; ++i) {
        Shape *shape = editor->getShape(i);

        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));

        if (shape) {
            tableWidget->setItem(i, 1, new QTableWidgetItem(shape->getShapeName()));
            tableWidget->setItem(i, 2, new QTableWidgetItem(shape->getCoordinates()));
        }
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
    MyEditor::getInstance()->selectShapeByIndex(-1);
}