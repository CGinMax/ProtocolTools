#ifndef CONTENTFACTORY_H
#define CONTENTFACTORY_H

#include "icontent.h"
class PROTOCOLSSHARED_EXPORT ContentFactory
{
public:
    ContentFactory();

    static IContent* createContent(uint8_t funCode, const std::vector<uint8_t>& datas = std::vector<uint8_t>());
};

#endif // CONTENTFACTORY_H
