//
// Created by andyroiiid on 12/29/2022.
//

#include "ImageWorkspace.h"

#include <QDebug>
#include <QBoxLayout>

ImageWorkspace::ImageWorkspace(QWidget *parent)
        : QWidget(parent) {
    m_imageView = new ImageView(this);
    m_toDDSButton = new QPushButton("Convert To DDS", this);

    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_imageView);
    layout->addWidget(m_toDDSButton);

    connect(m_toDDSButton, &QPushButton::pressed, this, &ImageWorkspace::toDDS);
}

void ImageWorkspace::setImage(const QString &image) {
    m_imageFilename = image;
    m_imageView->setImage(image);
}

void ImageWorkspace::toDDS() {
    m_toDDSProcess = new QProcess(this);
    m_toDDSProcess->start("texconv", QStringList{
            "-nologo",
            "-m",
            "1",
            "-f",
            "BC1_UNORM_SRGB",
            "-dx9",
            "-y",
            m_imageFilename
    });
    connect(m_toDDSProcess, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &ImageWorkspace::finishedToDDS);

    m_toDDSButton->setDisabled(true);
}

void ImageWorkspace::finishedToDDS(int exitCode, QProcess::ExitStatus exitStatus) {
    m_toDDSButton->setDisabled(false);

    qInfo().noquote() << QString(m_toDDSProcess->readAllStandardOutput());
    if (exitStatus != QProcess::NormalExit) {
        qInfo().noquote() << QString(m_toDDSProcess->readAllStandardError());
    }

    disconnect(m_toDDSProcess, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &ImageWorkspace::finishedToDDS);
    delete m_toDDSProcess;
    m_toDDSProcess = nullptr;
}
