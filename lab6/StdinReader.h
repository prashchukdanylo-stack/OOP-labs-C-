#pragma once

#include <QThread>
#include <cstdio>
#include <iostream>
#include <string>

class StdinReader : public QThread {
    Q_OBJECT

signals:
    void paramsReceived(int nPoint, int xMin, int xMax, int yMin, int yMax);

protected:
    void run() override {
        std::string line;
        while (std::getline(std::cin, line)) {
            int a, b, c, d, e;
            if (std::sscanf(line.c_str(), "%d %d %d %d %d", &a, &b, &c, &d, &e) == 5)
                emit paramsReceived(a, b, c, d, e);
        }
    }
};