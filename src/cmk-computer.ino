/****************************************************************\
 ================================================================

                           8-bit computer
                      
                                 by
                     
                          Code Monkey King

================================================================
\****************************************************************/

// libraries
#include <LiquidCrystal.h>
#include <Keypad.h>

/****************************************************************\
   ================================================================
                      CIRCUIT (Tinkercad version)
   ================================================================
                LCD RS pin to arduino digital pin 12
                LCD Enable pin to arduino digital pin 11
                LCD D4 pin to arduino digital pin 5
                LCD D5 pin to arduino digital pin 4
                LCD D6 pin to arduino digital pin 3
                LCD D7 pin to arduino digital pin 2
                LCD R/W pin to arduino ground
                LCD VSS pin to arduino ground
                LCD VCC pin to arduino 5V
                PUSH BUTTON terminal 1a to arduino pin 7
                PUSH BUTTON terminal 2a to ground
    
   ================================================================
            CIRCUIT (LCD shield 1602A D1 ROBOT (DF ROBOT))
   ================================================================
                LCD RS pin to arduino digital pin 8
                LCD Enable pin to arduino digital pin 9
                LCD Backlight LED to arduino pin 10
                LCD D4 pin to arduino digital pin 4
                LCD D5 pin to arduino digital pin 5
                LCD D6 pin to arduino digital pin 6
                LCD D7 pin to arduino digital pin 7
                LCD A0  to arduino A0 pin (LCD shield keypad) 
                LCD VIN to arduino VIN pin
                LCD GND to arduino GND pin
                LCD 5V to arduino 5V pin
                LCD RST to arduino RST pin
                KEYPAD row 1 to arduino digital pin 12
                KEYPAD row 2 to arduino digital pin 11
                KEYPAD row 3 to arduino digital pin 3
                KEYPAD row 4 to arduino digital pin 2
                KEYPAD col 1 to arduino analog pin 4
                KEYPAD col 2 to arduino analog pin 3
                KEYPAD col 3 to arduino analog pin 2
                KEYPAD col 4 to arduino analog pin 1
                
   ================================================================
  \****************************************************************/

// uncomment to rotate keypad CCW, enable LCD shield buttons
#define CMK_HARDWARE

// LCD pins
#define RS 8    // LCD reset pin
#define En 9    // LCD enable pin
#define D4 4    // LCD data pin 4
#define D5 5    // LCD data pin 5
#define D6 6    // LCD data pin 6
#define D7 7    // LCD data pin 7

// init LCD
LiquidCrystal lcd(RS, En, D4, D5, D6, D7);

// keypad size
const byte num_rows= 4;
const byte num_cols= 4;

#ifdef CMK_HARDWARE
// map keypad keys
uint8_t keymap[num_rows][num_cols] = {
  {'A', 'B', 'C', 'D'},
  {'3', '6', '9', 'F'},
  {'2', '5', '8', '0'},
  {'1', '4', '7', 'E'}
};
#else
// map keypad keys
uint8_t keymap[num_rows][num_cols] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { 'E', '0', 'F', 'D'}
};
#endif

// map keypad rows and columns
byte row_pins[num_rows] = {12, 11, 3, 2};     // Rows 0 to 3
byte col_pins[num_cols] = {A4, A3, A2, A1};  // Columns 0 to 3


// init kepad
Keypad keypad = Keypad(makeKeymap(keymap), row_pins, col_pins, num_rows, num_cols);


