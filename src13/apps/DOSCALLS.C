#include <conio.h>
#include <string.h>
#include <stdio.h>

#if (defined(DOS))
#include <dos.h>
#endif

#if (defined(_WIN95) || defined(WIN32) || defined(WIN31))
#include <windows.h>
#endif

#ifdef OPEN32
#include <os2win.h>
#endif

#ifdef OS2
#define INCL_BASE
#include <os2.h>
#endif

#include "doscalls.h"

#if (defined(__WATCOMC__))
#define _inp inp
#define _outp outp
#endif

#if (defined(OS2))
void _System BeepDos(unsigned long frequency,unsigned long duration)
#endif

#if (defined(_WIN95) || defined(WIN32))
void __stdcall BeepDos(unsigned long frequency,unsigned long duration)
#endif

#if (defined(OPEN32) || defined(WIN31) || defined(DOS))
void _cdecl BeepDos(unsigned long frequency,unsigned long duration)
#endif
{
#if (defined(OS2))
 DosBeep(frequency,duration);
#endif
#ifdef OPEN32
   Beep((unsigned long)frequency,(unsigned long)duration);
#endif
#if (defined(_WIN95) || defined(WIN32))
 int control;
 OSVERSIONINFO vi;
 vi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
 GetVersionEx(&vi);
 if(vi.dwPlatformId==VER_PLATFORM_WIN32_NT)
  {Beep((unsigned long)frequency,(unsigned long)duration);
   return;
   }
#endif

#if (defined(_WIN95) || defined(WIN32) || defined(WIN31) || defined(DOS))
    // If frequency is 0, Beep doesn't try to make a sound. It
    // just sleeps for the duration.

    if( frequency )
    {
        // 75 is about the shortest reliable duration of a sound.
        if( duration < 75 )
            duration = 75;

        // Prepare timer by sending 10111100 to port 43.
        _outp( 0x43, 0xb6 );

        // Divide input frequency by timer ticks per second and
        // write (byte by byte) to timer.

        frequency = (unsigned short)(1193180L / frequency);
        _outp( 0x42, (char)frequency );
        _outp( 0x42, (char)(frequency >> 8) );

        // Save speaker control byte.
        control = _inp( 0x61 );

        // Turn on the speaker (with bits 0 and 1).
        _outp( 0x61, control | 0x3 );
    }

    Sleep((unsigned long)duration );

    // Turn speaker back on if necessary.
    if( frequency )
        _outp( 0x61, control );
#endif
}

#if (defined(OS2))
void _System Sleep(unsigned long duration)
{DosSleep(duration);
}
#endif

#if (defined(WIN31) || defined(DOS))
void _cdecl Sleep(unsigned long duration)
{union REGS inregs;
 unsigned long per;
 unsigned short *ptr;
 per=duration*1000L;
 ptr=(unsigned short *)(&per);
 inregs.h.ah=0x86;
 inregs.x.dx=*ptr;
 inregs.x.cx=*(ptr+1);
 int86(0x15,&inregs,&inregs);
 }
#endif

#if (defined(WIN31) || defined(DOS))
int pascal DosSelectDisk(unsigned short Drive)
{unsigned int ndrives;
 _dos_setdrive((unsigned)Drive,&ndrives);
 return 0;
}

static struct find_t fppl;
int pascal DosFindFirst(char *mask,unsigned short *hdir,unsigned short attr,
                 FILEFINDBUF *fb,unsigned short size,unsigned short *ret,
                 unsigned long ign)
{
 int rc;
 *hdir;
 size;
 ign;
 rc=_dos_findfirst(mask,attr,&fppl);
 if(rc==0)
  {*ret=1;
   strcpy(fb->achName,fppl.name);
   fb->attrFile=fppl.attrib;
  }
  else *ret=0;
 return 0;
}
int pascal DosFindNext(unsigned short hdir,
                 FILEFINDBUF *fb,unsigned short size,unsigned short *ret)
{int rc;
 hdir;
 size;
 rc=_dos_findnext(&fppl);
 if(rc==0)
   {*ret=1;
   strcpy(fb->achName,fppl.name);
   fb->attrFile=fppl.attrib;
  }
  else *ret=0;

 return 0;
}
#endif
