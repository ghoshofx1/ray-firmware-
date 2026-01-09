#include "GPS.h"
#include "GPS_types.h"
#include "USART_driver.h"
#include <stdint.h>
#include <string.h>

#define GPS_BUFFER_MAX_SIZE 8

typedef struct {
    gps_rmc_t buffer[GPS_CB_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
    volatile uint8_t count;
} GPS_circular_buffer_t;

/*Main circular buffer for GPS messages*/
static GPS_circular_buffer_t gps_cbuf;


static uint8_t gps_cbuf_push_isr(const gps_rmc_t *fix)
{
    uint8_t next = (gps_cbuf.head + 1) % GPS_BUFFER_MAX_SIZE;

    if (next == gps_cbuf.tail)
        return 0; // full → drop

    gps_cbuf.buffer[gps_cbuf.head] = *fix;
    gps_cbuf.head = next;
    gps_cbuf.count++;
    return 1;
}

static uint8_t parse_rmc_fast(const char* line, gps_rmc_t* fix)
{

    fix->valid = 1; // Assume valid for this stub
    fix->lat_e7 = 123456789; // Dummy data
    fix->lon_e7 = 987654321; // Dummy data
    fix->utc_time = 123456; // Dummy data
    fix->utc_date = 230421; // Dummy data
    fix->speed_cms = 1000; // Dummy data
    fix->course_cd = 9000; // Dummy data

    return 1; // Indicate success
}

/* Called ONLY from UART ISR */
void GPS_push_line(const char* line, int length)
{   
    {
    if (length < 7)
        return;

    if (memcmp(line, "$GNRMC", 6) != 0)
        return;

    gps_rmc_t fix;

    if (!parse_rmc_fast(line, &fix))
        return;

    gps_cbuf_push_isr(&fix);
}

}

void GPS_init(void)
{
    GPS_arm_receive_interrupt();
}

uint8_t GPS_pop(gps_rmc_t *out)
{
    if (gps_cbuf.head == gps_cbuf.tail)
        return 0; // empty

    *out = gps_cbuf.buffer[gps_cbuf.tail];
    gps_cbuf.tail = (gps_cbuf.tail + 1) % GPS_BUFFER_MAX_SIZE;
    return 1;
}