#include "contentqueryversion.h"

ContentQueryVersion::ContentQueryVersion()
{

}

std::string ContentQueryVersion::toString(const std::vector<uint8_t> &datas, bool isSend)
{
    if (isSend || datas.empty()) {
        return std::string();
    }

    std::string result;
    uint8_t verLow = datas.at(0);
    uint8_t verHeigh = datas.at(1);
    result = result + u8"硬件版本=" + std::to_string(verHeigh) + "." + std::to_string(verLow);
    verLow = datas.at(2);
    verHeigh = datas.at(3);
    result += u8", 软件版本=" + std::to_string(verHeigh) + "." + std::to_string(verLow);

    return result;
}
