#include <stdio.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "rom/gpio.h"

#include "maqest.h"

enum estado_t estado = FECHADO;

bool flag_FECHADO = 1;
bool flag_ABERTO = 0;
bool flag_BOTAO_PRESSIONADO = 0;

bool button = 0;
bool last_button = 0;


void app_main()
{
    setup_gpios();

    while(1)
    {
        button = gpio_get_level(BT_PIN);

        if (button && !last_button)
        {
            flag_BOTAO_PRESSIONADO = 1;
        }

        novo_estado(&estado, &flag_ABERTO, &flag_FECHADO, &flag_BOTAO_PRESSIONADO);
        funcao_estado(&estado, &flag_ABERTO, &flag_FECHADO, &flag_BOTAO_PRESSIONADO);

        flag_BOTAO_PRESSIONADO = 0;
        last_button = button;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}