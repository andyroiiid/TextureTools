//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QImageIOHandler>

class StbImageIOHandler : public QImageIOHandler {
public:
    [[nodiscard]] bool canRead() const override;

    bool read(QImage *image) override;
};
