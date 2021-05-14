#ifndef CONTENTQUERYVERSION_H
#define CONTENTQUERYVERSION_H

#include "icontent.h"

class PROTOCOLSSHARED_EXPORT ContentQueryVersion : public IContent
{
public:
    explicit ContentQueryVersion(const std::vector<uint8_t>& m_datas);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

    std::string hardwareVersion() override;
    std::string softwareVersion() override;
    std::string productDescript() override;
private:
    std::string m_hardwareVer;
    std::string m_softwareVer;
    std::string m_productDesc;
    std::vector<uint8_t> m_datas;

};

#endif // CONTENTQUERYVERSION_H
