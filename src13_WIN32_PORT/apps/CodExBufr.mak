
CL=wcc386 /i$(INCLUDE) /d0 /fr /fp3 /od /wx /zp2 /zq -dWIN32 /DWIN32_LEAN_AND_MEAN

CodExBufr.exe: CodExBufr.obj openf.obj doscalls.obj 
   wlink fil CodExBufr.obj fil openf.obj fil doscalls.obj \
 system nt opt q

CodExBufr.obj: CodExBufr.C
   $(CL) CodExBufr.C

openf.obj: openf.C
   $(CL) openf.C

doscalls.obj: doscalls.c
    $(CL) doscalls.c



