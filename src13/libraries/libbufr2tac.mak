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

CL=wcc386 /i$(INCLUDE);$(INCBUFR) /d0 /fr /fp3 /od /wx /zq 

all: libbufr2tac.lib

libbufr2tac.lib: \
  time_r.obj \
  strptime.obj \
  unsetenv19.obj \
  strtok_r.obj \
  bufr2tac_buoy.obj \
  bufr2tac_climat.obj \
  bufr2tac_csv.obj \
  bufr2tac_env.obj \
  bufr2tac_io.obj \
  bufr2tac_json.obj \
  bufr2tac_mrproper.obj \
  bufr2tac_print.obj \
  bufr2tac_print_buoy.obj \
  bufr2tac_print_climat.obj \
  bufr2tac_print_synop.obj \
  bufr2tac_print_temp.obj \
  bufr2tac_sqparse.obj \
  bufr2tac_synop.obj \
  bufr2tac_tablec.obj \
  bufr2tac_temp.obj \
  bufr2tac_utils.obj \
  bufr2tac_x01.obj \
  bufr2tac_x02.obj \
  bufr2tac_x04.obj \
  bufr2tac_x05.obj \
  bufr2tac_x06.obj \
  bufr2tac_x07.obj \
  bufr2tac_x08.obj \
  bufr2tac_x10.obj \
  bufr2tac_x11.obj \
  bufr2tac_x12.obj \
  bufr2tac_x13.obj \
  bufr2tac_x14.obj \
  bufr2tac_x20.obj \
  bufr2tac_x22.obj \
  bufr2tac_x31.obj \
  bufr2tac_x33.obj \
  bufr2tac_xml.obj 
 lib -out:libbufr2tac.lib \
  time_r.obj \
  strptime.obj \
  unsetenv19.obj \
  strtok_r.obj \
  bufr2tac_buoy.obj \
  bufr2tac_climat.obj \
  bufr2tac_csv.obj \
  bufr2tac_env.obj \
  bufr2tac_io.obj \
  bufr2tac_json.obj \
  bufr2tac_mrproper.obj \
  bufr2tac_print.obj \
  bufr2tac_print_buoy.obj \
  bufr2tac_print_climat.obj \
  bufr2tac_print_synop.obj \
  bufr2tac_print_temp.obj \
  bufr2tac_sqparse.obj \
  bufr2tac_synop.obj \
  bufr2tac_tablec.obj \
  bufr2tac_temp.obj \
  bufr2tac_utils.obj \
  bufr2tac_x01.obj \
  bufr2tac_x02.obj \
  bufr2tac_x04.obj \
  bufr2tac_x05.obj \
  bufr2tac_x06.obj \
  bufr2tac_x07.obj \
  bufr2tac_x08.obj \
  bufr2tac_x10.obj \
  bufr2tac_x11.obj \
  bufr2tac_x12.obj \
  bufr2tac_x13.obj \
  bufr2tac_x14.obj \
  bufr2tac_x20.obj \
  bufr2tac_x22.obj \
  bufr2tac_x31.obj \
  bufr2tac_x33.obj \
  bufr2tac_xml.obj 

time_r.obj: time_r.c
 $(CL) time_r.c

strptime.obj: strptime.c
 $(CL) strptime.c

unsetenv19.obj: unsetenv19.c
 $(CL) unsetenv19.c

strtok_r.obj: strtok_r.c
 $(CL) strtok_r.c

bufr2tac_buoy.obj: bufr2tac_buoy.c
 $(CL) bufr2tac_buoy.c

bufr2tac_climat.obj: bufr2tac_climat.c
 $(CL) bufr2tac_climat.c

bufr2tac_csv.obj: bufr2tac_csv.c
 $(CL) bufr2tac_csv.c

bufr2tac_env.obj: bufr2tac_env.c
 $(CL) bufr2tac_env.c

bufr2tac_io.obj: bufr2tac_io.c
 $(CL) bufr2tac_io.c

bufr2tac_json.obj: bufr2tac_json.c
 $(CL) bufr2tac_json.c

bufr2tac_mrproper.obj: bufr2tac_mrproper.c
 $(CL) bufr2tac_mrproper.c

bufr2tac_print.obj: bufr2tac_print.c
 $(CL) bufr2tac_print.c

bufr2tac_print_buoy.obj: bufr2tac_print_buoy.c
 $(CL) bufr2tac_print_buoy.c

bufr2tac_print_climat.obj: bufr2tac_print_climat.c
 $(CL) bufr2tac_print_climat.c

bufr2tac_print_synop.obj: bufr2tac_print_synop.c
 $(CL) bufr2tac_print_synop.c

bufr2tac_print_temp.obj: bufr2tac_print_temp.c
 $(CL) bufr2tac_print_temp.c

bufr2tac_sqparse.obj: bufr2tac_sqparse.c
 $(CL) bufr2tac_sqparse.c

bufr2tac_synop.obj: bufr2tac_synop.c
 $(CL) bufr2tac_synop.c

bufr2tac_tablec.obj: bufr2tac_tablec.c
 $(CL) bufr2tac_tablec.c

bufr2tac_temp.obj: bufr2tac_temp.c
 $(CL) bufr2tac_temp.c

bufr2tac_utils.obj: bufr2tac_utils.c
 $(CL) bufr2tac_utils.c

bufr2tac_x01.obj: bufr2tac_x01.c
 $(CL) bufr2tac_x01.c

bufr2tac_x02.obj: bufr2tac_x02.c
 $(CL) bufr2tac_x02.c

bufr2tac_x04.obj: bufr2tac_x04.c
 $(CL) bufr2tac_x04.c

bufr2tac_x05.obj: bufr2tac_x05.c
 $(CL) bufr2tac_x05.c

bufr2tac_x06.obj: bufr2tac_x06.c
 $(CL) bufr2tac_x06.c

bufr2tac_x07.obj: bufr2tac_x07.c
 $(CL) bufr2tac_x07.c

bufr2tac_x08.obj: bufr2tac_x08.c
 $(CL) bufr2tac_x08.c

bufr2tac_x10.obj: bufr2tac_x10.c
 $(CL) bufr2tac_x10.c

bufr2tac_x11.obj: bufr2tac_x11.c
 $(CL) bufr2tac_x11.c

bufr2tac_x12.obj: bufr2tac_x12.c
 $(CL) bufr2tac_x12.c

bufr2tac_x13.obj: bufr2tac_x13.c
 $(CL) bufr2tac_x13.c

bufr2tac_x14.obj: bufr2tac_x14.c
 $(CL) bufr2tac_x14.c

bufr2tac_x20.obj: bufr2tac_x20.c
 $(CL) bufr2tac_x20.c

bufr2tac_x22.obj: bufr2tac_x22.c
 $(CL) bufr2tac_x22.c

bufr2tac_x31.obj: bufr2tac_x31.c
 $(CL) bufr2tac_x31.c

bufr2tac_x33.obj: bufr2tac_x33.c
 $(CL) bufr2tac_x33.c

bufr2tac_xml.obj: bufr2tac_xml.c
 $(CL) bufr2tac_xml.c

