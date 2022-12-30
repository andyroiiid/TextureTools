//
// Created by andyroiiid on 12/29/2022.
//

#include "StbImageIOPlugin.h"
#include "StbImageIOHandler.h"

QImageIOPlugin::Capabilities StbImageIOPlugin::capabilities(QIODevice *device, const QByteArray &format) const {
    QFlags<Capability> capabilities;

    return capabilities;
}

QImageIOHandler *StbImageIOPlugin::create(QIODevice *device, const QByteArray &format) const {
    auto handler = new StbImageIOHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}
