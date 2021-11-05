;--------------------------------------------------------------------------------------------------------;
;
;                                   Chess program for CMK computer
;
;                                                  by
;
;                                           Code Monkey King
;
;--------------------------------------------------------------------------------------------------------;
;--------------------------------------------------------------------------------------------------------;
;                                            PIECE ENCODING
;--------------------------------------------------------------------------------------------------------;
;
;                                  WHITE PAWN    0x01 | 0x08 = 0x09
;                                  WHITE KING    0x03 | 0x08 = 0x0b
;                                  WHITE KNIGHT  0x04 | 0x08 = 0x0c
;                                  WHITE BISHOP  0x05 | 0x08 = 0x0d
;                                  WHITE ROOK    0x06 | 0x08 = 0x0e
;                                  WHITE QUEEN   0x07 | 0x08 = 0x0f
;
;                                  BLACK PAWN    0x02 | 0x10 = 0x12
;                                  BLACK KING    0x03 | 0x10 = 0x13
;                                  BLACK KNIGHT  0x04 | 0x10 = 0x14
;                                  BLACK BISHOP  0x05 | 0x10 = 0x15
;                                  BLACK ROOK    0x06 | 0x10 = 0x16
;                                  BLACK QUEEN   0x07 | 0x10 = 0x17
;
;--------------------------------------------------------------------------------------------------------;
;--------------------------------------------------------------------------------------------------------;
;                                     BOARD REPRESENTATION (0x88)
;--------------------------------------------------------------------------------------------------------;
;
;                                PIECES                       POSITIONAL SCORES
;                   ------------------------------     ------------------------------
;                   16  14  15  17  13  15  14  16     00  00  00  00  00  00  00  00
;                   12  12  12  12  12  12  12  12     00  00  00  00  00  00  00  00
;                   00  00  00  00  00  00  00  00     00  00  00  00  00  00  00  00
;                   00  00  00  00  00  00  00  00     00  00  00  00  00  00  00  00    
;                   00  00  00  00  00  00  00  00     00  00  00  00  00  00  00  00
;                   00  00  00  00  00  00  00  00     00  00  00  00  00  00  00  00
;                   09  09  09  09  09  09  09  09     00  00  00  00  00  00  00  00
;                   0e  0c  0d  0b  0f  0d  0c  0e     00  00  00  00  00  00  00  00
;
;--------------------------------------------------------------------------------------------------------;
%define WHITE_PAWN      0x09                        ; maps to ASCII 'P' in print_board routine
%define WHITE_KNIGHT    0x0c                        ; maps to ASCII 'N' in print_board routine
%define WHITE_BISHOP    0x0d                        ; maps to ASCII 'B' in print_board routine
%define WHITE_ROOK      0x0e                        ; maps to ASCII 'R' in print_board routine
%define WHITE_QUEEN     0x0f                        ; maps to ASCII 'Q' in print_board routine
%define WHITE_KING      0x0b                        ; maps to ASCII 'K' in print_board routine
%define BLACK_PAWN      0x12                        ; maps to ASCII 'p' in print_board routine
%define BLACK_KNIGHT    0x14                        ; maps to ASCII 'n' in print_board routine
%define BLACK_BISHOP    0x15                        ; maps to ASCII 'b' in print_board routine
%define BLACK_ROOK      0x16                        ; maps to ASCII 'r' in print_board routine
%define BLACK_QUEEN     0x17                        ; maps to ASCII 'q' in print_board routine
%define BLACK_KING      0x13                        ; maps to ASCII 'k' in print_board routine
%define EMPTY_SQUARE    0x00                        ; maps to ASCII '.' in print_board routine
;--------------------------------------------------------------------------------------------------------;
%define BOARD_START     0x02ee                      ; address of board array index 0
%define BOARD_END       0x036e                      ; address of board array index 128
%define RANK_8          0x02ee ; + 0
%define RANK_7          0x02fe ; + 10
%define RANK_6          0x030e ; + 20
%define RANK_5          0x031e ; + 30
%define RANK_4          0x032e ; + 40
%define RANK_3          0x033e ; + 50
%define RANK_2          0x034e ; + 60
%define RANK_1          0x035e ; + 70
;--------------------------------------------------------------------------------------------------------;
start:                                              ; program start
  lpc game_loop                                     ; jump to init_board
