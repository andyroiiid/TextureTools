//
// Created by andyroiiid on 12/29/2022.
//

#include "MainWindow.h"

#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setWindowTitle("Texture Tools");
    resize(1280, 720);

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_imageList = new ImageList(centralWidget);
    m_imageWorkSpace = new ImageWorkspace(centralWidget);

    auto layout = new QHBoxLayout(centralWidget);
    layout->addWidget(m_imageList, 1);
    layout->addWidget(m_imageWorkSpace, 2);

    connect(m_imageList, &ImageList::currentImageChanged, m_imageWorkSpace, &ImageWorkspace::setImage);
}
