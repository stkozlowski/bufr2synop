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
 \file bufr2tac_xml.c
 \brief Output a struct \ref metreport in xml form
*/
#include "bufr2tac.h"



int print_xml_alphanum ( FILE *f, char *type, char *alphanum, struct metreport *m )
{
  // prints header
  fprintf ( f, "<metreport type=%s>\n", type );
  // print GTS_HEADER
  if ( m->h != NULL )
    {
      fprintf ( f, "<bufrfile>%s</bufrfile>\n",m->h->filename );
      fprintf ( f, " <gts_header>%s %s %s %s</gts_header>\n",m->h->bname, m->h->center, m->h->dtrel, m->h->order );
    }
  // print DATE AND TIME
  fprintf ( f, " <observation_datetime>%s</observation_datetime>\n",m->t.datime );

  // Geo data
  fprintf ( f, " <geo>\n" );
  if ( strlen ( m->g.index ) )
    {
      fprintf ( f, "  <index>%s</index>\n", m->g.index );
    }
  if ( strlen ( m->g.name ) )
    {
      fprintf ( f, "  <name>%s</name>\n", m->g.name );
    }
  if ( strlen ( m->g.country ) )
    {
      fprintf ( f, "  <country>%s</country>\n", m->g.country );
    }
  fprintf ( f, "  <latitude>%.6lf</latitude>\n", m->g.lat );
  fprintf ( f, "  <longitude>%.6lf</longitude>\n", m->g.lon );
  fprintf ( f, "  <altitude>%.1lf</altitude>\n", m->g.alt );
  fprintf ( f, " </geo>\n" );
  fprintf ( f, " <report>%s=</report>\n", alphanum );
  fprintf ( f, "</metreport>\n" );
  return 0;
}


/*!
  \fn int print_xml(FILE *f, struct metreport *m)
  \brief prints a struct \ref metreport in xml format
  \param f pointer to a file already open by caller routine
  \param m pointer to a struct \ref metreport containing the data to print
*/
int print_xml ( FILE *f, struct metreport *m )
{
  // Single report
  if ( m->alphanum[0] )
    {
      print_xml_alphanum ( f, m->type, m->alphanum, m );
    }

  if ( m->alphanum2[0] ) //TTBB
    {
      print_xml_alphanum ( f, m->type2, m->alphanum2, m );
    }

  if ( m->alphanum3[0] ) //TTCC
    {
      print_xml_alphanum ( f, m->type3, m->alphanum3, m );
    }

  if ( m->alphanum4[0] ) //TTDD
    {
      print_xml_alphanum ( f, m->type4, m->alphanum4, m );
    }

  return 0;
}
