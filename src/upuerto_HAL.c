/*******************************************************************************
* @file     upuerto_HAL.c
* @author   Guillermo Caporaletti
* @brief    Funciones HAL de manejo de GPIO.
*           TP3 Testeo Unitario, TSSE, CESE-FIUBA, Co18, 2023. 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "upuerto_HAL.h"

/* Tipos privados ------------------------------------------------------------*/
typedef struct {
    bool        inicializado;
    bool        salida;
    modoGpio_t  modo;
} controlGpio_t;

/* Macros y constantes privadas ----------------------------------------------*/

/* Variables privadas --------------------------------------------------------*/
controlGpio_t vectorGpioControl [CANTIDAD_GPIO] = {0};

/* Declaración de funciones privadas -----------------------------------------*/

/* Definición de funciones privadas ------------------------------------------*/

/* Definición de funciones públicas ------------------------------------------*/

/*******************************************************************************
* @brief   
* @param   
* @retval   true si tuvo éxito, false si hubo error.
*******************************************************************************/
bool gpioInicializar (gpio_t id_pin, modoGpio_t io) {
    if (id_pin >= CANTIDAD_GPIO) return false;
    vectorGpioControl[id_pin].modo = io;
    vectorGpioControl[id_pin].salida = false;
    vectorGpioControl[id_pin].inicializado = true;
    // TODO: Acá debería ir la función HAL correspondiente.
    // TODO: Falta también una tabla con las direcciones físicas de cada id_pin.
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval   true si tuvo éxito, false si hubo error.
*******************************************************************************/
bool gpioLeer (gpio_t id_pin, bool * p_valor) {
    if (id_pin >= CANTIDAD_GPIO) return false;
    if (vectorGpioControl[id_pin].inicializado == false) return false;
    *p_valor = vectorGpioControl[id_pin].salida;
    // TODO: Acá debería ir la función HAL correspondiente.
    // TODO: Falta también una tabla con las direcciones físicas de cada id_pin.
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval   true si tuvo éxito, false si hubo error.
*******************************************************************************/
bool gpioEscribir (gpio_t id_pin, bool valor) {
    if (id_pin >= CANTIDAD_GPIO) return false;
    if (vectorGpioControl[id_pin].inicializado == false) return false;
    if (vectorGpioControl[id_pin].modo < SALIDA) return false;
    // TODO: Acá debería ir la función HAL correspondiente.
    // TODO: Falta también una tabla con las direcciones físicas de cada id_pin.
    vectorGpioControl[id_pin].salida = valor;
    return true;
}
