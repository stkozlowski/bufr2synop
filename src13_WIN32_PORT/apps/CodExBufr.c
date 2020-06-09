/* Extract individual bufr files from packed bufr set from
   https://weather.cod.edu/digatmos/BUFR/SYNOP/EDZW/
   Copyright Stanislaw Koz³owski stkozlowski@gazeta.pl
   Compile with OPENWATCOM 1.9 
   Makefile: CodExBufr.mak

   usage:
   CodExBufr packed_COD_bufr_file outputdir<enter>

   For instance unpack 2006080900_synop3.bufr with command:

   CodExBufr 2006080900_synop3.bufr \some_outputdir<enter>
*/

#define  STRICT
#include <windows.h>
#include <windowsx.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <share.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <malloc.h>
#include <io.h>
#include <direct.h>
#include "openf.h"
#include "doscalls.h"

char buf[_MAX_PATH];
char outputdir[_MAX_PATH];

struct stat sstat;
char sourcewithpath[_MAX_PATH],targetwithpath[_MAX_PATH],targetSYNwithpath[_MAX_PATH];
char targetSYN2withpath[_MAX_PATH];
char targetSYN2withouthpath[_MAX_PATH];
char targetwithouthpath[_MAX_PATH];
char sourcefile[256],targetfile[256];
char sourcedate[256];

int main ( int argc, char *argv[] )
{int fh,fhout,errn,rc;
 unsigned i,j,k,bufrstart=0,bufrend=0;
 unsigned HeaderStart,HeaderEnd;
 unsigned char *p; 
 char Header[64];
 char* pp;
 int bstartfound=0;
 int bendfound=0;
 int filescreated=0;
 char drv[16],dir[_MAX_PATH],fname[256],ext[256];

 if (argc<3)
  {printf("Program extracts bufr contents from packed files from https://weather.cod.edu/digatmos/BUFR/SYNOP/EDZW/\n");
   printf("Usage: CodExBufr Bufr_file_name.bufr outputdir\n");
   exit(0); 
   }

 strcpy(outputdir,argv[2]);
 if(outputdir[strlen(outputdir)]=='\\') outputdir[strlen(outputdir)]=0;
 strcpy(sourcewithpath,argv[1]);
 rc=stat(sourcewithpath,&sstat);
 //printf("source %s\n",source);
 if (rc!=0) return -1;
 if(sstat.st_size==0) return -1;
 _splitpath(sourcewithpath,drv,dir,fname,ext);
 if(strlen(dir)==0) //must get current working dir
  {getcwd(buf,_MAX_PATH);
   drv[0]=buf[0];
   drv[1]=buf[1];
   drv[2]=0;
   strcpy(dir,&buf[2]);
   strcat(dir,"\\");
   }
 //printf("dir=%s\n",dir);

 rc=stat(sourcewithpath,&sstat);
 //printf("source %s\n",source);
 if (rc!=0) return -1;
 printf("Input file size=%d\n",sstat.st_size);
 fh=sopenSafe(sourcewithpath,O_RDONLY | O_BINARY | O_NOINHERIT,SH_DENYWR,&fh,&errn);
 if (fh<=0) return -1;
 p=malloc(sstat.st_size);
 read(fh,p,sstat.st_size);
 strcat(fname,ext); 
 for(;;)
 {
  bstartfound=0;
  bendfound=0;
  strcpy(sourcedate,"20");
  strncat(sourcedate,fname,10);
  strcpy(targetfile,sourcedate);
  strcat(targetfile,"00_");
  Header[0]=0;
  for(i=bufrend;i<sstat.st_size-1-4;i++)
   if(p[i]=='B' && p[i+1]=='U' && p[i+2]=='F' && p[i+3]=='R')
    {bstartfound=1;
     bufrstart=i; //points to 'B'
     printf("BUFR found at=%d\n",i);
     j=0;
     while(p[bufrstart-j]!=13) j++;
     //printf("j=%d\n",j);
     j++;
     while(p[bufrstart-j]!=13) j++;
     //printf("j=%d\n",j);
     HeaderEnd=bufrstart-j-1;
     //printf("p[HeaderEnd]=%c\n",p[HeaderEnd]);
     j++;
     while(p[bufrstart-j]!=10) j++;
     HeaderStart=bufrstart-j+1;
     //printf("HeaderStart=%d\n",HeaderStart); 
     //printf("HeaderEnd=%d\n",HeaderEnd); 
     k=0;
     for(j=HeaderStart;j<=HeaderEnd;j++)
      {Header[k]=p[j];
       k++;
       }
     Header[k]=0;
     //printf("Header=%s\n",Header);
     //replace all occurences of ' ' with '_'
     for (pp = Header; pp = strchr(pp, ' '); ++pp) 
      {
       *pp = '_';
       }
     //printf("Header=%s\n",Header);
     break;
     }
  for(i=bufrend+1;i<sstat.st_size-1-4;i++)
   if(p[i]=='7' && p[i+1]=='7' && p[i+2]=='7' && p[i+3]=='7')
    {bendfound=1;
     bufrend=i+3;//points to last '7'
     //printf("bufrend=%d\n",i);
     break;
     }
  if(bstartfound==1 && bendfound==1)
   {filescreated++;
    strcat(targetfile,Header);
    strcat(targetfile,".bufr");
    strcpy(targetwithpath,outputdir);
    strcat(targetwithpath,"\\");
    strcat(targetwithpath,targetfile);
    printf("Creating file: %s\n",targetwithpath);
    fhout=sopenSafe(targetwithpath,O_TRUNC|O_CREAT|O_RDWR|O_BINARY|O_NOINHERIT,SH_DENYWR,&fhout,&errn);
    if(fhout<1) 
     {printf("Cannot create file %s\n",targetwithpath);
      exit(1);
      } 
    write(fhout,&p[bufrstart],bufrend+1-bufrstart);
    close(fhout);

    }
   else break;
 }
 printf("Created %d files\n",filescreated);
 return 0;
}
