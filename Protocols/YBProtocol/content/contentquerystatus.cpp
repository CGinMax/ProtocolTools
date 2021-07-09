#include "contentquerystatus.h"

std::array<std::string, 6> ContentQueryStatus::currentStatus{u8"分", u8"合", u8"误分", u8"误合", u8"等待分", u8"等待合"};

ContentQueryStatus::ContentQueryStatus(uint8_t curCode, uint8_t setCode)
    : m_currentCode(curCode)
    , m_setCode(setCode)
{
    m_funCode = 0x03;
}

std::string ContentQueryStatus::toString(bool isSend)
{
    if (isSend) {
        return std::string();
    }

    std::string result = u8"目前状态=";
    result += getStatusSafe(m_currentCode);
    result += ", 已配置的状态=";
    switch (m_setCode) {
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

std::vector<uint8_t> ContentQueryStatus::toByteVector()
{
    return {m_currentCode, m_setCode};
}

std::string ContentQueryStatus::getStatusSafe(uint8_t status)
{
    if (status >= currentStatus.size()) {
        return u8"未知状态";
    }
    return currentStatus[status];
}
