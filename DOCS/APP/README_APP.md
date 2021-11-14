[![YecidMorenoUSP - ExoControl](https://img.shields.io/static/v1?label=YecidMorenoUSP&message=ExoControl&color=blue&logo=github)](https://github.com/YecidMorenoUSP/ExoControl)
[![alt](https://img.shields.io/github/license/YecidMorenoUSP/MY_LIBS?color=blue)](LICENSE.md)
![Windows](https://img.shields.io/badge/Windows-x64%20\|%20x86-blue?style=flat&logo=windows)

## REABROB_APP

Esta aplicacion fue diseñada con el objetivo de conectar cada uno de los robts que estan en el laboratorio de rehabilitacion roborica **REABROB**, coo lo es el AnkleBot, ExoTAO, y robot SPAR, ademas de ello tanbien se ha optado por crear una herramienta versaril que disponga de diferentes interfaces de entrada y salida para la interaccion con los robots, para de este modo intentar destar la barrera de programacion que pocaspersonas en el área mecánica conocen.

Mediante la programacion en bloques que de acuerdo a <span style="color:orange;">[REF: beneficons de la programacion en bloques]</span> ha demostrado tener una curva de aprendizaje más agil. 

## Porque C++ ? 

En el mundo de la robótica e del control existen lenguages que son ya conocidos por sus multiples caracteristicas, unos por su versatilidad, facilidad de implementacion u otros por el manejo de recursos a niveles de ejecucin más bajos, en este caso **C++** ya habia sido impleentado con anterioridad en todos los robots, ademas que pertmite la gestion de recursos de una manera más controlada, y rápida. uno de sus puntos debiles es la necesidad de generar un ejecutable diferente cada vez que se realiza un cambio, lo que a su vez tambien se convierte en un punto fuerte de estelenguaje de programacion, pues al ser compilado puede ejecutar instrucciones con una diferencia de tiempo considerable frente a otros lenguajes de programacion.

Además, la mayoria de sensores e equipamentos poseen una API disponible en C++ para su uso, entre ellos tenemos los Xsens, Delsys Trigno EMG, Rehamove3 FES, ESP32, EPOS y EPOS2.

## Es tiempo Real ? 

Como la mayoria de sistemas controlados por microprocesador no son de tiempo real y dependen de otros factores como carga del sistema operativo en recursos, servicios en segundo plano y otros factores que puedan afectar el rendimiento <span style="color:orange;">[REF: Rendimiento de un SO]</span>.

Ademas de las dificultades que se tienen al juntar diferentes sistemas en un solo proceso, como tiempos de sincronizacion, retardos, e problemas de conexion. Para intentar solucionar los cuellos de botella que se presentan en este caso especifico se hará uso de hilos, procesos y subprocesos que comparten informacion usando la memoria RAM, para de esta manera mantaner la sincronia del sistema, este modelo puede tener algunos problemas que son esperados, y demostrados en <span style="color:orange;">[REF: Subprocesos a diferentes frecuancias]</span>, y que en teoria no son tratables, como una discretizacion diferente debido a tiempos de muestreo diferente, aunque la sincronizacion del sistema estará en armonia.

## Modo de funcionamiento

## Versatilidad

Debido a que se usará C++ coo lenguaje d e programacion principal existen muchas posivilidades de usar APIs genericas de algunos dispositivos y equipos, 

Con uso de la memoria compartida del sistema, tambienes posible integrar diferentes servicios e lenguajes de programacion, cómo lo es el caso de python, C# y otros.

Tabien se desarrolló un apartado de Sockets, lo cualermite counicacion tanto con la misma maqina, tanto con el exterior, como lo es una red local, o inclusive hasta interner, esta caracteristica a´´un está en revision.




<!-- ## License -->
<!-- Released under [MIT](LICENSE) by [@YecidMorenoUSP](https://github.com/YecidMorenoUSP). -->


## Limitaciones
1. Velicidad con USB y EPOS

## BUGS
1. Cambiar el pwd despues de guardar o leer un archivo