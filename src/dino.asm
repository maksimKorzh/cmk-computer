start:                 ; program start  
  ldi dino_l
  tab
  ldi 0x00
  udg
  
  ldi dino_r
  tab
  ldi 0x01
  udg

  ldi cactus_1
  tab
  ldi 0x02
  udg
  
  ldi cactus_2
  tab
  ldi 0x03
  udg
  
  ldi cloud
  tab
  ldi 0x04
  udg
  
  ldi pterodactyl_up
  tab
  ldi 0x05
  udg
  
  ldi empty
  tab
  ldi 0x06
  udg

reset:
  ldi 0x01
  tab
  ldi 0x00
  pos
  spr 0x06
  ldi 0x10
  pos
  psh

run:
  dly 0xff
  pop
  spr 0x02
  sub 0x01
  spr 0x06
  
  pos
  psh
  cmp 0xfe
  jmp reset
  lpc run

  

dino_l:
  byte 0x07    ; 00000111
  byte 0x05    ; 00000101
  byte 0x07    ; 00000111
  byte 0x16    ; 00010110
  byte 0x1f    ; 00011111
  byte 0x1e    ; 00011110
  byte 0x0e    ; 00001110
  byte 0x04    ; 00000100

dino_r:
  byte 0x07    ; 00000111
  byte 0x05    ; 00000101
  byte 0x07    ; 00000111
  byte 0x16    ; 00010110
  byte 0x1f    ; 00011111
  byte 0x1e    ; 00011110
  byte 0x0e    ; 00001110
  byte 0x02    ; 00000010

cactus_1:
  byte 0x00    ; 00000000
  byte 0x04    ; 00000100
  byte 0x05    ; 00000101
  byte 0x15    ; 00010101
  byte 0x16    ; 00010110
  byte 0x0c    ; 00001100
  byte 0x04    ; 00000100
  byte 0x04    ; 00000100

cactus_2:
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x04    ; 00000100
  byte 0x05    ; 00000101
  byte 0x15    ; 00010101
  byte 0x16    ; 00010110
  byte 0x0c    ; 00001100
  byte 0x04    ; 00000100

cloud:
  byte 0x00    ; 00000000
  byte 0x0e    ; 00001110
  byte 0x11    ; 00010001
  byte 0x0e    ; 00001110
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000

pterodactyl_up:
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x04    ; 00000100
  byte 0x0c    ; 00001100
  byte 0x1f    ; 00011111
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000

empty:
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000
  byte 0x00    ; 00000000

exit:
  byte 0x00
