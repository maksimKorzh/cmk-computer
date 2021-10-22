start:
  ldi 0x00
  tab

print:
  lda hello
  dbg
  cmp 0x00
  jmp exit
  dly
  out
  inc
  lpc print

hello:
  byte 0x48    ; 'H'
  byte 0x65    ; 'e'
  byte 0x6c    ; 'l'
  byte 0x6c    ; 'l'
  byte 0x6f    ; 'o'
  byte 0x2c    ; ','
  byte 0x20    ; ' '
  byte 0x77    ; 'w'
  byte 0x6f    ; 'o'
  byte 0x72    ; 'r'
  byte 0x6c    ; 'l'
  byte 0x64    ; 'd'
  byte 0x21    ; '!'
  
hello_end:
  byte 0x00    ; zero terminating character

exit:
  byte 0x00    ; execution stops here
  ldi 0x61
  out
  
  
