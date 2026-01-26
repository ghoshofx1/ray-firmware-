#include "L2/Radio.h"
#include "L1/SPI_driver.h"
#include <stdbool.h>
#include "L2/Radio_typedefs.h"

static sx126x_status_t sx126x_set_standby(const sx126x_standby_cfg_t cfg)
{

    const uint8_t buf[SX126X_SIZE_SET_STANDBY] = {
        SX126X_SET_STANDBY,
        (uint8_t)cfg,
    };

    return (sx126x_status_t)sx126x_hal_write(buf, SX126X_SIZE_SET_STANDBY, 0, 0);
}

static sx126x_status_t sx126x_set_pkt_type(const sx126x_pkt_type_t pkt_type)
{

    const uint8_t buf[SX126X_SIZE_SET_PKT_TYPE] = {
        SX126X_SET_PKT_TYPE,
        (uint8_t)pkt_type,
    };

    return (sx126x_status_t)sx126x_hal_write(buf, SX126X_SIZE_SET_PKT_TYPE, 0, 0);
}

static sx126x_status_t sx126x_set_rf_freq(const uint32_t freq_in_hz)
{
}

static sx126x_status_t sx126x_set_pa_cfg(const sx126x_pa_cfg_params_t *params)
{
}

static sx126x_status_t sx126x_set_tx_params(const int8_t pwr_in_dbm, const sx126x_ramp_time_t ramp_time)
{
}

static sx126x_status_t sx126x_set_buffer_base_address(const uint8_t tx_base_address,
                                                      const uint8_t rx_base_address)
{
}

static sx126x_status_t sx126x_write_buffer(const uint8_t offset, const uint8_t *buffer,
                                           const uint8_t size)
{
}

static sx126x_status_t sx126x_set_lora_mod_params(const sx126x_mod_params_lora_t *params)
{
}

static sx126x_status_t sx126x_set_lora_pkt_params(const sx126x_pkt_params_lora_t *params)
{
}

static sx126x_status_t sx126x_set_dio_irq_params(const uint16_t irq_mask, const uint16_t dio1_mask,
                                                 const uint16_t dio2_mask, const uint16_t dio3_mask)
{
}

sx126x_status_t sx126x_set_lora_sync_word(const uint8_t sync_word)
{
}

sx126x_status_t sx126x_set_tx(const uint32_t timeout_in_ms)
{
}

sx126x_status_t sx126x_set_tx_with_timeout_in_rtc_step(const uint32_t timeout_in_rtc_step)
{
}
