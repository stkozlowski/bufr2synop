#include <stdio.h>
#include <errno.h>
#include <share.h>
#include <fcntl.h>
#include <io.h>
#include <sys\types.h>
#include <sys\stat.h>

#if !(defined(PM))
#define INCL_NOPMAPI
#define INCL_NOPM
#endif

#ifdef PM
#ifndef OS2
#define OS2
#endif
#endif

#if (defined(WIN31) || defined(_WIN95) || defined(WIN32))
#include <windows.h>
extern FILE *fpd;
#endif

#if (defined(OPEN32))
#include <os2win.h>
#endif

#if (defined(OS2))
#define INCL_BASE
#include <os2.h>
#endif

#ifndef BOOL
#ifdef __IBMC__
#pragma info(noppc)
#endif
#define BOOL int
#ifdef __IBMC__
#pragma info(ppc)
#endif
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#include "compdef.h"
#include "openf.h"

#include "doscalls.h"

#ifndef FORTRAN
#define INITIALIZE
#endif

#if(defined(MSC56) && defined(WIN31))
extern FILE *fpd;
#endif

#ifdef __cplusplus
"C"
{
#endif

int sopenSafe(char *FName,int oflags,int sflag,int *fh,int *errn);

FILE *fopenSafe(char *FName,int oflags,int sflag,char *fdflags,FILE **fp,int *errn)
{int fh;
 BOOL bFlag;
 if(*fp==NULL) {bFlag=TRUE;fh=0;} else {bFlag=FALSE;fh=1;}
 fh=sopenSafe(FName,oflags,sflag,&fh,errn);
 if(fh<=0) {*fp=NULL;return(*fp);}
 *fp=fdopen(fh,fdflags);
 if(*fp==NULL)
  {close(fh);
   if(bFlag==TRUE)
#if(defined(WIN31) && defined(DEBUG))
   if(fpd!=NULL)
    fprintf(fpd,"Error fdopening %s errno=%d\n",FName,*errn);
#else
#ifndef WIN31
    printf("Error fdopening %s errno=%d\n",FName,*errn);
#endif
#endif
   return NULL;
   }
 return *fp;
}
int sopenSafe(char *FName,int oflags,int sflag,int *fh,int *errn)
{BOOL bFlag;
 if(*fh==0) bFlag=TRUE; else bFlag=FALSE;
 for(;;)
  {errno=0;
#ifdef MSC56
   /*Microsoft C up to v. 6.00 requires O_NOINHERIT flag
     included with share flags
   */
   if(oflags & O_NOINHERIT)
    {
     /*'and' with 'bitwise NOT' of O_NOINHERIT
        removes O_NOINHERIT bits from oflags
     */
     oflags=oflags & (~O_NOINHERIT);
     sflag=sflag | O_NOINHERIT;
     }
#endif
   *fh=sopen(FName,oflags,sflag,S_IREAD|S_IWRITE);
   *errn=errno;
   if(*fh>0) return *fh;
   if (*errn==EACCESS)
    {
     BeepDos(1200,175);
     Sleep(1000L);
     continue;
     }
     else
      {
#if(defined(WIN31) && defined(DEBUG))
       if(bFlag==TRUE)
        if(fpd!=NULL)
         fprintf(fpd,"Can't open %s errno=%d\n",FName,*errn);
#else
#ifndef WIN31
       if(bFlag==TRUE)
        printf("Can't open %s errno=%d\n",FName,*errn);
#endif
#endif
       return -1;
       }
   }
 }
#ifdef __cplusplus
}
#endif
