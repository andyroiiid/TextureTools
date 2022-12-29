//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include "ImageList.h"

class ImageView : public QWidget {
Q_OBJECT
public:
    ImageView(QWidget *parent, ImageList *imageList);

    void resizeEvent(QResizeEvent *event) override;

private:
    void changeImage(const QString &image);

    void updateImageLabel();

    QPixmap m_pixmap;
    QLabel *m_imageLabel;
};
