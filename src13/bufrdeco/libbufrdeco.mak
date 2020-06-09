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

CL=wcc386 /i$(INCLUDE) /d0 /fr /fp3 /od /wx /zq

all: libbufrdeco.lib 

libbufrdeco.lib: pow10.obj bufrdeco_compressed.obj bufrdeco_csv.obj bufrdeco_data.obj bufrdeco_ecmwf.obj \
 bufrdeco_f2.obj bufrdeco_memory.obj bufrdeco_print.obj bufrdeco_print_html.obj bufrdeco_read.obj\
 bufrdeco_tableb.obj bufrdeco_tableb_csv.obj bufrdeco_tablec.obj bufrdeco_tablec_csv.obj \
 bufrdeco_tabled.obj bufrdeco_tabled_csv.obj bufrdeco_tree.obj bufrdeco_utils.obj bufrdeco_wmo.obj
 lib -out:libbufrdeco.lib pow10.obj bufrdeco_compressed.obj bufrdeco_csv.obj bufrdeco_data.obj bufrdeco_ecmwf.obj \
 bufrdeco_f2.obj bufrdeco_memory.obj bufrdeco_print.obj bufrdeco_print_html.obj bufrdeco_read.obj\
 bufrdeco_tableb.obj bufrdeco_tableb_csv.obj bufrdeco_tablec.obj bufrdeco_tablec_csv.obj \
 bufrdeco_tabled.obj bufrdeco_tabled_csv.obj bufrdeco_tree.obj bufrdeco_utils.obj bufrdeco_wmo.obj 

pow10.obj: pow10.C
   $(CL) pow10.C

bufrdeco_compressed.obj: bufrdeco_compressed.C
   $(CL) bufrdeco_compressed.C

bufrdeco_csv.obj: bufrdeco_csv.C
   $(CL) bufrdeco_csv.C

bufrdeco_data.obj: bufrdeco_data.C
   $(CL) bufrdeco_data.C

bufrdeco_ecmwf.obj: bufrdeco_ecmwf.C
   $(CL) bufrdeco_ecmwf.C

bufrdeco_f2.obj: bufrdeco_f2.C
   $(CL) bufrdeco_f2.C

bufrdeco_memory.obj: bufrdeco_memory.C
   $(CL) bufrdeco_memory.C

bufrdeco_print.obj: bufrdeco_print.C
   $(CL) bufrdeco_print.C

bufrdeco_print_html.obj: bufrdeco_print_html.C
   $(CL) bufrdeco_print_html.C

bufrdeco_read.obj: bufrdeco_read.C
   $(CL) bufrdeco_read.C

bufrdeco_tableb.obj: bufrdeco_tableb.C
   $(CL) bufrdeco_tableb.C

bufrdeco_tableb_csv.obj: bufrdeco_tableb_csv.C
   $(CL) bufrdeco_tableb_csv.C

bufrdeco_tablec.obj: bufrdeco_tablec.C
   $(CL) bufrdeco_tablec.C

bufrdeco_tablec_csv.obj: bufrdeco_tablec_csv.C
   $(CL) bufrdeco_tablec_csv.C

bufrdeco_tabled.obj: bufrdeco_tabled.C
   $(CL) bufrdeco_tabled.C

bufrdeco_tabled_csv.obj: bufrdeco_tabled_csv.C
   $(CL) bufrdeco_tabled_csv.C

bufrdeco_tree.obj: bufrdeco_tree.C
   $(CL) bufrdeco_tree.C

bufrdeco_utils.obj: bufrdeco_utils.C
   $(CL) bufrdeco_utils.C

bufrdeco_wmo.obj: bufrdeco_wmo.C
   $(CL) bufrdeco_wmo.C


