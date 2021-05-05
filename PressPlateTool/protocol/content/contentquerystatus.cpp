#include "contentquerystatus.h"

std::array<std::string, 6> ContentQueryStatus::currentStatus{u8"分", u8"合", u8"误分", u8"误合", u8"等待分", u8"等待合"};

ContentQueryStatus::ContentQueryStatus()
{

}

std::string ContentQueryStatus::toString(const std::vector<uint8_t> &datas, bool isSend)
{
    if (isSend || datas.empty()) {
        return std::string();
    }

    std::string result = u8"目前状态=";
    result += currentStatus[datas.at(0)];
    result += ", 已配置的状态=";
    switch (datas.at(1)) {
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
