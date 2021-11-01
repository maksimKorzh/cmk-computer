start:
  lpc draw

mario_head_left:
  byte 0x01             ; 0000 0001
  byte 0x03             ; 0000 0011
  byte 0x03             ; 0000 0011
  byte 0x05             ; 0000 0101
  byte 0x05             ; 0000 0101
  byte 0x06             ; 0000 0110
  byte 0x00             ; 0000 0000
  byte 0x0f             ; 0000 1111

mario_head_center:
  byte 0x1c             ; 0001 1100
  byte 0x1f             ; 0001 1111
  byte 0x12             ; 0001 0010
  byte 0x02             ; 0000 0010
  byte 0x11             ; 0001 0001
  byte 0x03             ; 0000 0011
  byte 0x00             ; 0000 0000
  byte 0x16             ; 0001 0110

mario_head_right:
  
draw:
  ldi mario_head_left
  tab
  ldi 0x00
  udg
  
  ldi mario_head_center
  tab
  ldi 0x01
  udg
  
  spr 0x00
  spr 0x01
  byte 0x00










