

import serial

rele = 0
dev = serial.Serial('/dev/ttyUSB0',9600)


def showMenu():
    if rele == 0:
        print(""" *********************
        *  MENU DE OPCIONES  *
        **********************
        *  R >> ENCIENDE RELE*
        *  X >> SALIR        *
        **********************\n""")
    else:
        print(""" *********************
        *  MENU DE OPCIONES  *
        **********************
        *  R >> APAGA RELE   *
        *  X >> SALIR        *
        **********************\n""")
while True:
    showMenu()
    opcion = input('Opcion').upper()
    if opcion == 'R':
        if rele == 1:
            rele = 0
            print('Enciende rele....\n')
        else:
            rele = 1
            print('Apaga rele...\n')
        cad = str(rele)
        dev.write(cad.encode('ascii'))
    elif opcion == 'X':
        print('Saliendo .... \n')
        break
    else:
        print('Opcion no valida..\n')
