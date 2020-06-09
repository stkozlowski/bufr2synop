/***************************************************************************
 *   Copyright (C) 2013-2018 by Guillermo Ballester Valor                  *
 *   gbv@ogimet.com                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*!
 \file bufr2tac_print.c
 \brief file with the code to print the results
 */
#include "bufr2tac.h"

/*!
  \fn  int print_plain ( FILE *f, struct metreport *m )
  \brief Print in a file the report decoded to Traditional Alphanumeric Code in plain text format. A line per report
  \param f pointer to file where to write to
  \param m pointer to struct \ref metreport where the decoded report is stored
*/
int print_plain ( FILE *f, struct metreport *m )
{
 char * schowek;
 char YYGGIw[32];
 char MiMiMjMj[16];
 struct synop_chunks *syn;
 static int aaxx_printed=0;
 static int bbxx_printed=0;

 syn = &m->synop;
 //printf("WIND %c%c%c%c\n",syn->s0.iw[0],syn->s0.iw[1],syn->s0.iw[2],syn->s0.iw[3]);
 //printf("print_plain %d %d %d %d\n",m->alphanum[0],m->alphanum2[0],m->alphanum3[0],m->alphanum4[0]);
  syn = &m->synop;
  if ( m->alphanum[0] )
   {strcpy(MiMiMjMj,m->type);

    if(strcmp(MiMiMjMj,"AAXX")==0) //for AAXX format typical SYNOP bulletin
     { 
      if(aaxx_printed==0)
       {
        fprintf(f,"%s ",MiMiMjMj);
        snprintf(YYGGIw,5,"%s\n",&(m->h->timestamp)[6]);
        YYGGIw[4]=syn->s0.iw[0];
        YYGGIw[5]=0;
        fprintf(f,"%s\n",YYGGIw);
        aaxx_printed=1;
        }
/*
      if (strlen (m->g.index ) )
                    fprintf (f,"%s ",m->g.index );
                   else
                    fprintf (f," " );
*/
      schowek=strstr(m->alphanum," ");
      schowek=strstr(&schowek[1]," ");
      schowek=strstr(&schowek[1]," ");
/*
      schowek=strstr(&schowek[1]," ");
      schowek=strstr(&schowek[1]," ");
*/
      //fprintf ( f, "%s\n", m->alphanum );
      fprintf ( f, "%s\n", &schowek[1] );
      }
   else
    if(strcmp(MiMiMjMj,"BBXX")==0) //for BBXX format typical SYNOP SHIP bulletin
      {
        if(bbxx_printed==0)
          {
           fprintf(f,"%s \n",MiMiMjMj);
           bbxx_printed=1;
           }
         if (strlen (m->g.index ) )
                    fprintf (f,"%s ", m->g.index );
                   else
                    fprintf (f," " );
         schowek=strstr(m->alphanum," ");
         schowek=strstr(&schowek[1]," ");
         schowek=strstr(&schowek[1]," ");
         fprintf ( f, "%s\n", &schowek[1]);
         }
    else
     if(strcmp(MiMiMjMj,"TTAA")==0) //for TTAA format typical TEMP bulletin
      { 
       fprintf(f,"%s ",MiMiMjMj);
       schowek=strstr(m->alphanum," ");
       schowek=strstr(&schowek[1]," ");
       fprintf ( f, "%s\n", &schowek[1] );
       }
    else
     if(strcmp(MiMiMjMj,"TTBB")==0) //for TTBB format typical TEMP bulletin
      { 
       fprintf(f,"%s ",MiMiMjMj);
       schowek=strstr(m->alphanum," ");
       schowek=strstr(&schowek[1]," ");
       fprintf ( f, "%s\n", &schowek[1] );
       }
     else fprintf ( f, "%s\n", m->alphanum );
    }
  if ( m->alphanum2[0] )
   {strcpy(MiMiMjMj,m->type2);
    if(strcmp(MiMiMjMj,"TTBB")==0) //for TTBB format typical TEMP bulletin
      { 
       fprintf(f,"%s ",MiMiMjMj);
       schowek=strstr(m->alphanum2," ");
       schowek=strstr(&schowek[1]," ");
       fprintf ( f, "%s\n", &schowek[1] );
       }
     else 
      fprintf ( f, "%s\n", m->alphanum2);
     }
  if ( m->alphanum3[0] )
   {strcpy(MiMiMjMj,m->type3);
    if(strcmp(MiMiMjMj,"TTCC")==0) //for TTCC format typical TEMP bulletin
      { 
       fprintf(f,"%s ",MiMiMjMj);
       schowek=strstr(m->alphanum3," ");
       schowek=strstr(&schowek[1]," ");
       fprintf ( f, "%s\n", &schowek[1] );
       }
     else
     fprintf ( f, "%s\n", m->alphanum3 );
    }
  if ( m->alphanum4[0] )
   {strcpy(MiMiMjMj,m->type4);
    if(strcmp(MiMiMjMj,"TTDD")==0) //for TTDD format typical TEMP bulletin
      { 
       fprintf(f,"%s ",MiMiMjMj);
       schowek=strstr(m->alphanum4," ");
       schowek=strstr(&schowek[1]," ");
       fprintf ( f, "%s\n", &schowek[1] );
       }
    else
     fprintf ( f, "%s\n", m->alphanum4 );
    }
  return 0;
}

/*!
  \fn  int print_html ( FILE *f, struct metreport *m )
  \brief Print in a file the report decoded to Traditional Alphanumeric Code in plain html format. A line per report
  \param f pointer to file where to write to
  \param m pointer to struct \ref metreport where the decoded report is stored
*/
int print_html ( FILE *f, struct metreport *m )
{
  fprintf(f, "<pre>");
  if ( m->alphanum[0] )
    fprintf ( f, "%s\n", m->alphanum );
  if ( m->alphanum2[0] )
    fprintf ( f, "%s\n", m->alphanum2 );
  if ( m->alphanum3[0] )
    fprintf ( f, "%s\n", m->alphanum3 );
  if ( m->alphanum4[0] )
    fprintf ( f, "%s\n", m->alphanum4 );
  fprintf(f, "</pre>");
  return 0;
}