/****************************************************************\
 ================================================================
                              OPCODES
 ================================================================
    
    ----------------------------------------------------------
          bin   hex  asm  description
    ----------------------------------------------------------
    0000 0000  0x00  NOP  no operation
    0000 0001  0x01  LDI  load immediate data to A register
    0000 0010  0x02  LDA  load data from memory to A register with register B offset
    0000 0011  0x03  TAB  transfer data from A to B register
    0000 0100  0x04  ADD  add A and B, store result to A register
    0000 0101  0x05  SUB  subtract B from A, store result to A register
    0000 0110  0x06  STA  set value from A register to memory
    0000 0111  0x07  RCH  read character from keypad
    0000 1000  0x08  LPC  load data from memory to program counter
    0000 1001  0x09  INC  increment value in register B
    0000 1010  0x0a  DCR  decrement value in register B
    0000 1011  0x0b  CMP  compare register A and immediate value
    0000 1100  0x0c  JMP  jump if zero flag is true
    0000 1101  0x0d  DBG  print debug info to serial port
    ----------------------------------------------------------
    0000 1110  0x0e  IN   read character from keypad
    0000 1111  0x0f  OUT  output character to LCD
    ----------------------------------------------------------
    0001 0000  0x10  BIT  A & B, set zero flag
    0001 0001  0x11  AND  A & B, store result to A register
    0001 0010  0x12  OR   A | B, store result to A register
    0001 0011  0x13  XOR  A ^ B, store result to A register
    0001 0100  0x14  NOT  invert bits in A register
    0001 0101  0x15  SHL  shift all bits one position left in A register
    0001 0110  0x16  SHR  shift all bits one position right in A register
    ----------------------------------------------------------
    0001 0111  0x17  CLS  clear LCD display
    0001 1000  0x18  SDL  Scrolls the contents of the display one space to the left
    0001 1001  0x19  SDR  Scrolls the contents of the display one space to the right
    0001 1010  0x1a  CRS  enable cursor
    0001 1011  0x1b  NCR  disable cursor
    0001 1100  0x1c  UDG  user defined character
    0001 1101  0x1d  SPR  draw sprite (user defined character)
    0001 1110  0x1e  POS  set cursor at position (register A = column, register B = row)
    ----------------------------------------------------------
    0001 1111  0x1f  DLY  delay execution
    0002 0000  0x20  RND  load random number between 0 and 0xff into A register
    ----------------------------------------------------------
    0002 0001  0x21  PSH  push register A, then register B to stack
    0002 0002  0x22  POP  pop register B, then register A from stack
    0002 0003  0x23  SBR  call subroutine
    0002 0004  0x24  RET  return from subroutine
    
 ================================================================
\****************************************************************/

// define opcodes
#define NOP 0x00
#define LDI 0x01
#define LDA 0x02
#define TAB 0x03
#define ADD 0x04
#define SUB 0x05
#define STA 0x06
#define RCH 0x07
#define LPC 0x08
#define INC 0x09
#define DCR 0x0a
#define CMP 0x0b
#define JMP 0x0c
#define DBG 0x0d
#define IN  0x0e
#define OUT 0x0f
#define BIT 0x10
#define AND 0x11
#define OR  0x12
#define XOR 0x13
#define NOT 0x14
#define SHL 0x15
#define SHR 0x16
#define CLS 0x17
#define SDL 0x18
#define SDR 0x19
#define CRS 0x1a
#define NCR 0x1b
#define UDG 0x1c
#define SPR 0x1d
#define POS 0x1e
#define DLY 0x1f
#define RND 0x20
#define PSH 0x21
#define POP 0x22
#define SBR 0x23
#define RET 0x24

// define commands
#define CLEAR 0xfffa
#define NEW   0xfffb
#define VIEW  0xfffc
#define LOAD  0xfffd
#define SAVE  0xfffe
#define RUN   0xffff

// define RAM size
#define MEMORY_SIZE 1024

// RAM array
uint8_t  memory[MEMORY_SIZE];

// CPU registers
uint8_t  register_A = 0;
uint8_t  register_B = 0;
uint16_t  program_counter = 0;
uint16_t stack_pointer = 0x3ff;
bool zero_flag = 0;


/****************************************************************\
 ================================================================

                              MEMORY

 ================================================================
\****************************************************************/

// clear RAM
void reset_memory() {
  for (uint16_t i = 0; i < MEMORY_SIZE; i++)
    memory[i] = 0;
}

// read byte from memory
uint8_t read_byte() {
  uint8_t value = memory[program_counter];
  program_counter++;
  return value;
}

// read word from memory
uint16_t read_word() {
  uint8_t MSB = read_byte();
  uint8_t LSB = read_byte();
  uint16_t value = MSB;
  value <<= 8;
  value |= LSB;
  return value;
}

// encode address
uint16_t encode_word() {
  uint16_t addr = 0;
  for (int i = 12; i >= 0; i -= 4) {  
    char input = getch();
    uint8_t hex = ascii_to_hex(input);
    if (i) addr |= hex << i;
    else addr |= hex;
    lcd.print(hex, HEX);
    
  }
  delay(200);
  return addr;
}

// encode byte
uint8_t encode_byte() {
  uint8_t value = 0;
  for (int i = 4; i >= 0; i -= 4) {  
    char input = getch();
    uint8_t hex = ascii_to_hex(input);
    if (i) value |= hex << i;
    else value |= hex;
    lcd.print(hex, HEX);
  } return value;
}

// prints 8-bit data in hex with leading zeroes
void print_byte(uint8_t  byte) {
  if (byte<0x10) lcd.print("0");
  lcd.print(byte, HEX);
  lcd.print(' ');
}

