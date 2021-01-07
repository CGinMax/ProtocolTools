#include "util.h"
#include <QString>

Util::Util()
{

}

QString Util::num2Hex(int num, int width)
{
    return QString("%1").arg(num, width, 16, QLatin1Char('0')).toUpper();
}

unsigned char Util::hexString2Num(const QString &str)
{
    bool ok = true;
    auto retVal = static_cast<unsigned char>(str.toUInt(&ok, 16));
    return ok ? retVal : 0;
}

