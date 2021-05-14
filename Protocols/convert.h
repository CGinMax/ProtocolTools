#ifndef CONVERT_H
#define CONVERT_H

#include <string>
class Convert
{
public:
    Convert();

    static std::string num2HexString(unsigned int num, unsigned int width = 2);
};

#endif // CONVERT_H
