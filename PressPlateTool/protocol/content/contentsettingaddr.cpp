#include "contentsettingaddr.h"
#include "../utilhelper.h"
ContentSettingAddr::ContentSettingAddr(uint8_t dataCode)
    : code(dataCode)
{

}


std::string ContentSettingAddr::toString(bool isSend)
{
    std::string result = u8"设定地址";
    if (isSend) {
        result += "=" + UtilHelper::num2HexString(code);
        return result;
    }

    if (code == 0x00) {
        result += u8":失败";
    } else {
        result += u8":成功";
    }

    return result;
}

std::vector<uint8_t> ContentSettingAddr::toByteVector()
{
    return {code};
}
