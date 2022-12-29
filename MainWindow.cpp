//
// Created by andyroiiid on 12/29/2022.
//

#include "MainWindow.h"

#include <QBoxLayout>

#include "ImageView.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setWindowTitle("Texture Tools");
    resize(1280, 720);

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_imageList = new ImageList(centralWidget);
    m_imageView = new ImageView(centralWidget);

    auto layout = new QHBoxLayout(centralWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_imageList, 1);
    layout->addWidget(m_imageView, 2);

    connect(m_imageList, &ImageList::currentImageChanged, m_imageView, &ImageView::setImage);
}
