start:
  ldi 0x61
  out
  sbr function
  dbg
  byte 0x00

function:
  dbg
  ldi 0x62
  out
  ret
  
