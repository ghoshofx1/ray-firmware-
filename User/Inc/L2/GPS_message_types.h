#ifndef GPS_MESSAGE_TYPES_H
#define GPS_MESSAGE_TYPES_H

#include <stdint.h>

typedef struct {
    uint8_t  valid;
    int32_t  lat_e7;
    int32_t  lon_e7;
    uint32_t utc_time;
    uint32_t utc_date;
    uint16_t speed_cms;
    uint16_t course_cd;
} GPS_RMC_t;


#endif /* GPS_MESSAGE_TYPES_H */