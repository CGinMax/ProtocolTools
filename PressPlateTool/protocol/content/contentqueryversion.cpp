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
    uint8_t verLow = datas.at(0);
    uint8_t verHeigh = datas.at(1);
    hardwareVer = std::to_string(verHeigh) + "." + std::to_string(verLow);
    verLow = datas.at(2);
    verHeigh = datas.at(3);
    softwareVer = std::to_string(verLow) + "." + std::to_string(verLow);
//    std::string desc;
//    if (datas.at(5) == 0x0B) {
//        desc = u8"通用款";
//    }
//    uint8_t flagLen = datas.at(7);
//    for (size_t i = 0; i < flagLen; i++) {
//        productDesc += static_cast<char>(datas.at(8 + i));
//    }
//    productDesc += desc;
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
