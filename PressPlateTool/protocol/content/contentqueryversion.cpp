#include "contentqueryversion.h"

ContentQueryVersion::ContentQueryVersion(const std::vector<uint8_t> &datas)
    : hardwareVer(std::string())
    , softwareVer(std::string())
    , productDesc(std::string())
    , datas(datas)
{
    funCode = 0x04;
    if (datas.empty()) {
        return ;
    }
    auto iter = datas.begin();
    uint8_t verLow = *iter++;
    uint8_t verHeigh = *iter++;
    hardwareVer = std::to_string(verHeigh) + "." + std::to_string(verLow);
    verLow = *iter++;
    verHeigh = *iter++;
    softwareVer = std::to_string(verHeigh) + "." + std::to_string(verLow);
    if (iter == datas.end()) {
        return;
    }

    std::string desc;
    iter++;// 4:0x00
    if (*iter++ == 0x0B) {
        desc = u8"通用款";
    }
    iter++;// 6:0x02
    uint8_t flagLen = *iter++;
    while (iter != datas.end()) {
        productDesc += static_cast<char>(*iter++);
    }

    productDesc += desc;
}

std::string ContentQueryVersion::toString(bool isSend)
{
    if (isSend || datas.empty()) {
        return std::string();
    }

    std::string result;
    uint8_t verLow = datas.at(0);
    uint8_t verHeigh = datas.at(1);
    result += u8"硬件版本=" + std::to_string(verHeigh) + "." + std::to_string(verLow);
    verLow = datas.at(2);
    verHeigh = datas.at(3);
    result += u8", 软件版本=" + std::to_string(verHeigh) + "." + std::to_string(verLow);

    return result;
}

std::vector<uint8_t> ContentQueryVersion::toByteVector()
{
//    return {};
    return datas;
}


std::string ContentQueryVersion::hardwareVersion()
{
    return hardwareVer;
}

std::string ContentQueryVersion::softwareVersion()
{
    return softwareVer;
}

std::string ContentQueryVersion::productDescript()
{
    return productDesc;
}
