#if (defined(OPEN32) || defined(WIN31) || defined(DOS))
void _cdecl BeepDos(unsigned long frequency,unsigned long duration);
#endif

#if (defined(_WIN95) || defined(WIN32))
void __stdcall BeepDos(unsigned long frequency,unsigned long duration);
#endif

#if (defined(OS2))
void _System BeepDos(unsigned long frequency,unsigned long duration);
#endif

#if (defined(WIN31) || defined(DOS))
void _cdecl Sleep(unsigned long milisec);
#endif

#if (defined(OS2))
void _System Sleep(unsigned long milisec);
#endif

#if (defined(WIN31) || defined(DOS))
typedef struct _FTIME {
    unsigned twosecs : 5;
    unsigned minutes : 6;
    unsigned hours   : 5;
} FTIME;

typedef struct _FDATE {
    unsigned day     : 5;
    unsigned month   : 4;
    unsigned year    : 7;
} FDATE;

typedef struct _FILEFINDBUF {
    //char bf[7];
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    unsigned long cbFile;
    unsigned long  cbFileAlloc;
    unsigned short attrFile;
    unsigned char  cchName;
    char   achName[13];
} FILEFINDBUF;
typedef FILEFINDBUF *PFILEFINDBUF;
int pascal DosFindFirst(char *mask,unsigned short *hdir,unsigned short attr,
                 FILEFINDBUF *fb,unsigned short size,unsigned short *ret,
                 unsigned long ign);
int pascal DosFindNext(unsigned short hdir,
                 FILEFINDBUF *fb,unsigned short size,unsigned short *ret);
#endif
