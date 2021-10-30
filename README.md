# CMK computer
CMK computer is a bundle of arduino nano/uno, 16x2 LCD shield and 4x4 keypad<br>
8-bit CPU emulator and a hex editor are flashed into ATMega328 microcontroller<br>
Programs can be entered via machine codes from the keypad or loaded via serial port<br>

# Operation codes / Assembly mnemonics
    ----------------------------------------------------------
     hex  asm  arg   description
    ----------------------------------------------------------
    0x00  NOP        no operation, resets program counter
    0x01  LDI  byte  load immediate data to A register
    0x02  LDA  word  load data from memory to A register with register B offset
    0x03  TAB        transfer data from A to B register
    0x04  ADD  byte  add immediate data to A register and store it
    0x05  SUB  byte  subtract immediate data from A register and store it
    0x06  STA  word  set value from A register to memory
    0x07  RCH        read character from keypad
    0x08  LPC  word  load data from memory to program counter
    0x09  INC        increment value in register B
    0x0a  DCR        decrement value in register B
    0x0b  CMP  byte  compare register A and immediate value
    0x0c  JMP  word  jump program counter to memory address if zero flag is true
    0x0d  DBG        print debug info to serial port
    ----------------------------------------------------------
    0x0e  IN         get user input from keypad to A register
    0x0f  OUT        output character from A register to LCD
    ----------------------------------------------------------
    0x10  BIT  byte  A bitwise AND immediate data, set zero flag
    0x11  AND  byte  A bitwise AND immediate data, store result to A register
    0x12  OR   byte  A bitwise OR immediate data, store result to A register
    0x13  XOR  byte  A bitwise XOR immediate data, store result to A register
    0x14  NOT  byte  bitwise NOT immediate data, store result to A register
    0x15  SHL  byte  A bitwise shift left by immediate data
    0x16  SHR  byte  A bitwise shift right by immediate data
    ----------------------------------------------------------
    0x17  CLS        clear LCD display
    0x18  SDL        Scrolls the contents of the display one space to the left
    0x19  SDR        Scrolls the contents of the display one space to the right
    0x1a  CRS        enable cursor (blink)
    0x1b  NCR        disable cursor (no blink)
    0x1c  UDG        user defined character (A equals id, B points to bytes)
    0x1d  SPR  byte  draw sprite (A equals to user defined character)
    0x1e  POS        set cursor at position (A = column, B = row)
    ----------------------------------------------------------
    0x1f  DLY  byte  delay execution
    0x20  RND  byte  load random number between 0 and immediate date into A register
    ----------------------------------------------------------
    0x21  PSH        push register A, then register B to stack
    0x22  POP        pop register B, then register A from stack
    0x23  SBR  word  call subroutine at memory address
    0x24  RET        return from subroutine
    ----------------------------------------------------------
    0x25  NUM  word  print decimal number at memory address
    0x26  INM  word  increment value at memory address
    0x27  DCM  word  decrement value at memory address

# Hello world example program
    start:         ; program start
      ldi 0x00     ; load 0 to A register
      tab          ; transfer the 0 from A to B register

    print:         ; print string loop
      lda hello    ; load byte at 'hello' label address + B register offset
      cmp 0x00     ; zero terminating character?
      jmp exit     ; if so then exit the program
      dly 0xff     ; wait for 255 ms
      out          ; print character to LCD display
      inc          ; increment B reister by 1
      lpc print    ; jump to 'print' label

    hello:         ; 'Hello, world!' string
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
      
    hello_end:     ; prorgam end
      byte 0x00    ; zero terminating character

    exit:          ; clean ups before exit
      ldi 0x02     ; load 2 to A register
      tab          ; transfer to from A to B register
      ldi 0x00     ; load 0 to A register
      pos          ; position cursor at A, B (col 0, row 2)
      byte 0x00    ; execution terminates here

# How to assemble
    python3 assembler.py hello.asm

# Try it online
https://www.tinkercad.com/things/9SkBg4xUM7Y

# Connect LCD shield
![LCD connect](https://raw.githubusercontent.com/maksimKorzh/cmk-computer/main/LCD_connect.png?token=AIFH42ONBYZL4KWSQ5HZGL3BPQDE4)

# 4x4 Keypad connect
![Keypad_connect](https://raw.githubusercontent.com/maksimKorzh/cmk-computer/main/Keypad_connect.png?token=AIFH42PHZAH27XM37VCJ2NDBPQDDO)

