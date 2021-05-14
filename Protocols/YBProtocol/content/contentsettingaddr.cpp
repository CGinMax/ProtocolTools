#include "contentsettingaddr.h"
#include "../../convert.h"
ContentSettingAddr::ContentSettingAddr(uint8_t dataCode)
    : m_addr(dataCode)
    , m_isSuccess(dataCode != 0)
{
    m_funCode = 0x05;
}


std::string ContentSettingAddr::toString(bool isSend)
{
    std::string result = u8"设定地址";
    if (isSend) {
        result += "=" + Convert::num2HexString(m_addr);
        return result;
    }

    if (m_isSuccess) {
        result += u8":失败";
    } else {
        result += u8":成功";
    }

    return result;
}

std::vector<uint8_t> ContentSettingAddr::toByteVector()
{
    return {m_addr};
}
