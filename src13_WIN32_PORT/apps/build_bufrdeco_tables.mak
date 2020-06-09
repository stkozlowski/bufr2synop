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

all: build_bufrdeco_tables.exe

build_bufrdeco_tables.exe: build_bufrdeco_tables.obj 
 wlink file build_bufrdeco_tables.obj lib $(LIBBUFRDECO) system nt opt q
 
build_bufrdeco_tables.obj: build_bufrdeco_tables.C
   $(CL) build_bufrdeco_tables.C



