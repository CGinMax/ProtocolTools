#include "contentforcesetaddr.h"
#include "../utilhelper.h"

ContentForceSetAddr::ContentForceSetAddr(uint8_t low, uint8_t high)
{
    m_addr = high;
    m_addr = static_cast<uint16_t>(m_addr << 8) | low;
    m_funCode = 0x90;
}


std::string ContentForceSetAddr::toString(bool isSend)
{
    (void)isSend;
    std::string result = u8"设定从机地址=";
    result += UtilHelper::num2HexString(m_addr);
    return result;
}

std::vector<uint8_t> ContentForceSetAddr::toByteVector()
{
    std::vector<uint8_t> result;
    result.push_back(m_addr & 0xFF);
    result.push_back((m_addr >> 8) & 0xFF);
    return result;
}

