#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"


/* SPI could be HSPI or VSPI bus: 
 *
 * HSPI-> MOSI 13, MISO 12, SCK 14, CS 15
 * VSPI-> MOSI 23, MISO 19, SCK 18, CS 55
 * 
 */

#define MOSI_GPIO 13
#define MISO_GPIO 12
#define SPI_SCLK 14
#define SPI_CS 15


//LED_DOT ARRAY ADDRESS DEFINES:
#define DECODE_MODE_REG 0x9 //0
#define INTENSITY_REG 0x0A //7
#define SCAN_LIMIT_REG 0xB //7
#define SHUTDOWN_REG 0xC //1
#define DISPLAY_TEST_REG 0xF //0

spi_device_handle_t spi_device_handle;

#define LED_TEST_TIME 500


static esp_err_t init_spi(void)
{
    spi_bus_config_t spi_bus_config = {};
    spi_bus_config.mosi_io_num = MOSI_GPIO;
    spi_bus_config.miso_io_num = MISO_GPIO;
    spi_bus_config.sclk_io_num = SPI_SCLK;
    spi_bus_config.quadwp_io_num = -1;
    spi_bus_config.quadhd_io_num = -1;
    spi_bus_config.max_transfer_sz = 32;

    spi_device_interface_config_t spi_device_interface_config = {};
    //spi_device_interface_config.command_bits = x;
    //spi_device_interface_config.address_bits = x;
    spi_device_interface_config.mode = 0;
    spi_device_interface_config.duty_cycle_pos = 128; //por defecto
    spi_device_interface_config.clock_speed_hz = 1000000; //1MHZ
    spi_device_interface_config.spics_io_num = SPI_CS;
    spi_device_interface_config.flags = SPI_DEVICE_HALFDUPLEX;
    spi_device_interface_config.queue_size = 1;
    spi_device_interface_config.pre_cb = NULL;
    spi_device_interface_config.post_cb = NULL;

    spi_bus_initialize(SPI2_HOST, &spi_bus_config, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST, &spi_device_interface_config, &spi_device_handle);

    return ESP_OK;
}

static void spi_write(uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};
    spi_transaction_t spi_transaction = {
        .tx_buffer = data,
        .length = 16

    };
    spi_device_transmit(spi_device_handle, &spi_transaction);
}

static esp_err_t max7219_init(void)
{
    spi_write(DECODE_MODE_REG, 0);
    spi_write(INTENSITY_REG, 7);
    spi_write(SCAN_LIMIT_REG, 7);
    spi_write(SHUTDOWN_REG, 1);
    spi_write(DISPLAY_TEST_REG, 0);
    return ESP_OK;
}

static void clear_max7219(void)
{
    for (size_t i = 0; i<8; i++)
    {
        spi_write(i+1, 0);
    }
}

