//
// Created by andyroiiid on 12/29/2022.
//

#include "StbImageIOHandler.h"

#include <QImage>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

bool StbImageIOHandler::canRead() const {
    return true;
}

bool StbImageIOHandler::read(QImage *image) {
    const QByteArray binary = device()->readAll();

    int width, height, channels;
    stbi_uc *data = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(binary.data()), binary.size(), &width, &height, &channels, 0);
    if (data == nullptr) {
        return false;
    }

    if (channels == 0 || channels == 2) {
        stbi_image_free(data);
        return false;
    }

    QImage::Format formats[5] = {
            QImage::Format::Format_Invalid,
            QImage::Format::Format_Mono,
            QImage::Format::Format_Invalid,
            QImage::Format::Format_RGB888,
            QImage::Format::Format_RGBA8888
    };

    *image = QImage(data, width, height, formats[channels], stbi_image_free, data);
    return true;
}
