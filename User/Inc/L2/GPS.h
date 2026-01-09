#ifndef GPS_H
#define GPS_H
#include "GPS_types.h"
#include <stdint.h>

#define GPS_CB_SIZE 8


uint8_t GPS_pop(gps_rmc_t *out);
void GPS_init(void);

void GPS_push_line(const char* line, int length);




#endif 