#include "contentsettingstatus.h"

ContentSettingStatus::ContentSettingStatus(uint8_t data)
    : m_status(data)
    , m_isSuccess(data != 0)
{
    m_funCode = 0x02;
}

std::string ContentSettingStatus::toString(bool isSend)
{
    std::string result;
    if (isSend) {
        switch (m_status) {
        case 0x00:
            result += u8"应分";
            break;

        case 0x01:
            result += u8"应合";
            break;

        case 0xFF:
            result += u8"未设定";
            break;
        default:
            break;
        }
        return result;
    }

    // 接收
    result = u8"设定地址:";
    if (m_isSuccess) {
        result += u8"失败";
    } else {
        result += u8"成功";
    }
    return result;
}


std::vector<uint8_t> ContentSettingStatus::toByteVector()
{
    return {m_status};
}
