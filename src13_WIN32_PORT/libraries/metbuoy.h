/* $Id$ */
/***************************************************************************
 *   Copyright (C) 2004-2018 by Guillermo Ballester Valor                  *
 *   gbv@ogimet.com                                                        *
 *                                                                         *
 *   This file is part of bufr2synop                                       *
 *                                                                         *
 *   Ogimet is free software; you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Ogimet is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
/*!
   \file metbuoy.h
   \brief Main header file for buoy related tasks
*/
#ifndef METBUOY_H
#define METBUOY_H


/*! \def BUOY_SEC0
    \brief mask bit meaning section 0 of buoy is solicited to or parsed with success
*/
#define BUOY_SEC0 1

/*! \def BUOY_SEC1
    \brief mask bit meaning section 1 of buoy is solicited to or parsed with success
*/
#define BUOY_SEC1 2

/*! \def BUOY_SEC2
    \brief mask bit meaning section 2 of buoy is solicited to or parsed with success
*/
#define BUOY_SEC2 4

/*! \def BUOY_SEC3
    \brief mask bit meaning section 3 of buoy is solicited to or parsed with success
*/
#define BUOY_SEC3 8

/*! \def BUOY_SEC4
    \brief mask bit meaning section 4 of buoy is solicited to or parsed with success
*/
#define BUOY_SEC4 16

/*! \def BUOY_EXT
    \brief mask bit meaning date extension is parsed with success
*/
#define BUOY_EXT 32


/*! \struct buoy_sec0
    \brief contains all possible substrings from section 0 when a report is parsed with success
*/
struct buoy_sec0
{
  char MiMi[4]; /*!< MiMi item. (Code table 2582) */
  char MjMj[4]; /*!< MjMj item. (Code table 2582) */
  char A1[2]; /*!< A1 item. WMO region */
  char bw[2]; /*!< bw item. WMO subregion */
  char nbnbnb[8]; /*!< kins and serial number for buoy */
  char D_D[8]; /*!< Ship signal*/
  char YY[4]; /*!< Day (UTC) of observation */
  char MM[4]; /*!< Month (UTC) of observation 01, 02 .... 12 */
  char J[4]; /*!< Least significant digit of year */
  char GG[4]; /*!< Hour (UTC) of observation */
  char gg[4]; /*!< Minute (UTC) of observation */
  char iw[2]; /*!< Indicator for source and units used in speed wind data */
  char Qc[2]; /*!< Quadrant of the Globe (Code table 3333) */
  char LaLaLaLaLa[8]; /*!< Latitude, precision up to in 0.001 degree */
  char LoLoLoLoLoLo[8]; /*!< Longitude, precision up to 0.001 degree */
  char Ql[2]; /*!< Quality control indicator for position (Code Table 3334) */
  char Qt[2]; /*!< Quality control for time (Code Table 3334) */
  char QA[2]; /*!< Location quality class (Code table 3302) */
};

/*! \struct buoy_sec1
    \brief contains all possible substrings from section 1 when a report is parsed with success
*/
struct buoy_sec1
{
  char Qd[2]; /*!< Quality control indicatitor (Code Table 3334) */
  char Qx[2]; /*!< Indicator of position of group (Regulation 18.3.3) */
  char dd[4]; /*!< True direction, in tens of degrees, from which wind is blowing (Code table 0877) */
  char ff[4]; /*!< Wind speed, in units indicated by iw. */
  char fff[4]; /*!< Wind speed, in units indicated by iw, of 99 units or more. */
  char sn1[2]; /*!< Sign of temperature (Code table 3845) */
  char TTT[4]; /*!< Air temperature, in tenths of a degree Celsius, its sign being given by sn1. */
  char sn2[2]; /*!< Sign of dewpoint temperature (Code table 3845)  */
  char TdTdTd[4]; /*!< Dew-point temperature, in tenths of a degree Celsius, its sign being given by sn2. */
  char UUU[4]; /*!< Relative humidity of the air, in per cent, the first figure being zero except for UUU = 100 percent.*/
  char PoPoPoPo[6]; /*!< Pressure at station level, in tenths of a hectopascal, omitting thousands digit of hectopascals of the pressure value. */
  char PPPP[6]; /*!< Pressure at mean sea level, in tenths of a hectopascal, omitting the thousands digit of hectopascals of the pressure value. */
  char a[2]; /*!< Characteristic of pressure tendency during the three hours preceding the time of observation. (Code table 0200) */
  char ppp[4]; /*!< Amount of pressure tendency at station level during the three hours preceding the time of observation, expressed in tenths of a hectopascal. */
};

/*! \struct buoy_sec2
    \brief contains all possible substrings from section 2 when a report is parsed with success
*/
struct buoy_sec2
{
  char Qd[2]; /*!< Quality control indicatitor (Code Table 3334) */
  char Qx[2]; /*!< Indicator of position of group (Regulation 18.3.3) */
  char sn[2]; /*!< Sign of temperature (Code table 3845) */
  char TwTwTw[4]; /*!< Sea surfacer temperature, in tenths of a degree Celsius, its sign being given by sn. */
  char PwaPwa[4]; /*!< Period of waves, obtained by instrumental methods, in seconds. */
  char HwaHwa[4]; /*!< heigh of waves, in units of 0.5 metre */
  char PwaPwaPwa[6]; /*!< Period of waves, obtained by instrumental methods, in tenths of a second.*/
  char HwaHwaHwa[6]; /*!< heigh of waves, in tenths of metre */
};

