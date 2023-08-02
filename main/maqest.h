#pragma once

#include <stdbool.h>

#define LED_VERDE 2
#define LED_AMARELO 4
#define BT_PIN 21

#define BOTAO_VERDE 23
#define BOTAO_BRANCO 22


enum estado_t {
    FECHADO,
    ABRINDO,
    ABERTO,
    FECHANDO
};


void setup_gpios();
void print_novo_estado(enum estado_t* estado_);
void novo_estado(enum estado_t* estado, bool* p_flag_ABERTO, bool* p_flag_FECHADO, bool* p_flag_BOTAO_PRESSIONADO);

void funcao_estado(enum estado_t* estado, bool* p_flag_ABERTO, bool* p_flag_FECHADO, bool* p_flag_BOTAO_PRESSIONADO);

void funcao_FECHADO(void);
void funcao_FECHANDO(bool* p_flag_ABERTO, bool* p_flag_FECHADO);
void funcao_ABERTO(void);
void funcao_ABRINDO(bool* p_flag_ABERTO, bool* p_flag_FECHADO);