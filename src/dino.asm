start:                  ; for programs bigger than around 200 bytes
  lpc init              ; make sure to store data in the beginning of the file
                        ; and then jump to program start for otherwise
                        ; local variable addresses may exceed 0xff resulting
                        ; in undefined behavior

world_row_1:
  byte 0x20
  byte 0x20 ; dino jumps here
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
  byte 0x00 ; dino
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

init:                 ; program start
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

get_ready:
  rch
  cmp 0x30
  jmp game_loop
  lpc get_ready

game_loop:  
  rch
  cmp 0x30
  jmp dino_jump  

game_continue:
  dbg ; stucks here after jump
  sbr update_world
  lpc game_loop

dino_jump:
  ;ldi 0x00
  ;tab
  ;ldi 0x00
  ;pos
  ;ldi 0x01
  ;tab
  ;lda world_row_2
  ;sta world_row_1
  ;ldi 0x20
  ;sta world_row_2
  ;sbr update_world
  ;sbr update_world
  ;sbr update_world
  ;sbr update_world
  ;ldi 0x00
  ;tab
  ;ldi 0x00
  ;pos
  ;ldi 0x01
  ;tab
  ;lda world_row_1
  ;sta world_row_2
  ;ldi 0x20
  ;sta world_row_1
  ;ldi 0x20
  ;dcr
  ;sta world_row_2
  lpc game_loop ;game_continue

update_world:          ; print game world procedure
  dly 0xff
  sbr scroll_world
  ldi 0x00             ; load 0 to A register
  tab                  ; transfer the 0 from A to B register

print_loop:            ; print world loop
  cmp 0x3a             ; A register equals to colon char?
  jmp next_line        ; if so it's time to update cursor position

load_next_char:        ; print next char in game world array
  lda world_row_1      ; load byte at 'hello' label address + B register offset
  jmp update_dino      ; if encounter a dino_l then swap legs
  cmp 0x01             ; if encounter a dino_l
  jmp update_dino      ; then swap legs as well

load_end:
  cmp 0xfe             ; terminating character?
  jmp update_return    ; if so then exit the program
  out                  ; print character to LCD display
  inc                  ; increment B reister by 1
  lpc print_loop       ; jump to 'print' label

update_dino:
  xor 0x01             ; swap dino legs
  sta world_row_1
  lpc load_end         ; continue loop

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

  cmp 0x02
  jmp set_object
  cmp 0x04
  jmp set_object
  
  ldi 0x20
  

set_object:            ; random source set
  sta random_object    ; set object (cactus_small/cactus_big/empty square)
  ldi 0x00             ; load 0x00 A register 
  tab                  ; and transfer it to B register to init the offset
  
  
scroll_loop:           ; loop over bytes in game world row 2
  lda world_row_2      ; load address of world_row_2 to A register
  cmp 0x02
  jmp scroll_object
  cmp 0x04
  jmp scroll_object

scroll_loop_end:
  cmp 0xfe             ; end of row?
  jmp scroll_return    ; all done
  inc
  lpc scroll_loop      ; scroll next byte

scroll_object:
  psh
  dcr                  ; decrement B register, so it points to next cell to scroll cactus to
  
  psh
  lda world_row_2      ; get next cell's content
  cmp 0x00             ; is it a dino_l?
  jmp game_over        ; if so the game is over
  cmp 0x01             ; is it a dino_r
  jmp game_over        ; if so the game is over
  pop
  
  sta world_row_2      ; store big or small cactus on the next cell
  inc                  ; restore original cactus location cell offset
  inc                  ; point B register to previous cell offset
  lda world_row_2      ; source it's content
  dcr                  ; then drop back to current cell again
  sta world_row_2      ; and replace it's content byte the content of the previous cell
  pop
  
  lpc scroll_loop_end

scroll_return:         ; all done
  ret                  ; return from procedure

game_over:
  pop
  pop
  pop
  pop
  
reset_map:              ; needed to play the game again without reloading
  ldi 0x02
  tab
  ldi 0x20

reset_loop:
  psh
  lda world_row_2
  cmp 0xfe
  jmp reset_end
  pop
  sta world_row_2
  inc
  lpc reset_loop

reset_end:
  pop
  byte 0x00
