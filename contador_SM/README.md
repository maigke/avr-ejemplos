
# contador_SM 

### Project created with APOS (AVR Project Open Source)

### Description:
Se lee un pulso emitido por un sensor de proximidad dicho pulso se ve refleado en dos leds de salida contando del 0 al 3 y al llegar un nuevo pulso causa el desbordamiento.
El conteo se realiza por medio de una maquina de estados finitos.
 
A continuación se muestra el circuito:
 
### circuito 
 
![Circuito contador](img/circuito.svg)

El circuito sensor se construye a partir del decodificador de tonos LM567

![circuito sensor](img/Sensor.svg)

En la siguiente figura se muestra una tabla con las funciones de las terminales de dicho circuito integrado.
![lm567 pinout](img/lm567.webp)
