#include "mouseevent.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MouseEvent window;
    window.setWindowTitle("Mouse Event Example");
    window.resize(800, 600);
    window.show();

    return app.exec();
}
