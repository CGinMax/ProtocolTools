#ifndef UTIL_H
#define UTIL_H

class QString;
class QByteArray;

class Util
{
public:
    Util();

    static QString num2Hex(int num, int width = 0);
    static unsigned char hexString2Num(const QString& str);

    static QString bytes2String(const char *buffer, int length, int splitNum = 0);
    static QString bytes2String(const QByteArray& buffer, int splitNum = 0);
};

#endif // UTIL_H
