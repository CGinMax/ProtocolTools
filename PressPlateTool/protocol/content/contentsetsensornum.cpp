#include "contentsetsensornum.h"

ContentSetSensorNum::ContentSetSensorNum(uint8_t data)
    : num(data)
    , isSuccess(data != 0)
{
    funCode = 0x0A;
}

std::string ContentSetSensorNum::toString(bool isSend)
{
    std::string result = u8"设定传感器数量";
    if (isSend) {
        result += "=" + std::to_string(num);
        return result;
    }

    if (isSuccess) {
        result += u8":失败";
    } else {
        result += u8":成功";
    }

    return result;
}

std::vector<uint8_t> ContentSetSensorNum::toByteVector()
{
    return {num};
}
