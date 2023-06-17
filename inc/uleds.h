/*******************************************************************************
* @file    uleds.h
* @author  Guillermo Caporaletti
* @brief   TP3 Testeo Unitario, TSSE, CESE-FIUBA, Co18, 2023. 
*******************************************************************************/

/* Para evitar inclusiones recursivas ----------------------------------------*/
#ifndef __ULEDS
#define __ULEDS

/* Librerías incluídas -------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "upuerto_HAL.h"
#include "upuerto_OSAL.h"

/* Macros públicas -----------------------------------------------------------*/
#define CANTIDAD_LED    16
#define CANTIDAD_MODOS_LED  9
#define LED_ENCENDIDO   true
#define LED_APAGADO     false
#define ERROR_LED       -1

/* Tipos de datos ------------------------------------------------------------*/
typedef int16_t idLed_t;
typedef bool estadoLed_t;
typedef enum {
    PLENO,
    PREDETERMINADO = PLENO,
    INTENSIDAD100 = PLENO,
    INTENSIDAD70,
    INTENSIDAD50,
    INTENSIDAD30,
    INTENSIDAD20,
    INTENSIDAD10,
    TITILANTE,
    TITILANTE_LENTO,
    BALIZA,
    ERROR,
} modoLed_t;

/* Constantes ----------------------------------------------------------------*/

/* Declaración de funciones públicas -----------------------------------------*/
idLed_t uLedInicializar(gpio_t id_pin);
bool uLedEncender(idLed_t led_id);
bool uLedApagar(idLed_t led_id);
bool uLedActualizar(idLed_t led_id);
bool uLedConfigurarModo(idLed_t led_id, modoLed_t led_modo);
bool uLedObtenerEstado(idLed_t led_id);
bool uLedObtenerEstadoFisico(idLed_t led_id);
modoLed_t uLedObtenerModo(idLed_t led_id);
bool uLedDesinicializar(idLed_t led_id);

/* Fin de #ifndef __ULEDS ----------------------------------------------------*/
#endif

/************************************************************* FIN DE ARCHIVO */