;--------------------------------------------------------------------------------------------------------;
ascii_pieces:                                       ; ".-pknbrq-P-KNBRQ"
  byte 0x2e                                         ; '.'
  byte 0x2d                                         ; '-'
  byte 0x70                                         ; 'p'
  byte 0x6b                                         ; 'k'
  byte 0x6e                                         ; 'n'
  byte 0x62                                         ; 'b'
  byte 0x72                                         ; 'r'
  byte 0x71                                         ; 'q'
  byte 0x2d                                         ; '-'
  byte 0x50                                         ; 'P'
  byte 0x2d                                         ; '-'
  byte 0x4b                                         ; 'K'
  byte 0x4e                                         ; 'N'
  byte 0x42                                         ; 'B'
  byte 0x52                                         ; 'R'
  byte 0x51                                         ; 'Q'
;--------------------------------------------------------------------------------------------------------;
file_count:
  byte 0x00

black_pieces:
  byte BLACK_ROOK
  byte BLACK_KNIGHT
  byte BLACK_BISHOP
  byte BLACK_QUEEN
  byte BLACK_KING
  byte BLACK_BISHOP
  byte BLACK_KNIGHT
  byte BLACK_ROOK
  byte 0xff

black_pawns:
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte BLACK_PAWN
  byte 0xff

white_pieces:
  byte WHITE_ROOK
  byte WHITE_KNIGHT
  byte WHITE_BISHOP
  byte WHITE_QUEEN
  byte WHITE_KING
  byte WHITE_BISHOP
  byte WHITE_KNIGHT
  byte WHITE_ROOK
  byte 0xff

white_pawns:
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte WHITE_PAWN
  byte 0xff
;--------------------------------------------------------------------------------------------------------;

game_loop:
  sbr reset_board
  sbr set_pieces
  sbr print_board
  ldi 0x0a
  ser
  dbg
  byte 0x00

reset_board:
  ldi 0x00
  tab
  ldi 0xff
  sta BOARD_END

reset_next:
  lda BOARD_START
  cmp 0xff
  jmp reset_return
  ldi EMPTY_SQUARE
  sta BOARD_START
  inc
  lpc reset_next

reset_return:
  ret
;--------------------------------------------------------------------------------------------------------;
set_pieces:
set_black_pieces:
  ldi 0x00
  tab
  
set_black_pieces_loop:
  lda black_pieces
  cmp 0xff
  jmp set_black_pawns
  sta RANK_8
  inc
  lpc set_black_pieces_loop

set_black_pawns:
  ldi 0x00
  tab

set_black_pawns_loop:
  lda black_pawns
  cmp 0xff
  jmp set_white_pawns
  sta RANK_7
  inc
  lpc set_black_pawns_loop

set_white_pawns:
  ldi 0x00
  tab

set_white_pawns_loop:
  lda white_pawns
  cmp 0xff
  jmp set_white_pieces
  sta RANK_2
  inc
  lpc set_white_pawns_loop

set_white_pieces:
  ldi 0x00
  tab

set_white_pieces_loop:
  lda white_pieces
  cmp 0xff
  jmp set_pst
  sta RANK_1
  inc
  lpc set_white_pieces_loop

set_pst:
  ldi 0x0b
  tab
  ldi 0x0f
  sta RANK_5
  inc
  sta RANK_5
  ldi 0x0b
  tab
  ldi 0x0f
  sta RANK_4
  inc
  sta RANK_4
  ldi 0x0a
  tab
  ldi 0x0b
  sta RANK_6
  inc
  inc
  inc
  sta RANK_6
  ldi 0x0a
  tab
  ldi 0x0b
  sta RANK_3
  inc
  inc
  inc
  sta RANK_3
  

set_pieces_return:
  ret
;--------------------------------------------------------------------------------------------------------;
print_board:
  ldi 0x00
  tab

print_loop:
  lda BOARD_START
  cmp 0xff ; comment
  jmp print_return
  psh
  psh
  ldi 0x00
  tab
  lda file_count
  cmp 0x08
  jmp print_space
  cmp 0x10
  jmp print_new_line
  pop
  
print_next:
  and 0x0f
  tab
  lda ascii_pieces
  ser  
  pop
  inc
  inm file_count
  lpc print_loop

print_space:
  ldi 0x20
  ser
  pop
  lpc print_next

print_new_line:
  ldi 0x00
  sta file_count
  ldi 0x0a
  ser
  pop
  lpc print_next

print_return:
  ret
;--------------------------------------------------------------------------------------------------------;
















