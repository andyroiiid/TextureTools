//
// Created by andyroiiid on 12/29/2022.
//

#include "ImageWorkspace.h"

#include <QDebug>
#include <QBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <stb_image.h>

ImageWorkspace::ImageWorkspace(QWidget *parent)
        : QWidget(parent) {
    m_imageView = new ImageView(this);

    auto buttons = new QWidget(this);
    m_toDDSButton = new QPushButton("Convert to DDS", buttons);
    m_toRGBMButton = new QPushButton("Convert to RGBM", buttons);
    auto buttonsLayout = new QHBoxLayout(buttons);
    buttonsLayout->setMargin(0);
    buttonsLayout->addWidget(m_toDDSButton);
    buttonsLayout->addWidget(m_toRGBMButton);

    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_imageView);
    layout->addWidget(buttons);

    connect(m_toDDSButton, &QPushButton::pressed, this, &ImageWorkspace::toDDS);
    connect(m_toRGBMButton, &QPushButton::pressed, this, &ImageWorkspace::toRGBM);
}

void ImageWorkspace::setImage(const QString &image) {
    m_imageFilename = image;
    m_imageView->setImage(image);

    m_toRGBMButton->setEnabled(QFileInfo(image).suffix() == "hdr");
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

void RGBMEncode(float &r, float &g, float &b, float &a) {
    static constexpr float RGBM_MAX_RANGE = 6.0f;
    static constexpr float RGBM_SCALE = 1.0f / RGBM_MAX_RANGE;

    r = std::min(r * RGBM_SCALE, 1.0f);
    g = std::min(g * RGBM_SCALE, 1.0f);
    b = std::min(b * RGBM_SCALE, 1.0f);

    a = std::min(std::max(std::max(r, g), std::max(b, 1e-6f)), 1.0f);
    a = std::ceil(a * 255.0f) / 255.0f;

    r /= a;
    g /= a;
    b /= a;
}

void ImageWorkspace::toRGBM() {
    int width, height;
    float *hdrData = stbi_loadf(m_imageFilename.toStdString().c_str(), &width, &height, nullptr, STBI_rgb);

    std::vector<uint8_t> pixels;
    pixels.resize(width * height * 4);
    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float r = hdrData[3 * i + 0];
            float g = hdrData[3 * i + 1];
            float b = hdrData[3 * i + 2];
            float a;

            RGBMEncode(r, g, b, a);

            pixels[4 * i + 0] = uint8_t(r * 255.0f);
            pixels[4 * i + 1] = uint8_t(g * 255.0f);
            pixels[4 * i + 2] = uint8_t(b * 255.0f);
            pixels[4 * i + 3] = uint8_t(a * 255.0f);

            i++;
        }
    }
    QImage image(pixels.data(), width, height, QImage::Format::Format_RGBA8888);

    QString outputImage = QFileDialog::getSaveFileName(
            this,
            "Convert to RGBM texture",
            {},
            "PNG File (*.png)"
    );
    image.save(outputImage);
}