// prints 16-bit data in hex with leading zeroes
void print_word(uint16_t  word) {
  uint8_t  MSB = byte(word >> 8);
  uint8_t  LSB = byte(word);
  if (MSB<0x10) { lcd.print("0"); } lcd.print(MSB,HEX);
  if (LSB<0x10) { lcd.print("0"); } lcd.print(LSB,HEX);
}

// dump memory
void memory_dump(uint16_t addr) {
  lcd.clear();
  print_word(addr); lcd.print(':');
  for (uint16_t i = addr; i < addr + 4; i++) print_byte(memory[i]);
  lcd.setCursor(0, 1);
}

// prints 8-bit data in hex with leading zeroes
void print_hex(uint8_t data)
{  
  if (data < 0x10) Serial.print("0"); 
  Serial.print(data, HEX);
}


/****************************************************************\
 ================================================================

                               CPU

 ================================================================
\****************************************************************/

// clear CPU registers
void reset_cpu() {
  register_A = 0;
  register_B = 0;
  program_counter = 0;
  stack_pointer = 0x3ff;
  zero_flag = 0;
}

// execute instruction
void execute() {
  while (true) {
    // read next opcode
    uint8_t opcode = read_byte();    
    
    // execute instruction
    switch (opcode) {
      case NOP: program_counter = 0; return;
      case LDI: zero_flag = ((register_A = read_byte()) == 0); break;
      case LDA: zero_flag = ((register_A = memory[(read_word() + register_B)]) == 0); break;
      case TAB: zero_flag = ((register_B = register_A) == 0); break;
      case ADD: zero_flag = ((register_A += read_byte()) == 0); break;
      case SUB: zero_flag = ((register_A -= read_byte()) == 0); break;
      case STA: memory[read_word() + register_B] = register_A; break;
      case LPC: program_counter = read_word(); break;
      case INC: zero_flag = (++register_B == 0); break;
      case DCR: zero_flag = (--register_B == 0); break;
      case CMP: zero_flag = ((register_A - read_byte()) == 0); break;
      case JMP: if (zero_flag) program_counter = read_word(); else read_word(); break;
      case RCH: zero_flag = (register_A = keypad.getKey()) == 0; break;
      case IN: while ((register_A = keypad.getKey()) == NO_KEY); break;
      case OUT: lcd.print(char(register_A)); break;
      case BIT: zero_flag = ((register_A & read_byte()) == 0); break;
      case AND: zero_flag = ((register_A &= read_byte()) == 0); break;
      case OR: zero_flag = ((register_A |= read_byte()) == 0); break;
      case XOR: zero_flag = ((register_A ^= read_byte()) == 0); break;
      case NOT: zero_flag = ((register_A = ~read_byte()) == 0); break;
      case SHL: zero_flag = ((register_A <<= read_byte()) == 0); break;
      case SHR: zero_flag = ((register_A >>= read_byte()) == 0); break;
      case CLS: lcd.clear(); break;
      case SDL: lcd.scrollDisplayLeft(); break;
      case SDR: lcd.scrollDisplayRight(); break;
      case CRS: lcd.blink(); break;
      case NCR: lcd.noBlink(); break;
      case POS: lcd.setCursor(register_A, register_B); break;
      case DLY: delay(read_byte()); break;
      case RND: zero_flag = (register_A = random(read_byte())); break;
      case PSH:
        memory[stack_pointer--] = register_A;
        memory[stack_pointer--] = register_B;
        break;
      case POP:
        register_B = memory[++stack_pointer];
        register_A = memory[++stack_pointer];
        break;
      case SBR:
        memory[stack_pointer--] = (uint8_t)(program_counter & 0x00ff) + 2;
        memory[stack_pointer--] = (uint8_t)(program_counter >> 4);
        program_counter = read_word();
        break;
      case RET:
        program_counter = 0;
        program_counter <<= memory[++stack_pointer];
        program_counter |= memory[++stack_pointer];
        break;
      case UDG:
        lcd.createChar(register_A, memory + register_B);
        lcd.begin(16, 2);
        break;
      case SPR: lcd.write(byte(read_byte())); break;
      case DBG:
        Serial.print("Register A: ");
        Serial.println(register_A, HEX);
        Serial.print("Register B: ");
        Serial.println(register_B, HEX);
        Serial.print("Program Counter: ");
        Serial.println(program_counter, HEX);
        Serial.print("Stack pointer:");
        Serial.println(stack_pointer, HEX);
        Serial.print("Zero Flag: ");
        Serial.println(zero_flag, HEX);
        break;
      default:
        lcd.clear();
        lcd.print("Unknown opcode:");
        lcd.setCursor(0, 1);
        print_byte(opcode);
        lcd.print("? ");
        return;
    }
  }
}


