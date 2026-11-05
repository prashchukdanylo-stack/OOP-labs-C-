#ifndef MYTABLE_H
#define MYTABLE_H

#include <QDialog>
#include <QTableWidget>
#include <functional>

class QPushButton;
class MyTableWindow : public QDialog {
    Q_OBJECT

private:
    QTableWidget* tableWidget;
    std::function<void(int)> onRowSelectedCallback;
    std::function<void(int, QString&, QString&)> getDataCallback;
    std::function<int()> getCountCallback;
    std::function<void()> onHiddenCallback;
    std::function<void(int)> onDeleteRowCallback;
    QPushButton *deleteButton;

public:
    explicit MyTableWindow(QWidget* parent = nullptr);
    
    void updateTableData();
    
    void setOnRowSelectedCallback(std::function<void(int)> callback) {
        onRowSelectedCallback = callback;
    }
    void setDataCallback(std::function<void(int index, QString &name, QString &coords)> cb) { getDataCallback = cb; }

    void setGetCountCallback(std::function<int()> cb) { getCountCallback = cb; }
    void setOnHiddenCallback(std::function<void()> cb) { onHiddenCallback = cb; }
    void setOnDeleteRowCallback(std::function<void(int)> cb) { onDeleteRowCallback = cb; }

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
};

#endif