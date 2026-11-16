#include <QApplication>
#include "Object2Window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int nPoint = 10;
    int xMin = 0, xMax = 50;
    int yMin = 0, yMax = 100;

    if (argc >= 6) {
        nPoint = QString(argv[1]).toInt();
        xMin = QString(argv[2]).toInt();
        xMax = QString(argv[3]).toInt();
        yMin = QString(argv[4]).toInt();
        yMax = QString(argv[5]).toInt();
    }

    Object2Window w(nPoint, xMin, xMax, yMin, yMax);
    w.show();
    return app.exec();
}