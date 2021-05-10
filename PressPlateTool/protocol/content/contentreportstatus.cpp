#include "contentreportstatus.h"
#include "contentquerystatus.h"

ContentReportStatus::ContentReportStatus(uint8_t curCode, uint8_t settingCode)
    : currentCode(curCode)
    , setCode(settingCode)
{
    funCode = 0x06;
}

std::string ContentReportStatus::toString(bool isSend)
{
    if (isSend) {
        return std::string();
    }

    std::string result = u8"目前状态:";
    result += ContentQueryStatus::currentStatus[currentCode];
    result += u8", 已配置的状态:";
    switch (setCode) {
    case 0x00:
        result += u8"分";
        break;
    case 0x01:
        result += u8"合";
        break;
    default:
        result += u8"未设定";
        break;
    }

    return result;
}

std::vector<uint8_t> ContentReportStatus::toByteVector()
{
    return {currentCode, setCode};
}
