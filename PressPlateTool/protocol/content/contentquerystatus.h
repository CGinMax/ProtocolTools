#ifndef CONTENTQUERYSTATUS_H
#define CONTENTQUERYSTATUS_H

#include "icontent.h"
#include <array>
class ContentQueryStatus : public IContent
{
public:
    ContentQueryStatus();

    static std::array<std::string, 6> currentStatus;
    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTQUERYSTATUS_H
