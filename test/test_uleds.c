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
#include "uleds.h"
#include "upuerto_HAL.h"

//TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

// Inicializar un led y verificar su estado apagado.
void test_inicializo_un_led(void) {
  idLed_t led1 = uLedInicializar( GPIO_LED_VERDE_EN_PLACA );
  TEST_ASSERT_TRUE( led1 == 0 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led1 ) == LED_APAGADO);
}

// Inicializar otro led y verificar su estado apagado.
void test_inicializo_otro_led(void) {
  idLed_t led2 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  TEST_ASSERT_TRUE( led2 == 1 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led2 ) == LED_APAGADO);
}

// Inicializar de nuevo el mismo led y verifico su id.
void test_inicializo_de_nuevo_mismo_led(void) {
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  TEST_ASSERT_TRUE( led3 == 1 );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_APAGADO);
}

// Encender un led y verificar su estado.
void test_prendo_led(void) {
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  bool lectura;
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_ENCENDIDO);
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );
}

// Verificar mensaje de error al leer led no inicializado.
void test_verifico_error(void) {
  bool lectura;
  TEST_ASSERT_FALSE( gpioLeer(GPIO_LED_AZUL_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );
}

// Encender y apagar un led y verificar su estado.
void test_prendo_y_apago_led(void) {
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  bool lectura;
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_ENCENDIDO);
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

  TEST_ASSERT_TRUE( uLedApagar(led3) );
  TEST_ASSERT_TRUE( uLedObtenerEstado( led3 ) == LED_APAGADO);
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );
  
}

// Poner en modo titilar, encender y verificar su estado en dos momentos distintos.
// Encender un led y verificar su estado.
void test_titilo_led(void) {
  idLed_t led3 = uLedInicializar( GPIO_LED_ROJO_EN_PLACA );
  bool lectura;
  TEST_ASSERT_TRUE( uLedConfigurarModo(led3, INTENSIDAD50) );
  
  TEST_ASSERT_TRUE( uLedEncender(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );
  
  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_FALSE( lectura );

  TEST_ASSERT_TRUE( uLedActualizar(led3) );
  TEST_ASSERT_TRUE( gpioLeer(GPIO_LED_ROJO_EN_PLACA, &lectura) );
  TEST_ASSERT_TRUE( lectura );

}
