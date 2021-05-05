#include "contentqueryaddr.h"

ContentQueryAddr::ContentQueryAddr()
{

}


std::string ContentQueryAddr::toString(const std::vector<uint8_t> &datas, bool isSend)
{
    if (isSend || datas.empty()) {
        return std::string();
    }

    std::string result = u8"查询地址=";
    uint16_t addr = datas.at(0);
    addr = (addr << 8) | datas.at(1);

    result += std::to_string(addr) + "()";//hex
    return result;
}
