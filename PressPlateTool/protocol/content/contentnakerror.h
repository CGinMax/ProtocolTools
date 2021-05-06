#ifndef CONTENTNAKERROR_H
#define CONTENTNAKERROR_H

#include "icontent.h"
class ContentNAKError : public IContent
{
public:
    explicit ContentNAKError(uint8_t funCode, uint8_t errorCode);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

private:
    uint8_t funCode;
    uint8_t errorCode;
};

#endif // CONTENTNAKERROR_H
