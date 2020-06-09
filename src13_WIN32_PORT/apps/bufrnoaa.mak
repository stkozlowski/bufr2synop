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

INCBUFR=..\..\src13\bufrdeco
INCBUFRLIB=..\..\src13\libraries
LIBBUFRDECO=..\..\src13\bufrdeco\libbufrdeco.lib
LIBBUFRTAC=..\..\src13\libraries\libbufr2tac.lib

CL=wcc386 /i$(INCLUDE);$(INCBUFR);$(INCBUFRLIB) /d0 /fr /fp3 /od /wx /zq

all: bufrnoaa.exe

bufrnoaa.exe: bufrnoaa.obj bufrnoaa_io.obj bufrnoaa_utils.obj gettimeofday.obj time_r.obj
 wlink file bufrnoaa.obj file bufrnoaa_io.obj file bufrnoaa_utils.obj file gettimeofday.obj file time_r.obj system nt opt q
#lib $(LIBBUFRTAC) lib $(LIBBUFRDECO) system nt opt q
 
bufrnoaa.obj: bufrnoaa.C
   $(CL) bufrnoaa.C

bufrnoaa_io.obj: bufrnoaa_io.C
   $(CL) bufrnoaa_io.C

bufrnoaa_utils.obj: bufrnoaa_utils.C
   $(CL) bufrnoaa_utils.C

gettimeofday.obj: gettimeofday.C
   $(CL) gettimeofday.C

time_r.obj: $(INCBUFRLIB)\time_r.C
   $(CL) $(INCBUFRLIB)\time_r.C



