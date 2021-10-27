start:                 ; program start  
  ldi dino_l
  tab
  ldi 0x00
  udg
  
  ldi dino_r
  tab
  ldi 0x01
  udg

  ldi cactus_big
  tab
  ldi 0x02
  udg
  
  ldi cactus_small
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
  lda world_row_1 ; load byte at 'hello' label address + B register offset
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
  ldi 0x00             ; load 0x00 to A register
  tab                  ; reset B register offset
  rnd 0x20             ; generate random number in range from 0x00 to 0x20
  and 0x06             ; mask for cactus and empty square (0010 0110 => 0x26)
  jmp empty_square     ; on 0x00 (dino char) set empty square
  cmp 0x06             ; mask cactus
  jmp empty_square     ; on 0x06 (undefined char) set empty square

set_object:            ; random source set
  ldi 0x02 ; temp
  sta random_object    ; set object (cactus_small/cactus_big/empty square)
  ldi 0x00             ; load 0x00 A register 
  tab                  ; and transfer it to B register to init the offset
  
scroll_loop:           ; loop over bytes in game world row 2
  lda world_row_2      ; load address of world_row_2 to A register
  cmp 0x02
  jmp scroll_object
  cmp 0x03
  jmp scroll_object

scroll_loop_end:
  cmp 0xfe             ; end of row?
  jmp scroll_return    ; all done
  inc
  lpc scroll_loop      ; scroll next byte

empty_square:
  ldi 0x20             ; make sure it's not a dino)
  lpc set_object

scroll_object:
  psh
  ; scroll logic here...
  
  pop
  lpc scroll_loop_end

scroll_return:         ; all done
  ret                  ; return from procedure

world_row_1:
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

world_row_2:
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

random_object:
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

cactus_big:
  byte 0x00             ; 00000000
  byte 0x04             ; 00000100
  byte 0x05             ; 00000101
  byte 0x15             ; 00010101
  byte 0x16             ; 00010110
  byte 0x0c             ; 00001100
  byte 0x04             ; 00000100
  byte 0x04             ; 00000100

cactus_small:
  byte 0x00             ; 00000000
  byte 0x00             ; 00000000
  byte 0x04             ; 00000100
  byte 0x05             ; 00000101
  byte 0x15             ; 00010101
  byte 0x16             ; 00010110
  byte 0x0c             ; 00001100
  byte 0x04             ; 00000100

exit:
  crs
  ldi 0x01
  tab
  ldi 0x00
  pos
  byte 0x00
