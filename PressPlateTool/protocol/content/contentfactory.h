#ifndef CONTENTFACTORY_H
#define CONTENTFACTORY_H

#include "icontent.h"
class ContentFactory
{
public:
    ContentFactory();

    static IContent* createContent(uint8_t funCode);
};

#endif // CONTENTFACTORY_H
