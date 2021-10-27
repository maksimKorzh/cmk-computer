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
  ldi 0x04
  udg

  sbr scroll_world
  sbr update_world
  lpc exit

update_world:          ; print game world procedure
  ldi 0x00             ; load 0 to A register
  tab                  ; transfer the 0 from A to B register

print_loop:            ; print world loop
  cmp 0x3a             ; A register equals to colon char?
  jmp next_line        ; if so it's time to update cursor position

load_next_char:        ; print next char in game world array
  lda game_world       ; load byte at 'hello' label address + B register offset
  cmp 0xfe             ; terminating character?
  jmp update_return    ; if so then exit the program
  out                  ; print character to LCD display
  inc                  ; increment B reister by 1
  lpc print_loop       ; jump to 'print' label

next_line:             ; handle LCD cursor placement
  psh                  ; preserve A and B registers on stack
  ldi 0x01             ; load 0x01 to A register
  tab                  ; transfer 0x01 to B register (cursor row)
  ldi 0x00             ; load 0x00 to A register (cursor column)
  pos                  ; set cursor to line row = 1, col = 0
  pop                  ; restore A and B registers
  inc                  ; skip
  inc                  ; three
  inc                  ; bytes
  lpc load_next_char   ; print the rest of the game world

update_return:         ; all done
  ret                  ; return from procedure

scroll_world:          ; infinite scroll game world
  
  
  ldi 0x00
  tab
  rnd 0x20             ; generate random number in range from 0x00 to 0x20
  and 0x06             ; mask for cactus and empty square (0010 0110 => 0x26)
  jmp empty_square
  cmp 0x06
  jmp empty_square

set_object:
  sta random_object

scroll_return:         ; all done
  ret                  ; return from procedure

empty_square:
  ldi 0x20             ; make sure it's not a dino)
  lpc set_object


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
  byte 0x00
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

random_object:  
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
