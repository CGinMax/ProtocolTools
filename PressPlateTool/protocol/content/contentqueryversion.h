#ifndef CONTENTQUERYVERSION_H
#define CONTENTQUERYVERSION_H

#include "icontent.h"

class ContentQueryVersion : public IContent
{
public:
    ContentQueryVersion();

    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTQUERYVERSION_H
