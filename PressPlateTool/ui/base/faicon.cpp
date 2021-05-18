#include "faicon.h"

FAIcon *FAIcon::instance()
{
    static FAIcon instance;
    return &instance;
}

QtAwesome *FAIcon::awesome()
{
    return m_awesomeIcon;
}

FAIcon::FAIcon(QObject *parent)
    : QObject(parent)
    , m_awesomeIcon(new QtAwesome(this))
{
    m_awesomeIcon->initFontAwesome();
}

FAIcon::~FAIcon()
{
    delete m_awesomeIcon;
}
