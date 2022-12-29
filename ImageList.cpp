//
// Created by andyroiiid on 12/29/2022.
//

#include "ImageList.h"

#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QBoxLayout>

ImageList::ImageList(QWidget *parent)
        : QWidget(parent) {
    m_listWidget = new QListWidget(this);

    auto addButton = new QPushButton("Add", this);
    auto removeButton = new QPushButton("Remove", this);
    auto clearButton = new QPushButton("Clear", this);

    auto buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(clearButton);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_listWidget);
    layout->addLayout(buttonsLayout);

    connect(m_listWidget, &QListWidget::currentTextChanged, this, &ImageList::currentImageChanged);
    connect(addButton, &QPushButton::pressed, this, &ImageList::add);
    connect(removeButton, &QPushButton::pressed, this, &ImageList::removeCurrent);
    connect(clearButton, &QPushButton::pressed, this, &ImageList::clear);
}

void ImageList::add() {
    QStringList images = QFileDialog::getOpenFileNames(
            this,
            "Add Textures",
            {},
            "Texture Files (*.jpg *.png *.hdr)"
    );

    m_images.append(images);
    m_images.removeDuplicates();
    m_images.sort();

    m_listWidget->clear();
    m_listWidget->addItems(m_images);
}

void ImageList::removeCurrent() {
    if (m_images.empty()) return;

    m_images.removeAt(m_listWidget->currentRow());

    delete m_listWidget->takeItem(m_listWidget->currentRow());
}

void ImageList::clear() {
    m_images.clear();

    m_listWidget->clear();
}
