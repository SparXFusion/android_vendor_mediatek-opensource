/*
 * Copyright (C) 2020 The Evolution X Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NMEA_PARSER_H__
#define __NMEA_PARSER_H__

#include "hal_mnl_interface_common.h"
#include "mnl_common.h"

// for different SV parse
typedef enum {
    UNKNOWN_SV = 0,
    GPS_SV,
    SBAS_SV,
    GLONASS_SV,
    QZSS_SV,
    BDS_SV,
    GALILEO_SV,
    IRNSS_SV,
} SV_TYPE;

typedef enum {
    GNSS_SYSTEM_ID_GP =  1,
    GNSS_SYSTEM_ID_GL =  2,
    GNSS_SYSTEM_ID_GA =  3,
    GNSS_SYSTEM_ID_BD =  4,
    GNSS_SYSTEM_ID_QZ =  5,
    GNSS_SYSTEM_ID_IR =  6,
    GNSS_SYSTEM_ID_SBAS =  7,
    GNSS_SYSTEM_ID_MAX,
} GNSS_SYSTEM_ID;

typedef enum {
    SIGNAL_ID_GP_ALL    = 0,
    SIGNAL_ID_GP_L1_CA  = 1,
    SIGNAL_ID_GP_L1_P   = 2,
    SIGNAL_ID_GP_L1_M   = 3,
    SIGNAL_ID_GP_L2_P   = 4,
    SIGNAL_ID_GP_L2C_M  = 5,
    SIGNAL_ID_GP_L2C_L  = 6,
    SIGNAL_ID_GP_L5_I   = 7,
    SIGNAL_ID_GP_L5_Q   = 8,
} SIGNAL_ID_GP;

typedef enum {
    SIGNAL_ID_QZ_ALL    = 0,
    SIGNAL_ID_QZ_L1_CA  = 1,
    SIGNAL_ID_QZ_L1_C   = 2,
    SIGNAL_ID_QZ_L2_C   = 3,
    SIGNAL_ID_QZ_L5     = 4,
    SIGNAL_ID_QZ_L1_SAIF= 5,
    SIGNAL_ID_QZ_LEX    = 6,
} SIGNAL_ID_QZ;

typedef enum {
    SIGNAL_ID_GL_ALL    = 0,
    SIGNAL_ID_GL_G1_CA  = 1,
    SIGNAL_ID_GL_G1_P   = 2,
    SIGNAL_ID_GL_G2_CA  = 3,
    SIGNAL_ID_GL_G2_P   = 4,
} SIGNAL_ID_GL;

typedef enum {
    SIGNAL_ID_GA_ALL    = 0,
    SIGNAL_ID_GA_E5A    = 1,
    SIGNAL_ID_GA_E5B    = 2,
    SIGNAL_ID_GA_E5AB   = 3,
    SIGNAL_ID_GA_E6_A   = 4,
    SIGNAL_ID_GA_E6_BC  = 5,
    SIGNAL_ID_GA_L1_A   = 6,
    SIGNAL_ID_GA_L1_BC  = 7,
} SIGNAL_ID_GA;

typedef enum {
    SIGNAL_ID_BD_ALL    = 0,
    SIGNAL_ID_BD_B1     = 1,
    SIGNAL_ID_BD_B1_C   = 2,
    SIGNAL_ID_BD_B2     = 3,
    SIGNAL_ID_BD_B2_A   = 4,
    SIGNAL_ID_BD_B3     = 5,
} SIGNAL_ID_BD;


/*****************************************************************/
/*****************************************************************/
/*****                                                       *****/
/*****       N M E A   P A R S E R                           *****/
/*****                                                       *****/
/*****************************************************************/
/*****************************************************************/
#define  NMEA_MAX_SIZE  255
/*maximum number of SV information in GPGSV*/
#define  NMEA_MAX_SV_INFO 4
#define  LOC_FIXED(pNmeaReader) ((pNmeaReader->fix_mode == 2) || (pNmeaReader->fix_mode ==3))
typedef struct {
    int     pos;
    int     overflow;
    int     utc_year;
    int     utc_mon;
    int     utc_day;
    int     utc_diff;
    gps_location  fix;

    /*
     * The fix flag extracted from GPGSA setence: 1: No fix; 2 = 2D; 3 = 3D
     * if the fix mode is 0, no location will be reported via callback
     * otherwise, the location will be reported via callback
     */
    int     fix_mode;
    /*
     * Indicate that the status of callback handling.
     * The flag is used to report GPS_STATUS_SESSION_BEGIN or GPS_STATUS_SESSION_END:
     * (0) The flag will be set as true when callback setting is changed via nmea_reader_set_callback
     * (1) GPS_STATUS_SESSION_BEGIN: receive location fix + flag set + callback is set
     * (2) GPS_STATUS_SESSION_END:   receive location fix + flag set + callback is null
     */
    int     cb_status_changed;
    int     sv_count;           /*used to count the number of received SV information*/
    gnss_sv_info  sv_status;
    // GpsCallbacks callbacks;
    char    in[ NMEA_MAX_SIZE+1 ];
} NmeaReader;

typedef struct {
    const char*  p;
    const char*  end;
} Token;

#define  MAX_NMEA_TOKENS  64

typedef struct {
    int     count;
    Token   tokens[ MAX_NMEA_TOKENS ];
} NmeaTokenizer;

void mtk_mnl_nmea_parser_process(const char * buffer, UINT32 length);
int get_gps_nmea_parser_end_status();
void mnld_get_mnl_version(char *mnl_ver);

#endif
