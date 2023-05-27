/*******************************************************************************
* @file    uleds.c
* @author  Guillermo Caporaletti
* @brief   TP3 Testeo Unitario, TSSE, CESE-FIUBA, Co18, 2023. 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "uleds.h"

/* Tipos privados ------------------------------------------------------------*/
typedef struct {
    gpio_t       pinLed;
    bool         inicializado;
    estadoLed_t  estado;
    modoLed_t    modo;
    uint16_t     nEncendido;
    uint16_t     nApagado;
    uint16_t     nActual;
} controlLed_t;

/* Macros y constantes privadas ----------------------------------------------*/
const uint16_t CiclosEncendidos [CANTIDAD_MODOS_LED] = { 10, 7, 5, 3, 2, 1, 200, 500, 100 };
const uint16_t CiclosApagados [CANTIDAD_MODOS_LED]   = {  0, 3, 5, 7, 8, 9, 200, 500, 900 };

/* Variables privadas --------------------------------------------------------*/
controlLed_t vectorLedControl [CANTIDAD_LED] = {0};

/* Declaración de funciones privadas -----------------------------------------*/
bool uLedVerificarId(idLed_t);

/* Definición de funciones privadas ------------------------------------------*/

/*******************************************************************************
* @brief    Verifica que id_led sea válido   
* @param    id_led
* @retval   
*******************************************************************************/
bool uLedVerificarId(idLed_t led_id) {
    if ( led_id < 0) return false;
    if ( led_id >= CANTIDAD_LED) return false;
    if ( vectorLedControl[led_id].inicializado == false ) return false;
    return true;
}


/* Definición de funciones públicas ------------------------------------------*/

/*******************************************************************************
* @brief   
* @param   
* @retval   Un identificador para manejar el led inicializado
*******************************************************************************/
idLed_t uLedInicializar(gpio_t pin_led) {
    idLed_t IdLed = 0;
    bool Id_Establecido = false;
    if (pin_led < GPIO_LED_MINIMO) return ERROR_LED;
    if (pin_led > GPIO_LED_MAXIMO) return ERROR_LED;

    // Verifico que este gpio_t pin_led no haya sido inicializado antes
    for (IdLed = 0; IdLed<CANTIDAD_LED; IdLed++) {
        if ( vectorLedControl[IdLed].pinLed == pin_led && 
             vectorLedControl[IdLed].inicializado == true ) {
            // Ya lo habíamos inicializado...
            // Ya tengo el valor de IdLed adecuado.
            Id_Establecido = true;
            break;
        }
    }

    // Si no había sido inicializado, busco Id libre
    if ( false == Id_Establecido ) {
        for (IdLed = 0; IdLed<CANTIDAD_LED; IdLed++) {
            if ( vectorLedControl[IdLed].inicializado == false ) {
                // Encontramos un Id libre
                Id_Establecido = true;
                break;
            }
        }
    }

    if ( Id_Establecido == false ) return ERROR_LED;

    // Reseteamos valores
    vectorLedControl[IdLed].pinLed = pin_led;
    vectorLedControl[IdLed].estado = LED_APAGADO;
    vectorLedControl[IdLed].modo = PREDETERMINADO;
    vectorLedControl[IdLed].nActual = 0;
    vectorLedControl[IdLed].nEncendido = CiclosEncendidos[vectorLedControl[IdLed].modo];
    vectorLedControl[IdLed].nApagado = CiclosApagados[vectorLedControl[IdLed].modo];
    vectorLedControl[IdLed].inicializado =true;
    if ( false == gpioInicializar (pin_led, SALIDA) ) return ERROR_LED;

    // Inicialización exitosa
    return IdLed;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedEncender(idLed_t led_id) {
    if ( false == uLedVerificarId(led_id) ) return false;
    vectorLedControl[led_id].nActual = 0;
    vectorLedControl[led_id].estado = LED_ENCENDIDO;
    if (false == uLedActualizar(led_id) ) return false;
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedApagar(idLed_t led_id) {
    if ( false == uLedVerificarId(led_id) ) return false;
    vectorLedControl[led_id].estado = LED_APAGADO;
    if (false == uLedActualizar(led_id) ) return false;
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedActualizar(idLed_t led_id) {
    bool salida = false;
    if ( false == uLedVerificarId(led_id) ) return false;

    if ( LED_APAGADO == vectorLedControl[led_id].estado) {
        // Led apagado
        salida = false;
    } else if ( vectorLedControl[led_id].nActual < vectorLedControl[led_id].nEncendido ) {
        // Led estado-encendido dentro del ciclo-encendido
        salida = true;
    } else {
        salida = false;
    }

    gpioEscribir (vectorLedControl[led_id].pinLed, salida);
    vectorLedControl[led_id].nActual++;
    if ( vectorLedControl[led_id].nActual >= 
        (vectorLedControl[led_id].nEncendido + vectorLedControl[led_id].nApagado) ) {
        // Se cumplió un período de ciclos completo
        vectorLedControl[led_id].nActual = 0;
    }
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedConfigurarModo(idLed_t led_id, modoLed_t led_modo) {
    if ( false == uLedVerificarId(led_id) ) return false;
    vectorLedControl[led_id].modo = led_modo;
    vectorLedControl[led_id].nEncendido = CiclosEncendidos[vectorLedControl[led_id].modo];
    vectorLedControl[led_id].nApagado = CiclosApagados[vectorLedControl[led_id].modo];
    return true;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedObtenerEstado(idLed_t led_id) {
    if ( false == uLedVerificarId(led_id) ) return false;
    return vectorLedControl[led_id].estado;
}

/*******************************************************************************
* @brief   Obtiene el modo de operación del led
* @param   led id
* @retval  modo del led
*******************************************************************************/
modoLed_t uLedObtenerModo(idLed_t led_id) {
    if ( false == uLedVerificarId(led_id) ) return (modoLed_t) ERROR;
    return vectorLedControl[led_id].modo;
}

/*******************************************************************************
* @brief   
* @param   
* @retval
*******************************************************************************/
bool uLedDesinicializar(idLed_t led_id) {
    if ( false == uLedVerificarId(led_id) ) return false;
    vectorLedControl[led_id].inicializado =false;
    return true;
}