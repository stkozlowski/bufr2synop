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
 \file bufr2tac_x13.c
 \brief decodes the descriptors with X = 13 . Precipitation and hidrology
 */
#include "bufr2tac.h"

/*!
  \fn char * prec_to_RRR ( char *target, double r )
  \brief converts a precipitation in Kg/m2 into a RRR string
  \param r the precipitation
  \param target the resulting string
*/
char * prec_to_RRR ( char *target, double r )
{
  if ( r == 0.0 )
    {
      strcpy ( target,"000" );
    }
  else if ( r > -0.11 && r < -0.09 ) // this is an approach to -0.1
    {
      strcpy ( target,"990" );
    }
  else if ( r < 0.95 )
    {
      sprintf ( target, "99%d", ( int ) ( r * 10.0 + 0.5 ) );
    }
  else if ( r >= 989.0 )
    {
      strcpy ( target,"989" );
    }
  else
    {
      sprintf ( target, "%03d", ( int ) ( r + 0.5 ) );
    }
  return target;

}

/*!
  \fn char * prec_to_RRRR ( char *target, double r )
  \brief converts a precipitation in Kg/m2 into a RRRR string (code table 3596)
  \param r the precipitation
  \param target the resulting string
*/
char * prec_to_RRRR ( char *target, double r )
{
  if ( r < 0.0 || ( r > 0.0 && r < 0.1 ) )
    {
      strcpy ( target,"9999" );
    }
  else if ( r <= 8899.0 )
    {
      sprintf ( target,"%04d", ( int ) ( r + 0.5 ) );
    }
  else
    {
      strcpy ( target,"8899" );
    }
  return target;
}

/*!
  \fn char * prec_to_RRRR24 ( char *target, double r )
  \brief converts a precipitation in Kg/m2 into a RRRR24 string
  \param r the precipitation
  \param target the resulting string
*/
char * prec_to_RRRR24 ( char *target, double r )
{
  if ( r < 0.0 || ( r > 0.0 && r < 0.1 ) )
    {
      strcpy ( target,"9999" );
    }
  else if ( r <= 999.8 )
    {
      sprintf ( target,"%04d", ( int ) ( r * 10.0 + 0.5 ) );
    }
  else
    {
      strcpy ( target,"9998" );
    }
  return target;
}

/*!
  \fn char * prec_to_RxRxRxRx ( char *target, double r )
  \brief converts a precipitation in Kg/m2 into a RxRxRxRx string
  \param r the precipitation
  \param target the resulting string
*/
char * prec_to_RxRxRxRx ( char *target, double r )
{
  sprintf ( target,"%04d", ( int ) ( r * 10.0 + 0.5 ) );
  return target;
}



/*!
  \fn char * total_snow_depth_to_sss ( char *target, double r )
  \brief converts tatal snow depth in m to sss (code table 3889)
  \param r recent snow depth in meters
  \param target the resulting string
*/
char * total_snow_depth_to_sss ( char *target, double r )
{
  int i;
  if ( r >= 0.0 )
    i = ( int ) ( r * 100.0 + 0.5 ); // convert to cm
  else
    i = ( int ) ( r * 100.0 - 0.5 ); // convert to cm

  if ( i > 0 && i <= 996 )
    {
      sprintf ( target, "%03d", i );
    }
  else if ( i == -1 )
    {
      sprintf ( target, "997" );
    }
  else if ( i == -2 )
    {
      sprintf ( target, "998" );
    }
  else
    {
      sprintf ( target, "999" );
    }
  return target;
}

/*!
  \fn char * recent_snow_to_ss( char *target, double r )
  \brief converts recent snow in m to ss (code table 3870)
  \param r recent snow depth in meters
  \param target the resulting string
*/
char * recent_snow_to_ss ( char *target, double r )
{
  int i;
  i = ( int ) ( r * 1000.0 + 0.5 ); // convert to mm

  if ( i == 0 )
    {
      sprintf ( target,"00" );
    }
  else if ( i < 0 )
    {
      sprintf ( target,"97" );
    }
  else if ( i < 7 )
    {
      sprintf ( target,"%02d", i + 90 );
    }
  else if ( i < 600 )
    {
      sprintf ( target,"%02d", i / 10 );
    }
  else if ( i <= 4000 )
    {
      sprintf ( target,"%02d", 50 + i/100 );
    }
  else if ( i > 4000 )
    {
      sprintf ( target,"98" );
    }
  else
    {
      sprintf ( target,"99" );
    }
  return target;
}

