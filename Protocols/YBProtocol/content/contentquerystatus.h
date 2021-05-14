#ifndef CONTENTQUERYSTATUS_H
#define CONTENTQUERYSTATUS_H

#include "icontent.h"
#include <array>
class PROTOCOLSSHARED_EXPORT ContentQueryStatus : public IContent
{
public:
    explicit ContentQueryStatus(uint8_t curCode = 0x00, uint8_t m_setCode = 0x00);

    static std::array<std::string, 6> currentStatus;
    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;


    uint8_t currentStatusCode() override {
        return m_currentCode;
    }

    uint8_t configedStatusCode() override {
        return m_setCode;
    }
private:
    uint8_t m_currentCode;
    uint8_t m_setCode;

};

#endif // CONTENTQUERYSTATUS_H
