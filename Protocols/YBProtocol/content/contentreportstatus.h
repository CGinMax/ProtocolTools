#ifndef CONTENTREPORTSTATUS_H
#define CONTENTREPORTSTATUS_H

#include "icontent.h"

class PROTOCOLSSHARED_EXPORT ContentReportStatus : public IContent
{
public:
    explicit ContentReportStatus(uint8_t curCode, uint8_t settingCode);

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

#endif // CONTENTREPORTSTATUS_H