static void testMax7219(void)
{
    //BLINK
    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();        

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();  

    //WAVING EFFECT
    spi_write(1, 0xFF);
    spi_write(2, 0x81);
    spi_write(3, 0x81);
    spi_write(4, 0x81);
    spi_write(5, 0x81);
    spi_write(6, 0x81);
    spi_write(7, 0x81);
    spi_write(8, 0xFF);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x7E);
    spi_write(3, 0x42);
    spi_write(4, 0x42);
    spi_write(5, 0x42);
    spi_write(6, 0x42);
    spi_write(7, 0x7E);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x3C);
    spi_write(4, 0x24);
    spi_write(5, 0x24);
    spi_write(6, 0x3C);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x18);
    spi_write(5, 0x18);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay(LED_TEST_TIME/portTICK_PERIOD_MS);
    clear_max7219();

    //ODD&EVEN EFECT   

    spi_write(1, 0xAA);
    spi_write(2, 0x55);
    spi_write(3, 0xAA);
    spi_write(4, 0x55);
    spi_write(5, 0xAA);
    spi_write(6, 0x55);
    spi_write(7, 0xAA);
    spi_write(8, 0x55);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();  

    spi_write(1, 0x55);
    spi_write(2, 0xAA);
    spi_write(3, 0x55);
    spi_write(4, 0xAA);
    spi_write(5, 0x55);
    spi_write(6, 0xAA);
    spi_write(7, 0x55);
    spi_write(8, 0xAA);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xAA);
    spi_write(2, 0x55);
    spi_write(3, 0xAA);
    spi_write(4, 0x55);
    spi_write(5, 0xAA);
    spi_write(6, 0x55);
    spi_write(7, 0xAA);
    spi_write(8, 0x55);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();  

    spi_write(1, 0x55);
    spi_write(2, 0xAA);
    spi_write(3, 0x55);
    spi_write(4, 0xAA);
    spi_write(5, 0x55);
    spi_write(6, 0xAA);
    spi_write(7, 0x55);
    spi_write(8, 0xAA);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xAA);
    spi_write(2, 0x55);
    spi_write(3, 0xAA);
    spi_write(4, 0x55);
    spi_write(5, 0xAA);
    spi_write(6, 0x55);
    spi_write(7, 0xAA);
    spi_write(8, 0x55);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();  

    spi_write(1, 0x55);
    spi_write(2, 0xAA);
    spi_write(3, 0x55);
    spi_write(4, 0xAA);
    spi_write(5, 0x55);
    spi_write(6, 0xAA);
    spi_write(7, 0x55);
    spi_write(8, 0xAA);
    vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
    clear_max7219();

    //HORIZONTAL WAVING
    spi_write(1, 0x80);
    spi_write(2, 0x80);
    spi_write(3, 0x80);
    spi_write(4, 0x80);
    spi_write(5, 0x80);
    spi_write(6, 0x80);
    spi_write(7, 0x80);
    spi_write(8, 0x80);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xC0);
    spi_write(2, 0xC0);
    spi_write(3, 0xC0);
    spi_write(4, 0xC0);
    spi_write(5, 0xC0);
    spi_write(6, 0xC0);
    spi_write(7, 0xC0);
    spi_write(8, 0xC0);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xE0);
    spi_write(2, 0xE0);
    spi_write(3, 0xE0);
    spi_write(4, 0xE0);
    spi_write(5, 0xE0);
    spi_write(6, 0xE0);
    spi_write(7, 0xE0);
    spi_write(8, 0xE0);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x70);
    spi_write(2, 0x70);
    spi_write(3, 0x70);
    spi_write(4, 0x70);
    spi_write(5, 0x70);
    spi_write(6, 0x70);
    spi_write(7, 0x70);
    spi_write(8, 0x70);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x38);
    spi_write(2, 0x38);
    spi_write(3, 0x38);
    spi_write(4, 0x38);
    spi_write(5, 0x38);
    spi_write(6, 0x38);
    spi_write(7, 0x38);
    spi_write(8, 0x38);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x1C);
    spi_write(2, 0x1C);
    spi_write(3, 0x1C);
    spi_write(4, 0x1C);
    spi_write(5, 0x1C);
    spi_write(6, 0x1C);
    spi_write(7, 0x1C);
    spi_write(8, 0x1C);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x0E);
    spi_write(2, 0x0E);
    spi_write(3, 0x0E);
    spi_write(4, 0x0E);
    spi_write(5, 0x0E);
    spi_write(6, 0x0E);
    spi_write(7, 0x0E);
    spi_write(8, 0x0E);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x07);
    spi_write(2, 0x07);
    spi_write(3, 0x07);
    spi_write(4, 0x07);
    spi_write(5, 0x07);
    spi_write(6, 0x07);
    spi_write(7, 0x07);
    spi_write(8, 0x07);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x03);
    spi_write(2, 0x03);
    spi_write(3, 0x03);
    spi_write(4, 0x03);
    spi_write(5, 0x03);
    spi_write(6, 0x03);
    spi_write(7, 0x03);
    spi_write(8, 0x03);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x01);
    spi_write(2, 0x01);
    spi_write(3, 0x01);
    spi_write(4, 0x01);
    spi_write(5, 0x01);
    spi_write(6, 0x01);
    spi_write(7, 0x01);
    spi_write(8, 0x01);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x80);
    spi_write(2, 0x80);
    spi_write(3, 0x80);
    spi_write(4, 0x80);
    spi_write(5, 0x80);
    spi_write(6, 0x80);
    spi_write(7, 0x80);
    spi_write(8, 0x80);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xC0);
    spi_write(2, 0xC0);
    spi_write(3, 0xC0);
    spi_write(4, 0xC0);
    spi_write(5, 0xC0);
    spi_write(6, 0xC0);
    spi_write(7, 0xC0);
    spi_write(8, 0xC0);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xE0);
    spi_write(2, 0xE0);
    spi_write(3, 0xE0);
    spi_write(4, 0xE0);
    spi_write(5, 0xE0);
    spi_write(6, 0xE0);
    spi_write(7, 0xE0);
    spi_write(8, 0xE0);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x70);
    spi_write(2, 0x70);
    spi_write(3, 0x70);
    spi_write(4, 0x70);
    spi_write(5, 0x70);
    spi_write(6, 0x70);
    spi_write(7, 0x70);
    spi_write(8, 0x70);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x38);
    spi_write(2, 0x38);
    spi_write(3, 0x38);
    spi_write(4, 0x38);
    spi_write(5, 0x38);
    spi_write(6, 0x38);
    spi_write(7, 0x38);
    spi_write(8, 0x38);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x1C);
    spi_write(2, 0x1C);
    spi_write(3, 0x1C);
    spi_write(4, 0x1C);
    spi_write(5, 0x1C);
    spi_write(6, 0x1C);
    spi_write(7, 0x1C);
    spi_write(8, 0x1C);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x0E);
    spi_write(2, 0x0E);
    spi_write(3, 0x0E);
    spi_write(4, 0x0E);
    spi_write(5, 0x0E);
    spi_write(6, 0x0E);
    spi_write(7, 0x0E);
    spi_write(8, 0x0E);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x07);
    spi_write(2, 0x07);
    spi_write(3, 0x07);
    spi_write(4, 0x07);
    spi_write(5, 0x07);
    spi_write(6, 0x07);
    spi_write(7, 0x07);
    spi_write(8, 0x07);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x03);
    spi_write(2, 0x03);
    spi_write(3, 0x03);
    spi_write(4, 0x03);
    spi_write(5, 0x03);
    spi_write(6, 0x03);
    spi_write(7, 0x03);
    spi_write(8, 0x03);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x01);
    spi_write(2, 0x01);
    spi_write(3, 0x01);
    spi_write(4, 0x01);
    spi_write(5, 0x01);
    spi_write(6, 0x01);
    spi_write(7, 0x01);
    spi_write(8, 0x01);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();
    //VERTICAL WAVING

    spi_write(1, 0xFF);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();        


    spi_write(1, 0xFF);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0xFF);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0xFF);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0xFF);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0xFF);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0xFF);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0xFF);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0xFF);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0xFF);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();

    spi_write(1, 0x00);
    spi_write(2, 0x00);
    spi_write(3, 0x00);
    spi_write(4, 0x00);
    spi_write(5, 0x00);
    spi_write(6, 0x00);
    spi_write(7, 0x00);
    spi_write(8, 0x00);
    vTaskDelay((LED_TEST_TIME/4)/portTICK_PERIOD_MS);
    clear_max7219();        


}

