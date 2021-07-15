#include "contentqueryaddr.h"

ContentQueryAddr::ContentQueryAddr(uint8_t low, uint8_t high)
{
    m_addr = high;
    m_addr = static_cast<uint16_t>(m_addr << 8) | low;
    m_funCode = 0x91;
}

std::string ContentQueryAddr::toString(bool isSend)
{
    if (isSend) {
        return std::string();
    }

    std::string result = u8",查询地址=";
    result += std::to_string(m_addr);//hex
    return result;
}

std::vector<uint8_t> ContentQueryAddr::toByteVector()
{
    std::vector<uint8_t> result;
    result.push_back(m_addr & 0xFF);
    result.push_back((m_addr >> 8) & 0xFF);
    return result;
}

