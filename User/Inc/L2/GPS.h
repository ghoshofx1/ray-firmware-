#ifndef GPS_H
#define GPS_H
#include "GPS_types.h"
#include <stdint.h>

#define GPS_CB_SIZE 8

/* Things to be done on GPS side: 
1. Implement true form of circular buffer - the push() needs to wrap around after reaching the maximum size
2. Implement application-facing parsing functions for NMEA sentences - most important are GGA, GLL, GSA, GSV, RMC
3. Refactor code such for cleaner API via GPS header */

uint8_t GPS_pop(GPS_RMC_t *out);
void GPS_init(void);

void GPS_push_line(const char* line, int length);

#endif 