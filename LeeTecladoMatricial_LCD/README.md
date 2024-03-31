
# Practica4 

### Project created with APOS (AVR Project Open Source)

To edit the project settings, open the Makefile and edit the first lines of the file.
## Descripción
Este código presenta la programación de la lectura de un teclado matricial, por medio de escaneo de filas y columnas, a fin de mostrar el valor capturado en una pantalla LCD alfanumérica de 2 líneas por 16 columnas.


## Seccion del Makefile

En este apartado se muestran algunas consideraciones para el makefile

1. En este punto se muestra la pequeña configuración para agregar el usbasp como programador.
'''
AVRDUDE_PROG  = -c usbasp -P usb
ABOS_PORT     = /dev/ttyUSB0
'''

2. En esta sección se muestra como debe incluirse los códigos objetos que se generan cuando se compila el Makefile y éstos puedan ser ligados al código de main. 

'''
OBJECT_FILES = main.o
OBJECT_FILES += ./src/lcd.o
OBJECT_FILES += ./src/clk.o
'''
