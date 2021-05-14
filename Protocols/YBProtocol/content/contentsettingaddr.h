#ifndef CONTENTSETTINGADDR_H
#define CONTENTSETTINGADDR_H

#include "icontent.h"

class PROTOCOLSSHARED_EXPORT ContentSettingAddr : public IContent
{
public:
    explicit ContentSettingAddr(uint8_t dataCode);

    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;

    uint8_t setAddress() override {
        return m_addr;
    }

    bool success() override {
        return m_isSuccess;
    }

private:
    uint8_t m_addr;
    bool m_isSuccess;
};

#endif // CONTENTSETTINGADDR_H
