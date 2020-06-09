/***************************************************************************
 *   Copyright (C) 2013-2017 by Guillermo Ballester Valor                  *
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
 \file bufrtotac.h
 \brief Include header file for binary bufrtotac
*/
#include "bufrdeco.h"
#include "bufr2tac.h"

// To use package config.h
#ifndef CONFIG_H
# include "config.h"
# define CONFIG_H
#endif

extern struct bufrdeco BUFR;
extern struct bufrdeco_subset_sequence_data SEQ;
extern struct bufrdeco_compressed_data_references REF;
extern struct metreport REPORT;
extern struct bufr2tac_subset_state STATE;

extern const char SELF[];
extern char ERR[256];
extern char INPUTFILE[256];
extern char OUTPUTFILE[256];
extern char BUFRTABLES_DIR[256];
extern char LISTOFFILES[256];
extern int NFILES;
extern int GTS_HEADER;
extern int XML;
extern int JSON;
extern int CSV;
extern int DEBUG;
extern int VERBOSE;
extern int SHOW_SEQUENCE;
extern int ECMWF;
extern int HTML;
extern int NOTAC;
extern int FIRST_SUBSET, LAST_SUBSET;
extern FILE *FL;

// functions
void print_usage ( void );
int read_args ( int _argc, char * _argv[] );
char * get_bufrfile_path ( char *filename, char *err );
int bufrdeco_parse_subset_sequence ( struct metreport *m, struct bufr2tac_subset_state *st, struct bufrdeco *b,
                                     char *err );
