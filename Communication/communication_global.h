﻿#ifndef COMMUNICATION_GLOBAL_H
#define COMMUNICATION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMUNICATION_LIBRARY)
#  define COMMUNICATIONSHARED_EXPORT Q_DECL_EXPORT
#elif defined (COMMUNICATION_STATIC)

#endif
#  define COMMUNICATIONSHARED_EXPORT


#endif // COMMUNICATION_GLOBAL_H
