/*******************************************************************************
* @file    test_uleds.c
* @author  Guillermo Caporaletti
* @brief   TP3 Testeo Unitario, TSSE, CESE-FIUBA, Co18, 2023. 
*******************************************************************************/

/*******************************************************************************
 * Testeos a realizar:
 * - Inicializar un led y verificar su estado apagado.
 * - Inicializar otro led y verificar su estado apagado.
 * - Encender un led y verificar su estado.
 * - Encender y apagar el led y verificar su estado.
 * - Poner en modo titilar, encender y verificar su estado en dos momentos distintos.
 * 
*******************************************************************************/

#include <stdint.h>
#include "unity.h"
#include "uleds.h"            // Éste es el módulo a probar
#include "mock_upuerto_HAL.h" // Esto me dice que reemplace la librería upuerto_HAL.h
//#include "upuerto_HAL.h"

//TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

// Inicializar un led y verificar su estado apagado.
void test_inicializo_un_led(void) {
  gpioInicializar_ExpectAndReturn( GPIO_LED_VERDE_EN_PLACA, SALIDA, true);
  idLed_t led1 = uLedInicializar( GPIO_LED_VERDE_EN_PLACA );
  TEST_ASSERT_TRUE( led1 == 0 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led1 ) == LED_APAGADO);
}

// Inicializar otro led y verificar su estado apagado.
void test_inicializo_otro_led(void) {
  gpioInicializar_ExpectAndReturn( GPIO_LED_ROJO_EN_PLACA, SALIDA, true);
  idLed_t led2 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  TEST_ASSERT_TRUE( led2 == 1 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led2 ) == LED_APAGADO);
}

// Inicializar de nuevo el mismo led y verifico su id.
void test_inicializo_de_nuevo_mismo_led(void) {
  gpioInicializar_ExpectAndReturn( GPIO_LED_ROJO_EN_PLACA, SALIDA, true);
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  TEST_ASSERT_TRUE( led3 == 1 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_APAGADO);
}

// Encender un led y verificar su estado.
void test_prendo_led(void) {
  gpioInicializar_ExpectAndReturn( GPIO_LED_ROJO_EN_PLACA, SALIDA, true);
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_ENCENDIDO);

  // Esta parte no tenía sentido...
  // bool lectura;
  // TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  // TEST_ASSERT_TRUE( lectura );
}

// Verificar mensaje de error al leer led no inicializado.
void test_verifico_error(void) {
  
  TEST_ASSERT_FALSE( uLedObtenerEstado( 3 ) == LED_ENCENDIDO);

}

// Encender y apagar un led y verificar su estado.
void test_prendo_y_apago_led(void) {

  gpioInicializar_ExpectAndReturn( GPIO_LED_ROJO_EN_PLACA, SALIDA, true);
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_ENCENDIDO);

  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedApagar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_APAGADO);
  
}


/*
bool gpioInicializar (gpio_t id_pin, modoGpio_t io) {}
bool gpioLeer        (gpio_t id_pin, bool * p_valor) {}
bool gpioEscribir    (gpio_t id_pin, bool valor) {}
*/

// Poner en modo titilar, encender y verificar su estado en dos momentos distintos.
// Encender un led y verificar su estado.
void test_titilo_led(void) {

  gpioInicializar_ExpectAndReturn( GPIO_LED_ROJO_EN_PLACA, SALIDA, true);
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
    
  // Modo que tiene encendido 5 ciclos y apagado otros 5 ciclos
  TEST_ASSERT_TRUE( uLedConfigurarModo(led3, INTENSIDAD50) ); 
  
  // Enciendo en este modo
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

  // 2do ciclo encendido
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

  // 3er ciclo encendido
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

  // 4to ciclo encendido
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

  // 5to ciclo encendido
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

  // 6to ciclo, se apaga
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_APAGADO);

  // 7mo ciclo, apagado
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_APAGADO);

  // 8vo ciclo, apagado
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_APAGADO);

  // 9no ciclo, apagado
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_APAGADO);

  // 10mo ciclo, se apaga
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, false, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_APAGADO);

  // 11vo ciclo, se enciende de nuevo
  gpioEscribir_ExpectAndReturn ( GPIO_LED_ROJO_EN_PLACA, true, true);
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstadoFisico( led3 ) == LED_ENCENDIDO);

}
