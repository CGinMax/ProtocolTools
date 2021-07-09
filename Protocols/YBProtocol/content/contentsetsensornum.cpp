#include "contentsetsensornum.h"

ContentSetSensorNum::ContentSetSensorNum(uint8_t data)
    : m_num(data)
    , m_isSuccess(data != 0)
{
    m_funCode = 0x0A;
}

std::string ContentSetSensorNum::toString(bool isSend)
{
    std::string result = u8"设定传感器数量";
    if (isSend) {
        result += "=" + std::to_string(m_num);
        return result;
    }

    result += m_isSuccess ? u8"成功" : u8"失败";
    return result;
}

std::vector<uint8_t> ContentSetSensorNum::toByteVector()
{
    return {m_num};
}
