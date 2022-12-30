#include <QApplication>
#include <QStyleFactory>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("TextureTools");
    QApplication::setOrganizationName("AndrewHuang");
    QApplication::setOrganizationDomain("andrewhuang.llc");
    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow window;
    window.show();

    return QApplication::exec();
}
