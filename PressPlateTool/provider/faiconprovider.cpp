#include "faiconprovider.h"
#include <QPixmap>
#include <QImage>
FAIconProvider::FAIconProvider(ImageType type)
    : QQuickImageProvider(type)
{
    _fa.initFontAwesome();
}

FAIconProvider::~FAIconProvider()
{

}

QImage FAIconProvider::requestImage(const QString &name, QSize *size, const QSize &requestedSize)
{
    auto icon = _fa.icon(name);
    auto pixmap = icon.pixmap(requestedSize);
    *size = pixmap.size();
    return pixmap.toImage();
}

QPixmap FAIconProvider::requestPixmap(const QString &name, QSize *size, const QSize &requestedSize)
{
    auto icon = _fa.icon(name);
    auto pixmap = icon.pixmap(requestedSize);
    *size = pixmap.size();
    return pixmap;
}