/*!
  \fn int syn_parse_x13 ( struct synop_chunks *syn, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 13
  \param syn pointer to a struct \ref synop_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int syn_parse_x13 ( struct synop_chunks *syn, struct bufr2tac_subset_state *s )
{
  int tpd, hr;
  char aux[8];

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    {
      return 0;
    }

  switch ( s->a->desc.y )
    {
    case 3: // 0 13 003 . Relative humidity %
      if ( s->ival < 0 || s->ival > 100 )
        {
          return 0;
        }
      sprintf ( syn->s1.UUU, "%03d", s->ival );
      syn->mask |= SYNOP_SEC1;
      break;

    case 11: // 0 13 011 . Total precipitation
        if ( s->val < 0.0 )
        {
           if (s->val < -0.11 || s->val > -0.09)  
             return 0; 
        }
      tpd = time_period_duration ( s );
      hr = hour_rounded ( syn );
      if ( tpd ==  3600 )
        {
          if ( syn->s3.RRR[0] == 0 )
            {
              if ( strcmp ( "1", syn->s0.A1 ) == 0 ||
                   strcmp ( "2", syn->s0.A1 ) == 0 ||
                   strcmp ( "3", syn->s0.A1 ) == 0 ||
                   strcmp ( "4", syn->s0.A1 ) == 0 ||
                   strcmp ( "5", syn->s0.A1 ) == 0 ||
                   strcmp ( "6", syn->s0.A1 ) == 0 )
                {
                  /*if ( hr % 3)
                    {*/
                  syn->s3.tr[0] = '5'; // 1 hour
                  prec_to_RRR ( syn->s3.RRR, s->val );
                  syn->mask |= SYNOP_SEC3;
                  /*}*/
                }
            }
          else if ( syn->s5.RRR[0] == 0 )
            {
              syn->s5.tr[0] = '5'; // 1 hour
              prec_to_RRR ( syn->s5.RRR, s->val );
              syn->mask |= SYNOP_SEC5;
            }
        }
      else if ( tpd == 7200 )
        {
          if ( syn->s1.RRR[0] == 0 )
            {
              if ( strcmp ( "6", syn->s0.A1 ) )
                {
                  //Not for REG IV
                  syn->s1.tr[0] = '6'; // 2 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
        }
      else if ( tpd == 10800 )
        {
          if ( ( hr % 3 ) == 0 )
            {
              if ( syn->s3.tr[0] == '5' )
                {
                  syn->s5.tr[0] = '5';
                  strcpy ( syn->s5.RRR, syn->s3.RRR );
                  syn->mask |= SYNOP_SEC5;
                }
              syn->s3.tr[0] = '7'; // 3 hour
              prec_to_RRR ( syn->s3.RRR, s->val );
              syn->mask |= SYNOP_SEC3;
            }
        }
      else if ( tpd == ( 6 * 3600 ) )
        {
          if ( strcmp ( "1", syn->s0.A1 ) == 0 )
            {
              if ( ( hr % 12 ) == 0 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
            {
              if ( ( hr % 3 )  == 0 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "3", syn->s0.A1 ) == 0 )
            {
              if ( hr == 0 ||
                   hr == 6 ||
                   hr == 18 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "4", syn->s0.A1 ) == 0 )
            {
              if ( ( hr % 6 ) == 0 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "5", syn->s0.A1 ) == 0 )
            {
              if ( hr == 6  ||
                   hr == 12 ||
                   hr == 18 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
            {
              if ( hr == 0 ||
                   hr == 18 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
            {
              if ( hr == 6 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }

          // last chance
          if ( syn->s1.RRR[0] == 0 )
            {
              if ( ( hr % 6 ) == 0 )
                {
                  syn->s1.tr[0] = '1'; // 6 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
        }
      else if ( tpd == ( 9 * 3600 ) )
        {
          if ( syn->s3.RRR[0] == 0 )
            {
              syn->s3.tr[0] = '8'; // 9 hour
              prec_to_RRR ( syn->s3.RRR, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( syn->s5.RRR[0] == 0 )
            {
              syn->s5.tr[0] = '8'; // 9 hour
              prec_to_RRR ( syn->s5.RRR, s->val );
              syn->mask |= SYNOP_SEC5;
            }
        }
      else if ( tpd == ( 12 * 3600 ) )
        {
          if ( strcmp ( "1", syn->s0.A1 ) == 0 )
            {
              if ( hr == 18 )
                {
                  syn->s1.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
            {
              if ( ( hr % 3 ) == 0 )
                {
                  syn->s1.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
            {
              if ( ( hr % 12 ) == 6 )
                {
                  syn->s1.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
          else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
            {
              if ( hr == 12 )
                {
                  syn->s1.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }

          // last chance
          if ( syn->s1.RRR[0] == 0 )
            {
              if ( ( hr % 6 ) == 0 )
                {
                  syn->s1.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
              else if ( ( hr % 3 ) == 0 )
                {
                  if ( syn->s3.RRR[0] == 0 )
                    {
                      syn->s3.tr[0] = '2'; // 12 hour
                      prec_to_RRR ( syn->s3.RRR, s->val );
                      syn->mask |= SYNOP_SEC3;
                    }
                  else if ( syn->s3.tr[0] == '1' ||
                            syn->s3.tr[0] == '5' )
                    {
                      strcpy ( syn->s5.tr, syn->s3.tr );
                      strcpy ( syn->s5.RRR, syn->s3.RRR );
                      syn->mask |= SYNOP_SEC5;
                      syn->s3.tr[0] = '2'; // 12 hour
                      prec_to_RRR ( syn->s3.RRR, s->val );
                      syn->mask |= SYNOP_SEC3;
                    }
                }
            }
        }
      else if ( tpd == ( 15 * 3600 ) )
        {
          if ( syn->s3.RRR[0] == 0 )
            {
              syn->s3.tr[0] = '9'; // 15 hour
              prec_to_RRR ( syn->s3.RRR, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( syn->s5.RRR[0] == 0 )
            {
              syn->s5.tr[0] = '9'; // 15 hour
              prec_to_RRR ( syn->s5.RRR, s->val );
              syn->mask |= SYNOP_SEC5;
            }
        }
      else if ( tpd == ( 18 * 3600 ) )
        {
          if ( strcmp ( "7", syn->s0.A1 ) == 0 )
            {
              if ( hr == 18 )
                {
                  syn->s1.tr[0] = '3'; // 12 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
        }
      else if ( tpd == ( 24 * 3600 ) )
        {
          if ( strcmp ( "1", syn->s0.A1 ) == 0 )
            {
              if ( hr == 6 )
                {
                  syn->s1.tr[0] = '4'; // 24 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
            {
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( strcmp ( "3", syn->s0.A1 ) == 0 )
            {
              if ( hr == 12 )
                {
                  syn->s1.tr[0] = '4'; // 24 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( strcmp ( "4", syn->s0.A1 ) == 0 )
            {
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( strcmp ( "5", syn->s0.A1 ) == 0 )
            {
              if ( hr == 0 )
                {
                  syn->s1.tr[0] = '4'; // 24 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
          else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
            {
              if ( strcmp ( "07", syn->s0.II ) == 0 ) // France
                {
                  if ( strcmp ( "06", syn->e.HH ) == 0 )
                    {
                      prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
                      syn->mask |= SYNOP_SEC3;
                    }
                }
              else
                {
                  prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
                  syn->mask |= SYNOP_SEC3;
                }
            }
          else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
            {
              if ( hr == 0 )
                {
                  syn->s1.tr[0] = '4'; // 24 hour
                  prec_to_RRR ( syn->s1.RRR, s->val );
                  syn->mask |= SYNOP_SEC1;
                }
            }
        }
      break;

    case 13: // 0 13 013 . Total snow depth
      if ( syn->s3.sss[0] == 0 )
        {
          total_snow_depth_to_sss ( syn->s3.sss, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      break;

    case 19: // 0 13 019 . Total precipitaction past 1 hour
      hr = hour_rounded ( syn );
      if ( syn->s3.RRR[0] == 0 )
        {
          if ( strcmp ( "1", syn->s0.A1 ) == 0 ||
               strcmp ( "2", syn->s0.A1 ) == 0 ||
               strcmp ( "3", syn->s0.A1 ) == 0 ||
               strcmp ( "4", syn->s0.A1 ) == 0 ||
               strcmp ( "5", syn->s0.A1 ) == 0 ||
               strcmp ( "6", syn->s0.A1 ) == 0 )
            {
              /*if ( hr % 3)
                {*/
              syn->s3.tr[0] = '5'; // 1 hour
              prec_to_RRR ( syn->s3.RRR, s->val );
              syn->mask |= SYNOP_SEC3;
              /*}*/
            }
        }
      else if ( syn->s5.RRR[0] == 0 )
        {
          syn->s5.tr[0] = '5'; // 1 hour
          prec_to_RRR ( syn->s5.RRR, s->val );
          syn->mask |= SYNOP_SEC5;
        }
      break;

    case 20: // 0 13 020 . Total precipitation past 3 hours
      hr = hour_rounded ( syn );
      if ( ( hr % 3 ) == 0 )
        {
          if ( syn->s3.tr[0] == '5' )
            {
              syn->s5.tr[0] = '5';
              strcpy ( syn->s5.RRR, syn->s3.RRR );
              syn->mask |= SYNOP_SEC5;
            }
          syn->s3.tr[0] = '7'; // 3 hour
          prec_to_RRR ( syn->s3.RRR, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      break;

    case 21: // 0 13 021 . Total precipitation past 6 hours
      hr = hour_rounded ( syn );
      if ( strcmp ( "1", syn->s0.A1 ) == 0 )
        {
          if ( ( hr % 12 ) == 0 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
        {
          if ( ( hr % 3 ) == 0 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "3", syn->s0.A1 ) == 0 )
        {
          if ( hr == 0 ||
               hr == 6 ||
               hr == 18 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "4", syn->s0.A1 ) == 0 )
        {
          if ( ( hr % 6 ) == 0 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "5", syn->s0.A1 ) == 0 )
        {
          if ( hr == 6 ||
               hr == 12 ||
               hr == 18 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
        {
          if ( hr == 0 ||
               hr == 18 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
        {
          if ( hr == 6 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }

      if ( syn->s1.RRR[0] == 0 )
        {
          if ( ( hr % 6 ) == 0 )
            {
              syn->s1.tr[0] = '1'; // 6 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      break;

    case 22: // 0 13 022 . Total precipitation past 12 hours
      hr = hour_rounded ( syn );
      if ( strcmp ( "1", syn->s0.A1 ) == 0 )
        {
          if ( hr == 18 )
            {
              syn->s1.tr[0] = '2'; // 12 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
        {
          if ( ( hr % 3 ) == 0 )
            {
              syn->s1.tr[0] = '2'; // 12 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
        {
          if ( ( hr % 12 ) == 6 )
            {
              syn->s1.tr[0] = '2'; // 12 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
        {
          if ( hr == 12 )
            {
              syn->s1.tr[0] = '2'; // 12 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }

      // Last chance
      if ( syn->s1.RRR[0] == 0 )
        {
          if ( ( hr % 6 ) == 0 )
            {
              syn->s1.tr[0] = '2'; // 12 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
          else if ( ( hr % 3 ) == 0 )
            {
              if ( syn->s3.RRR[0] == 0 )
                {
                  syn->s3.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s3.RRR, s->val );
                  syn->mask |= SYNOP_SEC3;
                }
              else if ( syn->s3.tr[0] == '1' ||
                        syn->s3.tr[0] == '5' )
                {
                  strcpy ( syn->s5.tr, syn->s3.tr );
                  strcpy ( syn->s5.RRR, syn->s3.RRR );
                  syn->mask |= SYNOP_SEC5;
                  syn->s3.tr[0] = '2'; // 12 hour
                  prec_to_RRR ( syn->s3.RRR, s->val );
                  syn->mask |= SYNOP_SEC3;
                }
            }
        }

      break;

    case 23: // 0 13 023 . Total precipitaction past 24 hours
      if ( s->val < 0.0 )
        {
          return 0;
        }
      hr = hour_rounded ( syn );
      if ( strcmp ( "1", syn->s0.A1 ) == 0 )
        {
          if ( hr == 6 )
            {
              syn->s1.tr[0] = '4'; // 24 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
          prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      else if ( strcmp ( "2", syn->s0.A1 ) == 0 )
        {
          prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      else if ( strcmp ( "3", syn->s0.A1 ) == 0 )
        {
          if ( hr == 12 )
            {
              syn->s1.tr[0] = '4'; // 24 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
          prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      else if ( strcmp ( "4", syn->s0.A1 ) == 0 )
        {
          prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      else if ( strcmp ( "5", syn->s0.A1 ) == 0 )
        {
          if ( hr == 0 )
            {
              syn->s1.tr[0] = '4'; // 24 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
          prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
          syn->mask |= SYNOP_SEC3;
        }
      else if ( strcmp ( "6", syn->s0.A1 ) == 0 )
        {
          if ( strcmp ( "07", syn->s0.II ) == 0 ) // France
            {
              if ( strcmp ( "06", syn->e.HH ) == 0 )
                {
                  prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
                  syn->mask |= SYNOP_SEC3;
                }
            }
          else
            {
              prec_to_RRRR24 ( syn->s3.RRRR24, s->val );
              syn->mask |= SYNOP_SEC3;
            }
        }
      else if ( strcmp ( "7", syn->s0.A1 ) == 0 )
        {
          if ( hr == 0 )
            {
              syn->s1.tr[0] = '4'; // 24 hour
              prec_to_RRR ( syn->s1.RRR, s->val );
              syn->mask |= SYNOP_SEC1;
            }
        }
      break;

    case 56: // 0 13 056 . Character and intensity of precipitation
      if ( strcmp ( syn->s0.A1, "1" ) == 0 ) // Only for Region I
        {
          sprintf ( aux, "%d", s->ival );
          syn->s3.XoXoXoXo[2] = aux[0];
          syn->mask |= SYNOP_SEC3;
        }
      break;

    case 57: // 0 13 057 . Time of beginning or end of precipitation
      if ( strcmp ( syn->s0.A1, "1" ) == 0 ) // Only for region I
        {
          sprintf ( aux, "%d" , s->ival );
          syn->s3.XoXoXoXo[3] = aux[0];
          syn->mask |= SYNOP_SEC3;
        }
      break;

    case 118: // 0 13 118 . Recent snow depth
      if ( syn->s3.d9.n < SYNOP_NMISC )
        {
          sprintf ( syn->s3.d9.misc[syn->s3.d9.n].SpSp, "931%s", recent_snow_to_ss ( aux, s->val ) );
          ( syn->s3.d9.n ) ++;
        }
      break;
    default:
      break;
    }
  return 0;
}

/*!
  \fn int buoy_parse_x13 ( struct buoy_chunks *b, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 13
  \param b pointer to a struct \ref buoy_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int buoy_parse_x13 ( struct buoy_chunks *b, struct bufr2tac_subset_state *s )
{

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    {
      return 0;
    }

  if ( b == NULL )
    {
      return 1;
    }


  switch ( s->a->desc.y )
    {
    default:
      break;
    }
  return 0;
}

/*!
  \fn int climat_parse_x13 ( struct climat_chunks *c, struct bufr2tac_subset_state *s )
  \brief Parse a expanded descriptor with X = 13
  \param c pointer to a struct \ref climat_chunks where to set the results
  \param s pointer to a struct \ref bufr2tac_subset_state where is stored needed information in sequential analysis

  It returns 0 if success, 1 if problems when processing. If a descriptor is not processed returns 0 anyway
*/
int climat_parse_x13 ( struct climat_chunks *c, struct bufr2tac_subset_state *s )
{

  if ( s->a->mask & DESCRIPTOR_VALUE_MISSING )
    {
      return 0;
    }

  if ( c == NULL )
    {
      return 1;
    }


  switch ( s->a->desc.y )
    {
    case 4: // 0 13 004 . Mean vapor pressure in tenths of hectopascal
      if ( s->is_normal == 0 )
        {
          sprintf ( c->s1.eee,"%03d", ( int ) ( s->val * 0.1 + 0.5 ) );
          c->mask |= CLIMAT_SEC1;
        }
      else
        {
          sprintf ( c->s2.eee,"%03d", ( int ) ( s->val * 0.1 + 0.5 ) );
          c->mask |= CLIMAT_SEC2;
        }
      break;

    case 51: // 0 13 051 . Frequency group precipitation
      if ( s->ival >= 0 && s->ival <= 6 )
        {
          sprintf ( c->s1.Rd, "%d", s->ival );
        }
      break;

    case 52: // 0 13 052 . Highest daily amount of precipitation
      prec_to_RxRxRxRx ( c->s4.RxRxRxRx, s->val );
      if ( s->more_days == 0 )
        {
          sprintf ( c->s4.yr, "%02d", s->day );
        }
      else
        {
          sprintf ( c->s4.yr, "%02d", (s->day + 50) % 50 );
        }
      c->mask |= CLIMAT_SEC4;
      break;

    case 60: // 0 13 060 . Total acumulated precipitation
      if ( s->is_normal == 0 )
        {
          prec_to_RRRR ( c->s1.R1R1R1R1, s->val );
          c->mask |= CLIMAT_SEC1;
        }
      else
        {
          prec_to_RRRR ( c->s2.R1R1R1R1, s->val );
          c->mask |= CLIMAT_SEC2;
        }
      break;
    default:
      break;
    }
  return 0;
}

