#include "contentqueryaddr.h"

ContentQueryAddr::ContentQueryAddr(uint8_t low, uint8_t high)
{
    addr = high;
    addr = static_cast<uint16_t>(addr << 8) | low;
    funCode = 0x91;
}

std::string ContentQueryAddr::toString(bool isSend)
{
    if (isSend) {
        return std::string();
    }

    std::string result = u8"查询地址=";
    result += std::to_string(addr);//hex
    return result;
}

std::vector<uint8_t> ContentQueryAddr::toByteVector()
{
    std::vector<uint8_t> result;
    result.push_back(addr & 0xFF);
    result.push_back((addr >> 8) & 0xFF);
    return result;
}

