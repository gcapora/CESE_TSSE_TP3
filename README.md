# CESE_TSSE_TP3

Testeo sobre el módulo de control de leds. El módulo busca controlar diversos modos indicativos de led: encendico, titilante e intensidad variable. Este módulo será utilizado bajo FreeRTOS. 

## Aclaración: problema a resolver en la implementación

El problema no resuelto aún es la forma de utilización de los gpio físicos. En esta prueba, se accedería a las instrucciones HAL mediante la capa upuerto_HAL.h. Sin embargo, las instrucciones HAL no están implementadas aún, por lo que se hizo el MOCK sobre esta capa directamente. No es la forma más óptima. Como resultado, el atributo estadoFisico de la estructura de cada led indica el estado que debiera tener el pin-led físico en la placa en ese momento.

## Cómo funcionan los modos del led

El titilada de led y la intensidad 50% de led se hacen de la misma forma: con ciclos encendidos y ciclos apagados. Sólo cambia la cantidad total de ciclos que equivale a un período. Se presupone que la función uLedActualizar() es llamada cada 1 milisegundo. 

## Resultado

El test fue exitoso. :-)
