//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class ImageView : public QWidget {
Q_OBJECT
public:
    explicit ImageView(QWidget *parent);

    void resizeEvent(QResizeEvent *event) override;

    void setImage(const QString &image);

private:
    void updateImageLabel();

    QLabel *m_imageLabel;
    QLabel *m_infoLabel;

    QImage m_image;
    QPixmap m_pixmap;
};
