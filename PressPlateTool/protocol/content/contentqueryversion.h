#ifndef CONTENTQUERYVERSION_H
#define CONTENTQUERYVERSION_H

#include "icontent.h"

class ContentQueryVersion : public IContent
{
public:
    explicit ContentQueryVersion(const std::vector<uint8_t>& datas);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

private:
    std::vector<uint8_t> datas;
};

#endif // CONTENTQUERYVERSION_H
