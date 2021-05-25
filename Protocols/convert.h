#ifndef CONVERT_H
#define CONVERT_H

#include <string>
#include <vector>
#include "protocols_global.h"

class PROTOCOLSSHARED_EXPORT Convert
{
public:
    Convert();

    /**
     * @brief num2HexString 十进制转十六进制字符串
     * @param num           十进制数
     * @param width         十六进制字符串宽度
     * @return
     */
    static std::string num2HexString(unsigned int num, unsigned int width = 2);

    static std::string bytes2String(const std::vector<uint8_t>& buffer, int splitNum = 0);
};

#endif // CONVERT_H
