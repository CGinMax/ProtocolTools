#include "contentsettingaddr.h"
#include "../utilhelper.h"
ContentSettingAddr::ContentSettingAddr(uint8_t dataCode)
    : addr(dataCode)
    , isSuccess(dataCode != 0)
{
    funCode = 0x05;
}


std::string ContentSettingAddr::toString(bool isSend)
{
    std::string result = u8"设定地址";
    if (isSend) {
        result += "=" + UtilHelper::num2HexString(addr);
        return result;
    }

    if (isSuccess) {
        result += u8":失败";
    } else {
        result += u8":成功";
    }

    return result;
}

std::vector<uint8_t> ContentSettingAddr::toByteVector()
{
    return {addr};
}