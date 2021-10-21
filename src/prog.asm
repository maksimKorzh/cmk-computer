start:
  ldi sprite_0
  tab
  ldi 0x00
  udg
  ldi 0x02
  tab
  ldi 0x03
  pos
  ldi 0x00
  spr
  crs

loop:
  lpc end

sprite_0:
  BYTE 0x1f  ; 0001 1111
  BYTE 0x11  ; 0001 0001
  BYTE 0x11  ; 0001 0001
  BYTE 0x11  ; 0001 0001
  BYTE 0x11  ; 0001 0001
  BYTE 0x11  ; 0001 0001
  BYTE 0x11  ; 0001 0001
  BYTE 0x1f  ; 0001 1111

end:
  dbg
