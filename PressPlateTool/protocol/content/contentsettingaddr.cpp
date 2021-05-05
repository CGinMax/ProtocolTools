#include "contentsettingaddr.h"

ContentSettingAddr::ContentSettingAddr()
{

}


std::string ContentSettingAddr::toString(const std::vector<uint8_t> &datas, bool isSend)
{
    if (isSend || datas.empty()) {
        return std::string();
    }

    std::string result = u8"设定地址";
    if (datas.at(0) == 0x00) {
        result += u8"失败";
    } else {
        result += u8"成功";
    }

    return result;
}
