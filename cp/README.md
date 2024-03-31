
# Nombre del programa: cp 

# Cálculo de las RPM de un motor

## Características
 *   muescas = 8;
 *   Eventos por vuelta = 16  ---> vuelta
 *   Tiempo de muestreo 50ms  ---> Ts = 10
 *   Cuenta de muescas        ---> n
 
 Para calcular la velocidad en RPM se realizan las siguientes operaciones
 
 **Velocidad**
 $$v = \frac{n}{T_s}$$
 

 
La velocidad en terminos de Hertz, se determina como

- v = velocidad/ Eventos por vuelta
- v = v/16  (Hz)

Para convertir esta cantidad a RPM se debe multiplicar por 60 segundos

- v_RPM = 60v;

Por lo tanto la expresion puede quedar como

$$v_{RPM} = \frac{60\cdot n \cdot T_s}{vuelta}$$



