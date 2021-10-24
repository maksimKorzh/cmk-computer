start:         ; program start
  
  ldi 0x12
  tab
  ldi 0x67
  psh
  dbg
  
  ldi 0x00
  tab
  ldi 0x00
  dbg
  
  pop
  dbg
  lpc exit
  
  ldi dino_a
  tab
  ldi 0x00
  udg
  
  ldi dino_b
  tab
  ldi 0x01
  udg

run:  
  ldi 0x01
  tab
  ldi 0x01
  pos
  spr 0x00
  ldi 0x01
  tab
  ldi 0x01
  pos
  spr 0x01
  lpc run

dino_a:
  byte 0x07    ; 00000111
  byte 0x05    ; 00000101
  byte 0x07    ; 00000111
  byte 0x16    ; 00010110
  byte 0x1f    ; 00011111
  byte 0x1e    ; 00011110
  byte 0x0e    ; 00001110
  byte 0x04    ; 00000100

dino_b:
  byte 0x07    ; 00000111
  byte 0x05    ; 00000101
  byte 0x07    ; 00000111
  byte 0x16    ; 00010110
  byte 0x1f    ; 00011111
  byte 0x1e    ; 00011110
  byte 0x0e    ; 00001110
  byte 0x02    ; 00000100


exit:
  byte 0x00
