#include "contentsettingstatus.h"

ContentSettingStatus::ContentSettingStatus()
{

}

std::string ContentSettingStatus::toString(const std::vector<uint8_t> &datas, bool isSend)
{
    std::string result;
    if (isSend) {
        switch (datas.at(0)) {
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

    // 接收的
    if (datas.at(0) == 0x00) {
        result += u8"设定失败";
    } else if (datas.at(0) == 0x01) {
        result += u8"设定成功";
    }
    return result;
}
