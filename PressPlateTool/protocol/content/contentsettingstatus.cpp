#include "contentsettingstatus.h"

ContentSettingStatus::ContentSettingStatus(uint8_t statusCode)
    : statusCode(statusCode)
{

}

std::string ContentSettingStatus::toString(bool isSend)
{
    std::string result;
    if (isSend) {
        switch (statusCode) {
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
    if (statusCode == 0x00) {
        result += u8"设定失败";
    } else if (statusCode == 0x01) {
        result += u8"设定成功";
    }
    return result;
}


std::vector<uint8_t> ContentSettingStatus::toByteVector()
{
    return {statusCode};
}
