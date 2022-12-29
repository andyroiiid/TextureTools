//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QListWidget>

class ImageList : public QWidget {
Q_OBJECT
public:
    explicit ImageList(QWidget *parent);

signals:

    void currentImageChanged(const QString &currentImage);

private:
    void add();

    void removeCurrent();

    void clear();

    QListWidget *m_listWidget;

    QStringList m_images;
};
