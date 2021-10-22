start:
  ldi 0x00
  tab

print:
  lda hello
  cmp 0x00
  jmp exit
  dly 0xff
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
  ldi 0x02
  tab
  ldi 0x00
  pos
  byte 0x00
  
  