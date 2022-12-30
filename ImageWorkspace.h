//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QWidget>
#include <QProcess>
#include <QPushButton>

#include "ImageView.h"

class ImageWorkspace : public QWidget {
Q_OBJECT
public:
    explicit ImageWorkspace(QWidget *parent);

    void setImage(const QString &image);

private:
    void toDDS();

    void finishedToDDS(int exitCode, QProcess::ExitStatus exitStatus);

    void toRGBM();

    ImageView *m_imageView;
    QPushButton *m_toDDSButton;
    QPushButton *m_toRGBMButton;

    QString m_imageFilename;

    QProcess *m_toDDSProcess = nullptr;
};
