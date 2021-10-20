start:
  LDI 0x42
  TAB
  LDI 0x30

loop:
  OUT
  INC
  DBG
  CMP
  JMP clear
  LPC loop

clear:
  CLS
  DBG
  LPC loop
