#ifndef UTIL_H
#define UTIL_H

class QString;

class Util
{
public:
    Util();

    static QString num2Hex(int num, int width = 0);
    static unsigned char hexString2Num(const QString& str);
};

#endif // UTIL_H
