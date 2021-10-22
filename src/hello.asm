start:
  ldi 0x00

print:
  lda count
  ;lda hello    ; load char at address 'hello + register B' to A register
  
  
  ;cmp
  ;jmp end
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
  byte 0x00    ; zero terminating character

count:
  byte hello

end:
  byte 0x00    ; execution stops here
