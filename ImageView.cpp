//
// Created by andyroiiid on 12/29/2022.
//

#include "ImageView.h"

#include <QBoxLayout>
#include <QImageReader>

ImageView::ImageView(QWidget *parent)
        : QWidget(parent) {
    m_imageLabel = new QLabel("No image", this);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_infoLabel = new QLabel("Test", this);
    m_infoLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
    m_infoLabel->setMinimumHeight(30);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_imageLabel, 2);
    layout->addWidget(m_infoLabel, 0);
}

void ImageView::resizeEvent(QResizeEvent *event) {
    updateImageLabel();

    QWidget::resizeEvent(event);
}

void ImageView::setImage(const QString &image) {
    m_imageLabel->clear();
    m_infoLabel->clear();

    m_image.load(image);
    if (m_image.isNull()) {
        m_imageLabel->setText(QString("Cannot open image %1").arg(image));
        return;
    }

    m_pixmap = QPixmap::fromImage(m_image);

    updateImageLabel();
}

void ImageView::updateImageLabel() {
    if (m_pixmap.isNull()) {
        return;
    }

    m_imageLabel->setPixmap(m_pixmap.scaled(m_imageLabel->size(), Qt::KeepAspectRatio));
    m_infoLabel->setText(QString("%1 x %2 (%3 alpha)").arg(
            QString::number(m_image.width()),
            QString::number(m_image.height()),
            m_image.hasAlphaChannel() ? QString("with") : QString("no")
    ));
}
