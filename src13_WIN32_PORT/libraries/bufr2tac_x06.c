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
 \file bufr2tac_x06.c
 \brief decodes the descriptors with X = 06 (Horizontal Position-2)
 */
#include "bufr2tac.h"


/*!
  \fn char * latlon_to_MMM(char *target, double lat, double lon)
  \brief convert latitude and longitude to a MMM string
  \param lat latitude (degree, N positive)
  \param lon longitude (degree, E positive)
  \param target resulting MMM string
*/
char * latlon_to_MMM ( char *target, double lat, double lon )
{
  int col, row, ori = 0;

  if ( lon < 0.0 )
    col = ( int ) ( -lat * 0.1 ) + 1;
  else
    col = 36 - ( int ) ( lat * 0.1 );


  if ( lat >= 80.0 )
    row = 25;
  else if ( lat >=  0.0 )
    row = ( int ) ( lat * 0.1 );
  else
    {
      ori = 299;
      row = ( int ) ( -lat * 0.1 );
    }

  sprintf ( target,"%03d", col + ori + row * 36 );

  return target;
}

/*!
  \fn int syn_parse_x06 ( struct synop_chunks *syn, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 06
  \param syn pointer to a struct \ref synop_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int syn_parse_x06 ( struct synop_chunks *syn, struct bufr2tac_subset_state *s )
{
  int ia;

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    return 0;

  switch ( s->a->desc.y )
    {
    case 1: // 0 06 001 . Longitude (High accuracy)
    case 2: // 0 06 002 . Longitude (Coarse)
      if ( s->val < 0.0 )
        s->mask |= SUBSET_MASK_LONGITUDE_WEST; // Sign for longitude
      s->mask |= SUBSET_MASK_HAVE_LONGITUDE;
      ia = ( int ) ( fabs ( s->val ) * 10.0 + 0.5 );
      sprintf ( syn->s0.LoLoLoLo, "%04d",ia );
      syn->s0.Ulo[0] = syn->s0.LoLoLoLo[2];
      s->lon = s->val;
      break;
    default:
      break;
    }

  // check if set both LaLaLa and LoLoLoLo to set Qc
  if ( ( syn->s0.Qc[0] == 0 ) && syn->s0.LaLaLa[0] && syn->s0.LoLoLoLo[0] )
    {
      if ( s->mask & SUBSET_MASK_LATITUDE_SOUTH )
        {
          if ( s->mask & SUBSET_MASK_LONGITUDE_WEST )
            strcpy ( syn->s0.Qc, "5" );
          else
            strcpy ( syn->s0.Qc, "3" );
        }
      else
        {
          if ( s->mask & SUBSET_MASK_LONGITUDE_WEST )
            strcpy ( syn->s0.Qc, "7" );
          else
            strcpy ( syn->s0.Qc, "1" );
        }
    }

  // check if about MMM
  if ( ( syn->s0.MMM[0] == 0 ) && syn->s0.LaLaLa[0] && syn->s0.LoLoLoLo[0] )
    {
      latlon_to_MMM ( syn->s0.MMM, s->lat, s->lon );
    }

  return 0;
}

/*!
  \fn int buoy_parse_x06 ( struct buoy_chunks *b, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 06
  \param b pointer to a struct \ref buoy_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int buoy_parse_x06 ( struct buoy_chunks *b, struct bufr2tac_subset_state *s )
{
  int ia;

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    return 0;

  switch ( s->a->desc.y )
    {
    case 1: // 0 06 001 . Longitude (High accuracy)
    case 2: // 0 06 002 . Longitude (Coarse accuracy)
      if ( s->val < 0.0 )
        s->mask |= SUBSET_MASK_LONGITUDE_WEST; // Sign for longitude
      s->mask |= SUBSET_MASK_HAVE_LONGITUDE;
      s->lon = s->val;
      ia = ( int ) ( fabs ( s->val ) * 1000.0 + 0.5 );
      sprintf ( b->s0.LoLoLoLoLoLo, "%06d",ia );
      break;
    default:
      break;
    }
  return 0;
}


/*!
  \fn int climat_parse_x06 ( struct climat_chunks *c, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 06
  \param c pointer to a struct \ref climat_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int climat_parse_x06 ( struct climat_chunks *c, struct bufr2tac_subset_state *s )
{
  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    return 0;

  // this is to avoid warning
  if ( c == NULL )
    return 1;

  switch ( s->a->desc.y )
    {
    case 1: // 0 06 001 . Longitude (High accuracy)
    case 2: // 0 06 002 . Longitude (Coarse accuracy)
      if ( s->val < 0.0 )
        s->mask |= SUBSET_MASK_LONGITUDE_WEST; // Sign for longitude
      s->mask |= SUBSET_MASK_HAVE_LONGITUDE;
      s->lon = s->val;
      break;
    default:
      break;
    }
  return 0;
}

/*!
  \fn int temp_parse_x06 ( struct tempop_chunks *t, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 06
  \param t pointer to a struct \ref temp_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int temp_parse_x06 ( struct temp_chunks *t, struct bufr2tac_subset_state *s )
{
  int ia;

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    return 0;

  switch ( s->a->desc.y )
    {
    case 1: // 0 06 001 . Longitude (High accuracy)
    case 2: // 0 06 002 . Longitude (Coarse)
      if ( s->val < 0.0 )
        s->mask |= SUBSET_MASK_LONGITUDE_WEST; // Sign for longitude
      s->mask |= SUBSET_MASK_HAVE_LONGITUDE;
      ia = ( int ) ( fabs ( s->val ) * 10.0 + 0.5 );
      sprintf ( t->a.s1.LoLoLoLo, "%04d",ia );
      sprintf ( t->b.s1.LoLoLoLo, "%04d",ia );
      sprintf ( t->c.s1.LoLoLoLo, "%04d",ia );
      sprintf ( t->d.s1.LoLoLoLo, "%04d",ia );
      t->a.s1.Ulo[0] = t->a.s1.LoLoLoLo[2];
      t->b.s1.Ulo[0] = t->b.s1.LoLoLoLo[2];
      t->c.s1.Ulo[0] = t->c.s1.LoLoLoLo[2];
      t->d.s1.Ulo[0] = t->d.s1.LoLoLoLo[2];
      s->lon = s->val;

      // check if set both LaLaLa and LoLoLoLo to set Qc
      if ( ( t->a.s1.Qc[0] == 0 ) && t->a.s1.LaLaLa[0] && t->a.s1.LoLoLoLo[0] )
        {
          if ( s->mask & SUBSET_MASK_LATITUDE_SOUTH )
            {
              if ( s->mask & SUBSET_MASK_LONGITUDE_WEST )
                strcpy ( t->a.s1.Qc, "5" );
              else
                strcpy ( t->a.s1.Qc, "3" );
            }
          else
            {
              if ( s->mask & SUBSET_MASK_LONGITUDE_WEST )
                strcpy ( t->a.s1.Qc, "7" );
              else
                strcpy ( t->a.s1.Qc, "1" );
            }
          strcpy ( t->b.s1.Qc, t->a.s1.Qc );
          strcpy ( t->c.s1.Qc, t->a.s1.Qc );
          strcpy ( t->d.s1.Qc, t->a.s1.Qc );
        }

      // check if about MMM
      if ( ( t->a.s1.MMM[0] == 0 ) && t->a.s1.LaLaLa[0] && t->a.s1.LoLoLoLo[0] )
        {
          latlon_to_MMM ( t->a.s1.MMM, s->lat, s->lon );
          strcpy ( t->b.s1.MMM, t->a.s1.MMM );
          strcpy ( t->c.s1.MMM, t->a.s1.MMM );
          strcpy ( t->d.s1.MMM, t->a.s1.MMM );
        }
      break;

    case 15: // 0 06 015. Longitude displacement since launch site (high accuracy)
      if ( s->rep > 0 && s->r->n > 0 )
        {
          s->r->raw[s->r->n - 1].dlon = s->val;
        }
      else if ( s->w->n > 0 )
        {
          s->w->raw[s->w->n - 1].dlon = s->val;
        }
      break;

    default:
      break;
    }


  return 0;
}
