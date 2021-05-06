#include "contentforcesetaddr.h"
#include "../utilhelper.h"

ContentForceSetAddr::ContentForceSetAddr(uint8_t low, uint8_t high)
{
    addr = high;
    addr = static_cast<uint16_t>(addr << 8) | low;

}


std::string ContentForceSetAddr::toString(bool isSend)
{
    (void)isSend;
    std::string result = u8"设定从机地址=";
    result += UtilHelper::num2HexString(addr);
    return result;
}

std::vector<uint8_t> ContentForceSetAddr::toByteVector()
{
    std::vector<uint8_t> result;
    result.push_back(addr & 0xFF);
    result.push_back((addr >> 8) & 0xFF);
    return result;
}
