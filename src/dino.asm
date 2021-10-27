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
  
  
  sbr update_world
  lpc exit

update_world:
  ldi 0x00             ; load 0 to A register
  tab                  ; transfer the 0 from A to B register

print:                 ; print string loop
  lda game_world       ; load byte at 'hello' label address + B register offset
  cmp 0xfe             ; terminating character?
  jmp update_return    ; if so then exit the program
  out                  ; print character to LCD display
  inc                  ; increment B reister by 1
  dbg
  lpc print            ; jump to 'print' label

update_return:
  ret

game_world:
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x53
  byte 0x63
  byte 0x6f
  byte 0x72
  byte 0x65
  byte 0x3a
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x61
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0x20
  byte 0xfe

dino_l:
  byte 0x07             ; 00000111
  byte 0x05             ; 00000101
  byte 0x07             ; 00000111
  byte 0x16             ; 00010110
  byte 0x1f             ; 00011111
  byte 0x1e             ; 00011110
  byte 0x0e             ; 00001110
  byte 0x04             ; 00000100

dino_r:
  byte 0x07             ; 00000111
  byte 0x05             ; 00000101
  byte 0x07             ; 00000111
  byte 0x16             ; 00010110
  byte 0x1f             ; 00011111
  byte 0x1e             ; 00011110
  byte 0x0e             ; 00001110
  byte 0x02             ; 00000010

cactus_1:
  byte 0x00             ; 00000000
  byte 0x04             ; 00000100
  byte 0x05             ; 00000101
  byte 0x15             ; 00010101
  byte 0x16             ; 00010110
  byte 0x0c             ; 00001100
  byte 0x04             ; 00000100
  byte 0x04             ; 00000100

cactus_2:
  byte 0x00             ; 00000000
  byte 0x00             ; 00000000
  byte 0x04             ; 00000100
  byte 0x05             ; 00000101
  byte 0x15             ; 00010101
  byte 0x16             ; 00010110
  byte 0x0c             ; 00001100
  byte 0x04             ; 00000100

exit:
  byte 0x00