/*!
  \struct b_sec3_layer1
  \brief A layer with Temperature and salinity for a buoy report
*/
struct b_sec3_layer1
{
  char zzzz[6]; /*!< Meters below sea level */
  char TTTT[6]; /*!< Temperature in cents of celsius degrees */
  char SSSS[6]; /*!< Salinity in cents of parts per 1000 */
};

/*!
  \struct b_sec3_layer2
  \brief A layer with direction and speed for a sea current
*/
struct b_sec3_layer2
{
  char zzzz[6]; /*!< Meters below sea level */
  char dd[4]; /*!< Direction of current in ten degrees */
  char ccc[6]; /*!< Current speed in cm/s */
};

/*! \struct buoy_sec3
    \brief contains all possible substrings from section 3 when a report is parsed with success
*/
struct buoy_sec3
{
  char Qd1[2]; /*!< Quality control for temperature and salinity (Table 3334)*/
  char Qd2[2]; /*!< Quality control for direction and speed (Table 3334)*/
  char k2[2]; /*!< Method for salinity measurement (Table 2263)*/
  char k3[2]; /*!< Duration and medition of current speed */
  char k6[2]; /*!< Method to eliminate the effect the ship or buoy movement */
  struct b_sec3_layer1 l1[32]; /*!< Array of temperature and salinity for layers */
  struct b_sec3_layer2 l2[32]; /*!< Array of direction and speed for layers */
};

/*! \struct buoy_sec4
    \brief contains all possible substrings from section 4 when a report is parsed with success
*/
struct buoy_sec4
{
  char Qp[2]; /*!< Quality of the pressure measurement. (Code table 3315) */
  char Q2[2]; /*!< Quality of the housekeeping parameter (second word in first block of ARGOS platform
transmitters terminal sensor data). (Code table 3363) */
  char QTW[2]; /*!< Quality of the measurement of the water-surface temperature. (Code table 3319)(FM 18)  */
  char Q4[2]; /*!< Quality of the measurement of air temperature. (Code table 3363) */
  char QN[2]; /*!< Quality of the buoy satellite transmission. (Code table 3313) */
  char QL[2]; /*!< Quality of location.(Code table 3311)  */
  char QA[2]; /*!< Location quality class (Code table 3302)  */
  char Qz[2]; /*!< Indicator of depth correction (indication whetherprobe depths are corrected using hydrostatic pressure or not). (Code table 3318)  */
  char Qc[2]; /*!< Quadrant of the globe. (Code table 3333)  */
  char LaLaLaLaLa[8]; /*!<  Latitude, in thousandths of a degree. */
  char LoLoLoLoLoLo[8]; /*!< Longitude, in thousandths of a degree. */
  char YY[4]; /*!< Day of the month (UTC), with 01 indicating the first day, 02 the second day, etc. */
  char MM[4]; /*!< Month of the year (UTC), i.e. 01 = January; 02 = February, etc.  */
  char J[2]; /*!<  Units digit of the year (UTC), i.e. 1974 = 4.  */
  char GGgg[8]; /*!< Time of observation, in hours and minutes UTC. */
  char ZhZhZhZh[6]; /*!< Hydrostatic pressure of lower end of cable, in kPa.  */
  char ZcZcZcZc[6]; /*!< Length of cable, in metres (thermistor strings). */
  char BtBt[4]; /*!<   */
  char XtXt[4]; /*!< Typeof drogue. Code table 4780) */
  char AhAhAh[6]; /*!< Anemometer height expressed in decimetres. */
  char AN[2]; /*!< Type of anemometer. (Code table 0114)  */
  char VBVB[4]; /*!< Drifting speed, in cm s–1, of the buoy at the last known position of the buoy given in the groups YYMMJ GGgg/  */
  char dBdB[4]; /*!< Drift direction of the buoy, expressed in tens of degrees, at the last known position of the
  buoy given in the groups YYMMJ GGgg/ */
  char ViViViVi[6]; /*!< Information on the engineering status of the buoy. */
  char ZdZdZd[6]; /*!< Length of the cable at which the drogue is attached, in metres. */
};


/*! \struct buoy_chunks
    \brief contains all possible substrings from a synop report is parsed with success
*/
struct buoy_chunks
{
  int mask; /*!< Mask with sections parsed succesfully */
  struct report_date_ext e; /*!< struct with the optional extension parsed */
  struct buoy_sec0 s0; /*!< struct with parsed header and section 0 */
  struct buoy_sec1 s1; /*!< struct with parsed section 1 */
  struct buoy_sec2 s2; /*!< struct with parsed section 2 if present */
  struct buoy_sec3 s3; /*!< struct with parsed section 3 if present */
  struct buoy_sec4 s4; /*!< struct with parsed section 4 if present */
  char error[128]; /*!< string with error code if a wrong synop report is found */
};

#endif
