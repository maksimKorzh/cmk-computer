start:
  ldi 0x01
  tab
  lda label
  
  dbg

label:
  byte 0x48
  byte 0x56

