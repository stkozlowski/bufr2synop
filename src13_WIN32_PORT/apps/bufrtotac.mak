# -5r Pentium register calling conventions
# -fp5 generate Pentium floating-point code
# -d0 no debugging information
# -wx set warning maximum level
# -e25 set limit of displayed error messages
# -zq operate quietly
# -od disable optimizations
# -bt=nt build target for operating system NT or Win95
# -fr disable production of error file
# -bm multithread
# -d define symbols
# -zp=1 pack structure members with alinment 1

INCBUFR=..\..\src13_WIN32_PORT\bufrdeco
INCBUFRLIB=..\..\src13_WIN32_PORT\libraries
LIBBUFRDECO=..\..\src13_WIN32_PORT\bufrdeco\libbufrdeco.lib
LIBBUFRTAC=..\..\src13_WIN32_PORT\libraries\libbufr2tac.lib

CL=wcc386 /i$(INCLUDE);$(INCBUFR);$(INCBUFRLIB) /d0 /fr /fp3 /od /wx /zq

all: bufrtotac.exe

bufrtotac.exe: $(LIBBUFRTAC) $(LIBBUFRDECO) bufrtotac.obj bufrtotac_io.obj
 wlink file bufrtotac.obj file bufrtotac_io.obj lib $(LIBBUFRTAC) lib $(LIBBUFRDECO) system nt opt q
 
bufrtotac.obj: bufrtotac.C
   $(CL) bufrtotac.C

bufrtotac_io.obj: bufrtotac_io.C
   $(CL) bufrtotac_io.C


