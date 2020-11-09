/*****************************************************************************************************/
This is WIN32 port of bufr2synop-0.13.0 UNIX original software.
Copyright (C) 2013-2020 by Guillermo Ballester Valor gbv@ogimet.com
Original UNIX software converts SYNOP and TEMP bufr messages
to alphanumeric GTS text

The port was made to use with my METEOWIN 2020 software system.

Resulting EXE file is bufrtotac.exe 

Ported by Stanislaw Kozlowski stkozlowski@gazeta.pl

Compiler used: Free OpenWatcom 1.9

Resulting libraries: libbufrdeco.lib, libbufr2tac.lib
Resulting EXE file: bufrtotac.exe which uses these libraries.

All functionality of original bufrtotac is retained.

Plus: 
a) working -o option for specifying output file
b) resulting converted GTS can be further conversted to standard meteo bulletin format.
   For this three Windows VBS scripts are provided:
   trbufrtotacsyn.vbs
   trbufrtotacshp.vbs
   trbufrtotactemp.vbs
   

For instance:

bufrtotac -i 20200607170000_ISND01_EDZW_071700_RRA.bufr -o 20200607170000_ISND01_EDZW_071700_RRA.txt
trbufrtotacsyn.vbs 20200607170000_ISND01_EDZW_071700_RRA.txt  20200607170000_ISND01_EDZW_071700_RRA.syn

File 20200607170000_ISND01_EDZW_071700_RRA.txt
is converted to standard meteo bulletin format

123
ISND01 EDZW 071700 RRA
AAXX 07171
10004 46/60 /2605 10126 20090 30077 40077 51021 333 55310=

Program works OK on examples from author's original package.
It works as well on routine bufr files from:
https://weather.cod.edu/digatmos/BUFR/SYNOP/EDZW/
for instance 2006080900_synop3.bufr.

Note: 
Files from:
https://weather.cod.edu/digatmos/BUFR/SYNOP/EDZW/ 	
for instance 2006080900_synop3.bufr, are packaged in sets and before converting to GTS ASCII
they should be unpacked.

For my needs I have written a special program for unpacking these files.

You find it in folder apps apps\CodExBufr.c
Makefile is apps\CodExBufr.mak

Usage: CodExBufr packed_COD_bufr_file some_outputdir<enter>

some_outputdir folder should be previously created.

For instance unpacking included example 2006080900_synop3.bufr with command:

CodExBufr 2006080900_synop3.bufr \some_outputdir<enter>

gives following output:

Input file size=41244
BUFR found at=32
Creating file: \some_outputdir\20200608090000_ISID03_EDZW_080900.bufr
BUFR found at=4667
Creating file: \some_outputdir\20200608090000_ISID08_EDZW_080900.bufr
BUFR found at=9680
Creating file: \some_outputdir\20200608090000_ISID06_EDZW_080900.bufr
BUFR found at=13867
Creating file: \some_outputdir\20200608090000_ISID04_EDZW_080900.bufr
BUFR found at=16806
Creating file: \some_outputdir\20200608090000_ISID05_EDZW_080900.bufr
BUFR found at=19960
Creating file: \some_outputdir\20200608090000_ISID07_EDZW_080900.bufr
BUFR found at=23317
Creating file: \some_outputdir\20200608090000_ISID09_EDZW_080900.bufr
BUFR found at=27328
Creating file: \some_outputdir\20200608090000_ISID02_EDZW_080900.bufr
BUFR found at=33206
Creating file: \some_outputdir\20200608090000_ISID01_EDZW_080900.bufr
BUFR found at=38661
Creating file: \some_outputdir\20200608090000_ISID03_EDZW_080900_CCA.bufr
BUFR found at=39108
Creating file: \some_outputdir\20200608090000_ISID02_EDZW_080900_RRA.bufr
BUFR found at=39951
Creating file: \some_outputdir\20200608090000_ISID07_EDZW_080900_RRA.bufr
BUFR found at=40398
Creating file: \some_outputdir\20200608090000_ISID02_EDZW_080900_CCA.bufr
BUFR found at=40841
Creating file: \some_outputdir\20200608090000_ISID01_EDZW_080900_RRA.bufr
Created 14 files

*********************************************************************************

Then run:
bufrtotac -i 20200608090000_ISID01_EDZW_080900_RRA.bufr


Note:
bufrtotac uses CSV bufr_tables from original bufr2synop-0.13.0.zip

For my special needs these tables are placed in folder:
\meteow\bufr_tables 

This location is hardcoded in file:
bufrdeco\bufrdeco_wmo.c
It can be changed and then program should be recompiled.

************************************************************************************

Assuming you have OpenWatcom 1.9 for WIN32 installed,
to compile bufrtotac under WIN32 perform following steps:

1. Copy contents of this package with subfolders to some folder ie. D:\wrk\bufr
2. Structure of subfolders should be:
   D:\wrk\bufr\src13\apps
   D:\wrk\bufr\src13\bufrdeco
   D:\wrk\bufr\src13\libraries
3. Create folder D:\meteow\Bufr_tables
   Copy contents of folder D:\wrk\bufr\src13\Bufr_tables to
   D:\meteow\Bufr_tables
4. Open CMD command prompt

5. In order to create libbufrdeco.lib: 
6. d:<enter>
7. cd d:\wrk\bufr\src13\bufrdeco<enter>
8. nmake -a -f libbufrdeco.mak<enter>

9. In order to create libbufr2tac.lib:
10. cd d:\wrk\bufr\src13\libraries<enter>
11. nmake -a -f libbufr2tac.mak<enter>

12. In order to create bufrtotac.exe:
13. cd d:\wrk\bufr\src13\apps<enter>
14. nmake -a -f bufrtotac.mak<enter>

****************************************************************************

METEOWIN 2020 software system

bufrtotac.exe program is used in my Windows 32 METEOWIN 2020 software system.
This shareware system is able to automatically download meteorological bulletins
from free internet sites and display them as graphical meteo charts and diagrams.
Processed are synop, aerological and metar data.
Data sources are OGIMET and https://weather.cod.edu/digatmos

Several examples of graphics files in png format are in this folder:

1 - Download.png  - How to point and click download meteorological data from internet 
  using METEOWIN 2020
2 - View diurnal course.png  - view diurnal course of weather on any station
3 - View synoptic chart of Europe.png
4 - View synoptic chart of Spain.png
6 - View synoptic chart of world.png
7 - View aerological chart of Europe.png
8 - View aerological diagram.png
9 - View metar chart of Europe.png

If you are interested in Windows 32 METEOWIN 2020 software system, email to stkozlowski@gazeta.pl

