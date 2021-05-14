#include "convert.h"
#include <iostream>
#include <sstream>

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
    return result;
}
