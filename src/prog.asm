start:
  lda 0x00
  
  udg
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
  BYTE 0x1f  ; 0001 1111

end:
