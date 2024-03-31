#ifndef KEYB_H
#define KEYB_H

/* Copia y pega esta variable como global en el main

 char keyMap[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
  
  */

uint8_t Leeteclado(void);
char KeyMap(uint8_t valor);
void xdelay_ms(int valor);
#endif
