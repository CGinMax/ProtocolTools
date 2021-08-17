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

QString Util::bytes2String(const char *buffer, int length, int splitNum)
{
    QString bufstr;
    if (length > 0 && buffer != nullptr)
    {
        QString bufstr;
        const uchar *ubuff = (const uchar *)buffer;
        for(int i=0;i<length;i++)
        {
            bufstr.append(QString::number((ubuff[i] >> 4), 16));
            bufstr.append(QString::number(ubuff[i] & 0xF, 16) + " ");
        }
        bufstr = bufstr.trimmed().toUpper();
    }
    if (splitNum == 0) {
        return bufstr;
    }
    int splitPos = 3 * splitNum;
    while (bufstr.size() >= splitPos) {
        bufstr.insert(splitPos, '\n');
        splitPos += 3* splitNum + 1;
    }

    return bufstr;
}

QString Util::bytes2String(const QByteArray &buffer, int splitNum)
{
    QString bufstr(buffer.toHex(' ').toUpper());
    if (splitNum == 0) {
        return bufstr;
    }

    int splitPos = 3 * splitNum;
    while (bufstr.size() >= splitPos) {
        bufstr.insert(splitPos, '\n');
        splitPos += 3* splitNum + 1;
    }

    return bufstr;
}