static void printLedMatrix1D(uint8_t symb, bool test, bool tick)
{
    if (test != true)
    {
        if (tick == false)
        {
            if (symb == 0)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x14);
                spi_write(4, 0x14);
                spi_write(5, 0x14);
                spi_write(6, 0x14);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);
            }
            else if (symb == 1)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x08);
                spi_write(3, 0x18);
                spi_write(4, 0x08);
                spi_write(5, 0x08);
                spi_write(6, 0x08);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);
            }
            else if (symb == 2)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x14);
                spi_write(4, 0x04);
                spi_write(5, 0x08);
                spi_write(6, 0x10);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }
            else if (symb == 3)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x04);
                spi_write(4, 0x04);
                spi_write(5, 0x1C);
                spi_write(6, 0x04);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }
            else if (symb == 4)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x14);
                spi_write(3, 0x14);
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, 0x04);
                spi_write(7, 0x04);
                spi_write(8, 0x00);            
            }
            else if (symb == 5)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x10);
                spi_write(4, 0x10);
                spi_write(5, 0x1C);
                spi_write(6, 0x04);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }                
            else if (symb == 6)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x10);
                spi_write(4, 0x10);
                spi_write(5, 0x1C);
                spi_write(6, 0x14);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }
            else if (symb == 7)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x14);
                spi_write(4, 0x04);
                spi_write(5, 0x04);
                spi_write(6, 0x04);
                spi_write(7, 0x04);
                spi_write(8, 0x00);            
            }
            else if (symb == 8)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x14);
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, 0x14);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }
            else if (symb == 9)
            {
                spi_write(1, 0x00);
                spi_write(2, 0x1C);
                spi_write(3, 0x14);
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, 0x04);
                spi_write(7, 0x1C);
                spi_write(8, 0x00);            
            }                        
            else
            {
                testMax7219();
            }
        }
        else if (tick == true)
        {
            if (symb == 0)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x14);
                spi_write(5, 0x14);
                spi_write(6, (0x14 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);
            }
            else if (symb == 1)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x08 | 0x40));
                spi_write(3, (0x18 | 0x40));
                spi_write(4, 0x08);
                spi_write(5, 0x08);
                spi_write(6, (0x08 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);
            }
            else if (symb == 2)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x04);
                spi_write(5, 0x08);
                spi_write(6, (0x10 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 3)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x04 | 0x40));
                spi_write(4, 0x04);
                spi_write(5, 0x1C);
                spi_write(6, (0x04 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 4)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x14 | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, (0x04 | 0x40));
                spi_write(7, (0x04 | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 5)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x10 | 0x40));
                spi_write(4, 0x10);
                spi_write(5, 0x1C);
                spi_write(6, (0x04 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }                
            else if (symb == 6)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x10 | 0x40));
                spi_write(4, 0x10);
                spi_write(5, 0x1C);
                spi_write(6, (0x14 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 7)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x04);
                spi_write(5, 0x04);
                spi_write(6, (0x04 | 0x40));
                spi_write(7, (0x04 | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 8)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, (0x14 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }
            else if (symb == 9)
            {
                spi_write(1, 0x00);
                spi_write(2, (0x1C | 0x40));
                spi_write(3, (0x14 | 0x40));
                spi_write(4, 0x14);
                spi_write(5, 0x1C);
                spi_write(6, (0x04 | 0x40));
                spi_write(7, (0x1C | 0x40));
                spi_write(8, 0x00);            
            }                        
            else
            {
                testMax7219();
            }
        }
        else
        {
            testMax7219();
        }
    }
    else
    {
        testMax7219();
    }    


}



void app_main(void)
{
	uint8_t displayed_number = 0;
    bool led_test = false;
    bool seconds_ticking = true;
    ESP_ERROR_CHECK(init_spi());
    ESP_ERROR_CHECK(max7219_init());
    clear_max7219();
    while (1)
    {
        //printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        
        displayed_number = 0;
        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;

        printLedMatrix1D(displayed_number, led_test, !seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        printLedMatrix1D(displayed_number, led_test, seconds_ticking);
        vTaskDelay((LED_TEST_TIME/2)/portTICK_PERIOD_MS);
        displayed_number++;
        
    }

    

}
