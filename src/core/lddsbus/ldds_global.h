#ifndef LDDSBUS_GLOBAL_H__20241227
#define LDDSBUS_GLOBAL_H__20241227

#include <QtCore/qglobal.h>

#if defined(LDDSBUS_LIBRARY)
#define LDDSBUS_EXPORT Q_DECL_EXPORT
#else
#define LDDSBUS_EXPORT Q_DECL_IMPORT
#endif

#endif