/****************************************************************\
 ================================================================

                               MAIN

 ================================================================
\****************************************************************/

// get user keypress
char getch() {
  char key;
  while ((key = keypad.getKey()) == NO_KEY) {
    // use LCD Shield buttons as commands shortcuts
    #ifdef CMK_HARDWARE
      int shield_input;
      shield_input = analogRead (0);
      if (shield_input < 60) { delay(300); command_save(); }          // button right
      else if (shield_input < 200) { delay(300); command_view(); }   // button up
      else if (shield_input < 400) { delay(300); command_clear(); }   // button down
      else if (shield_input < 600) { delay(300); command_load(); }    // button left
      else if (shield_input < 800) { delay(300); command_run(); }    // button select
    #endif
  }

  return key;
}

// convert ASCII character to HEX number
uint8_t ascii_to_hex(char ascii) {
  return ascii <= '9' ? (ascii - '0') : (ascii - 'A' + 10);
}

// reset computer
void init_computer() {
  lcd.clear();
  lcd.print("Code Monkey King");
  lcd.setCursor(0, 1);
  reset_cpu();
  reset_memory();
}

// run program
void command_run() {
  lcd.clear();
  lcd.print("RUN  ");
  lcd.setCursor(3, 2);
  delay(300);
  lcd.clear();
  execute();
}

// view memory dump
void command_view() {
  lcd.clear();
  lcd.print("VIEW: ");
  memory_dump(encode_word());
}

// load program
void command_load() {
  lcd.clear();
  lcd.print("LOAD ");
  delay(300);
  lcd.clear();
  lcd.print(" Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("incoming data...");
  while (Serial.available() == 0);
  lcd.clear();
  lcd.print("Loading...");
  Serial.readBytes(memory, MEMORY_SIZE);
  
  // ascii to bytes       
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i] = ascii_to_hex(memory[i]);
    if ((i % 2) == 0) memory[i] <<= 4;
    else {
      memory[i - 1] |= memory[i];
      memory[i] = 0;
    }
  }
  
  // group bytes
  for (int i = 0; i < MEMORY_SIZE; i++) {
    if ((i % 2) == 0) {
      if (i) {
        memory[i - ((int)(i / 2))] = memory[i];
        memory[i] = 0;
      }
    }
  }

  // verify transfered bytes
  //Serial.println("Your program bytes loaded:");
  //for (int i = 0; i < MEMORY_SIZE; i++) print_hex(memory[i]);

  lcd.print("  done");
  lcd.setCursor(0, 1);
}

// save program
void command_save() {
  lcd.clear();
  lcd.print("SAVE ");
  delay(300);
  lcd.clear();
  lcd.print("Saving...");
  
  for (int i = 0; i < MEMORY_SIZE; i++) {
    if ( memory[i] < 0x10) Serial.print("0");
    Serial.print(memory[i], HEX);
  }
  
  lcd.print("   done");
  lcd.setCursor(0, 1);
}

// clear screen
void command_clear() {
  lcd.clear();
  lcd.print("CLEAR");
  delay(300);
  lcd.clear();
}

// software reset
void command_new() {
  lcd.clear();
  lcd.print("NEW  ");
  lcd.setCursor(3, 2);
  delay(300);
  init_computer();
}

// arduino setup
void setup() {
  // init serial port for debugging
  Serial.begin(9600);
  
  // init LCD
  lcd.begin(16, 2);
  lcd.noAutoscroll();
  lcd.blink();
  
  // reset computer  
  init_computer();
}

void shift_value(int i) {
  int count = 2;
  while (true) {
    if (memory[i - count] != 0) { memory[i - count + 1] = memory[i - 1]; break; }
    else count++;
  }
}

// arduino loop
void loop() {  
  while (true) {
    // get user command/address
    uint16_t addr = encode_word();
    lcd.print(':');

    // handle user commands
    switch (addr) {
      case CLEAR: command_clear(); break;      // clear LCD
      case NEW: command_new(); break;          // software reset
      case VIEW: command_view(); break;        // view memory dump
      case LOAD: command_load(); break;        // load program via serial port
      case SAVE: command_save(); break;        // save program via serial port
      case RUN: command_run(); break;
      
      // enter bytes to memory
      default:
        for (int i = addr; i < addr + 4; i++) {
          memory[i] = encode_byte();
          lcd.print(' ');
        }
        
        memory_dump(addr);
        break;
    }    
  }
}
 
