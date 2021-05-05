#ifndef CONTENTREPORTSTATUS_H
#define CONTENTREPORTSTATUS_H

#include "icontent.h"

class ContentReportStatus : public IContent
{
public:
    ContentReportStatus();

    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTREPORTSTATUS_H
