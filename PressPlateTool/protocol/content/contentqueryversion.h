#ifndef CONTENTQUERYVERSION_H
#define CONTENTQUERYVERSION_H

#include "icontent.h"

class ContentQueryVersion : public IContent
{
public:
    explicit ContentQueryVersion(const std::vector<uint8_t>& datas);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

    std::string hardwareVersion() override;
    std::string softwareVersion() override;
    std::string productDescript() override;
private:
    std::string hardwareVer;
    std::string softwareVer;
    std::string productDesc;
    std::vector<uint8_t> datas;

};

#endif // CONTENTQUERYVERSION_H
