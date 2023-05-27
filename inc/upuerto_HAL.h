/*******************************************************************************
* @file    upuerto_HAL.h
* @author  Guillermo Caporaletti
* @brief   TP3 Testeo Unitario, TSSE, CESE-FIUBA, Co18, 2023. 
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UPUERTO_HAL
#define __UPUERTO_HAL

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//#include "stm32f4xx_hal.h"  		/* <- HAL include */
//#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Macros y constantes públicas ----------------------------------------------*/
#define CANTIDAD_GPIO            32

#define GPIO_LED_ROJO_EN_PLACA   0
#define GPIO_LED_VERDE_EN_PLACA  1
#define GPIO_LED_AZUL_EN_PLACA   2
#define GPIO_LED_GENERADOR_1     3
#define GPIO_LED_GENERADOR_2     4
#define GPIO_LED_CAPTURADORA_1   5
#define GPIO_LED_CAPTURADORA_2   6
#define GPIO_LED_MINIMO          GPIO_LED_ROJO_EN_PLACA
#define GPIO_LED_MAXIMO          GPIO_LED_CAPTURADORA_2


/* Definición de tipos públicos ----------------------------------------------*/
typedef uint8_t gpio_t;
typedef enum {
    ENTRADA,
    ENTRADA_PULL_UP,
    SALIDA,
    SALIDA_COLECTOR_ABIERTO,
} modoGpio_t;

/* Constants -----------------------------------------------------------------*/
/* Declaración de funciones públicas -----------------------------------------*/
bool gpioInicializar (gpio_t id_pin, modoGpio_t io);
bool gpioLeer        (gpio_t id_pin, bool * p_valor);
bool gpioEscribir    (gpio_t id_pin, bool valor);

/* Fin de #ifndef __UPUERTO_HAL ----------------------------------------------*/
#endif

/************************************************************* FIN DE ARCHIVO */