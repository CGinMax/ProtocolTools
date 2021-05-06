#ifndef CONTENTREPORTSTATUS_H
#define CONTENTREPORTSTATUS_H

#include "icontent.h"

class ContentReportStatus : public IContent
{
public:
    explicit ContentReportStatus(uint8_t curCode, uint8_t settingCode);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

private:
    uint8_t currentCode;
    uint8_t setCode;
};

#endif // CONTENTREPORTSTATUS_H
