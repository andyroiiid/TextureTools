//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QImageIOPlugin>

class StbImageIOPlugin : public QImageIOPlugin {
Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QImageIOHandlerFactoryInterface" FILE "StbImageIOPlugin.json")

public:
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const override;

    QImageIOHandler *create(QIODevice *device, const QByteArray &format) const override;
};
