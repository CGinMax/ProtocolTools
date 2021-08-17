#ifndef PROTOCOLS_GLOBAL_H
#define PROTOCOLS_GLOBAL_H

#  ifdef linux
#    define Q_DECL_EXPORT     __attribute__((visibility("default")))
#    define Q_DECL_IMPORT     __attribute__((visibility("default")))
#    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  elif defined(_WIN32)
#    ifdef _MSC_VER
#       define Q_DECL_EXPORT     __declspec(dllexport)
#       define Q_DECL_IMPORT     __declspec(dllimport)
#    else
#       define Q_DECL_EXPORT     __attribute__((visibility("default")))
#       define Q_DECL_IMPORT     __attribute__((visibility("default")))
#       define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#    endif

#  endif

#if defined(PROTOCOLS_LIBRARY)
#  define PROTOCOLSSHARED_EXPORT Q_DECL_EXPORT
#elif defined (PROTOCOLS_STATIC)
#  define PROTOCOLSSHARED_EXPORT
#else
#  define PROTOCOLSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PROTOCOLS_GLOBAL_H
