#include "convert.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

Convert::Convert()
{

}

std::string Convert::num2HexString(unsigned int num, unsigned int width)
{
    std::stringstream ioss;     //定义字符串流
    std::string hexStr;         //存放转化后字符
    ioss << std::hex << num;      //以十六制形式输出
    ioss >> hexStr;

    if(width > hexStr.size())
    {
        std::string str0(width - hexStr.size(), '0');      //位数不够则补0
        hexStr = str0 + hexStr;                            //合并
    }

    std::string result = hexStr.substr(hexStr.length() - width, hexStr.length());    //取右width位
    std::transform(result.begin(), result.end(), result.begin(), toupper);
    return result;
}

std::string Convert::bytes2String(const std::vector<uint8_t> &buffer, int splitNum)
{
    std::string result;

    for (auto& data : buffer) {
        result += num2HexString(data >> 4, 1);
        result += num2HexString(data & 0x0F, 1) + " ";
    }

    if (splitNum == 0) {
        return result;
    }

    auto splitPos = static_cast<size_t>(3 * splitNum);
    while (result.size() >= splitPos) {
        result.insert(splitPos, "\n");
        splitPos += static_cast<size_t>(3 * splitNum + 1);
    }
    return result;
}
