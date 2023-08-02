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

void setup_gpios()
{
    gpio_pad_select_gpio(LED_VERDE);
    gpio_set_direction(LED_VERDE, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(LED_AMARELO);
    gpio_set_direction(LED_AMARELO, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(BT_PIN);
    gpio_set_direction(BT_PIN, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(BOTAO_VERDE);
    gpio_set_direction(BOTAO_VERDE, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(BOTAO_BRANCO);
    gpio_set_direction(BOTAO_BRANCO, GPIO_MODE_INPUT);
}

void print_novo_estado(enum estado_t* estado)
{
    if(*estado == FECHADO)
        printf("FECHADO");
    else if(*estado == FECHANDO)
        printf("FECHANDO");
    else if(*estado == ABRINDO)
        printf("ABRINDO");
    else if(*estado == ABERTO)
        printf("ABERTO");

    return;
}

void novo_estado(enum estado_t* estado, bool* p_flag_ABERTO, bool* p_flag_FECHADO, bool* p_flag_BOTAO_PRESSIONADO)
{
    if(*estado == FECHADO && *p_flag_BOTAO_PRESSIONADO)
        *estado = ABRINDO;

    else if(*estado == ABRINDO && *p_flag_ABERTO)
        *estado = ABERTO;

    else if(*estado == ABERTO && *p_flag_BOTAO_PRESSIONADO)
        *estado = FECHANDO;

    else if(*estado == FECHANDO && *p_flag_FECHADO)
        *estado = FECHADO;
    
    return;
}

void funcao_estado(enum estado_t* estado, bool* p_flag_ABERTO, bool* p_flag_FECHADO, bool* p_flag_BOTAO_PRESSIONADO)
{
    if(*estado == FECHADO)
        funcao_FECHADO();

    else if(*estado == ABRINDO)
    {
        funcao_ABRINDO(&p_flag_ABERTO, &p_flag_FECHADO);
    }

    else if(*estado == ABERTO)
        funcao_ABERTO();

    else if(*estado == FECHANDO)
    {
        funcao_FECHANDO(&p_flag_ABERTO, &p_flag_FECHADO);
    }

    return;
}

// TODO
void funcao_FECHADO(void)
{
    
    gpio_set_level(LED_VERDE, 0);
    gpio_set_level(LED_AMARELO, 0);

    return;
}

void funcao_FECHANDO(bool* p_flag_ABERTO, bool* p_flag_FECHADO)
{
    gpio_set_level(LED_VERDE, 0);
    gpio_set_level(LED_AMARELO, 1);

    while(!(*p_flag_FECHADO)) vTaskDelay(10 / portTICK_PERIOD_MS);

    *p_flag_ABERTO = 0;

    return;
}

void funcao_ABERTO(void)
{
    gpio_set_level(LED_VERDE, 1);
    gpio_set_level(LED_AMARELO, 1);

    return;
}

void funcao_ABRINDO(bool* p_flag_ABERTO, bool* p_flag_FECHADO)
{
    gpio_set_level(LED_VERDE, 1);
    gpio_set_level(LED_AMARELO, 0);

    while(!(*p_flag_ABERTO)) vTaskDelay(10 / portTICK_PERIOD_MS);

    *p_flag_FECHADO = 0;

    return;
}