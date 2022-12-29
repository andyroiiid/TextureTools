#include <QApplication>
#include <QStyleFactory>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow window;
    window.showMaximized();

    return QApplication::exec();
}
