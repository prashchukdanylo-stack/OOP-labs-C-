#include <QApplication>
#include "Object3Window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Object3Window w;
    w.show();
    return app.exec();
}