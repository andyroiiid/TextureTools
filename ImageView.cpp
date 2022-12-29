//
// Created by andyroiiid on 12/29/2022.
//

#include "ImageView.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QImageReader>

ImageView::ImageView(QWidget *parent, ImageList *imageList)
        : QWidget(parent) {
    m_imageLabel = new QLabel("No image", this);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_imageLabel);

    connect(imageList, &ImageList::currentImageChanged, this, &ImageView::changeImage);
}

void ImageView::resizeEvent(QResizeEvent *event) {
    updateImageLabel();

    QWidget::resizeEvent(event);
}

void ImageView::changeImage(const QString &image) {
    m_imageLabel->clear();

    QImageReader reader(image);

    QImage newImage = reader.read();
    if (newImage.isNull()) {
        m_imageLabel->setText(QString("Cannot open image %1: %2").arg(image, reader.errorString()));
        return;
    }

    m_pixmap = QPixmap::fromImage(newImage);

    updateImageLabel();
}

void ImageView::updateImageLabel() {
    if (m_pixmap.isNull()) {
        return;
    }

    m_imageLabel->setPixmap(m_pixmap.scaled(m_imageLabel->size(), Qt::KeepAspectRatio));
}
