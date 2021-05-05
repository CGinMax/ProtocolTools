#ifndef CONTENTQUERYADDR_H
#define CONTENTQUERYADDR_H

#include "icontent.h"

class ContentQueryAddr : public IContent
{
public:
    ContentQueryAddr();

    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTQUERYADDR_H
