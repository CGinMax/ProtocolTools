#ifndef UTILHELPER_H
#define UTILHELPER_H

#include <string>

class UtilHelper
{
public:
    UtilHelper();

    static std::string num2HexString(unsigned int num, unsigned int width = 2);
};

#endif // UTILHELPER_H
