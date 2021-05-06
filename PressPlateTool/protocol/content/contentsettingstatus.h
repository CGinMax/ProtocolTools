#ifndef CONTENTSETTINGSTATUS_H
#define CONTENTSETTINGSTATUS_H

#include "icontent.h"

class ContentSettingStatus : public IContent
{
public:
    explicit ContentSettingStatus(uint8_t statusCode);
    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;

private:
    uint8_t statusCode;

};

#endif // CONTENTSETTINGSTATUS_H
