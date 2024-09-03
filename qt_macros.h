#ifndef QT_MACROS_H
#define QT_MACROS_H

// UCS - Universal Coded Character Set
#define UCS( str ) QString::fromUtf8( str )
#define UCSSTD( stdStr ) QString::fromUtf8( stdStr.c_str() )
#define UTF8( qstr ) qstr.toUtf8().data()

#endif // QT_MACROS_H
