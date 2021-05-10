#include "contentsettingstatus.h"

ContentSettingStatus::ContentSettingStatus(uint8_t data)
    : status(data)
    , isSuccess(data != 0)
{
    funCode = 0x02;
}

std::string ContentSettingStatus::toString(bool isSend)
{
    std::string result;
    if (isSend) {
        switch (status) {
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
    if (isSuccess) {
        result += u8"失败";
    } else {
        result += u8"成功";
    }
    return result;
}


std::vector<uint8_t> ContentSettingStatus::toByteVector()
{
    return {status};
}
