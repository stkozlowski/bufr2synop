#ifndef _STRPTIME_H
#define _STRPTIME_H

#define ALT_E          0x01
#define ALT_O          0x02
//#define LEGAL_ALT(x)       { if (alt_format & ~(x)) return (0); }
#define LEGAL_ALT(x)       { ; }
#define TM_YEAR_BASE   (1900)

#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#ifdef __cplusplus
extern "C" {  
#endif  

char * strptime(const char *buf, const char *fmt, struct tm *tm);

#ifdef __cplusplus
}
#endif


#endif

