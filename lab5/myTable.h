#ifndef MYTABLE_H
#define MYTABLE_H

#include <QDialog>
#include <QTableWidget>
#include <functional>

class MyTableWindow : public QDialog {
    Q_OBJECT

private:
    QTableWidget* tableWidget;
    std::function<void(int)> onRowSelectedCallback;

public:
    explicit MyTableWindow(QWidget* parent = nullptr);
    
    void updateTableData();
    
    void setOnRowSelectedCallback(std::function<void(int)> callback) {
        onRowSelectedCallback = callback;
    }

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
};

#endif // MYTABLE_H