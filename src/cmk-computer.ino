/****************************************************************\
 ================================================================

                           8-bit computer
                      
                                 by
                     
                          Code Monkey King

================================================================
\****************************************************************/

// LCD driver
#include <LiquidCrystal.h>
#include <Keypad.h>

/****************************************************************\
 ================================================================
                              CIRCUIT
 ================================================================
 
  initialize the library with the numbers of the interface pins

                    LCD RS pin to digital pin 12
                    LCD Enable pin to digital pin 11
                    LCD D4 pin to digital pin 5
                    LCD D5 pin to digital pin 4
                    LCD D6 pin to digital pin 3
                    LCD D7 pin to digital pin 2
                    LCD R/W pin to ground
                    LCD VSS pin to ground
                    LCD VCC pin to 5V
                    10K resistor:
                    ends to +5V and ground
                    wiper to LCD VO pin (pin 3)

 ================================================================
\****************************************************************/

/****************************************************************\
 ================================================================
                              OPCODES
 ================================================================
    
    ----------------------------------------------------------
          bin   hex  asm  description
    ----------------------------------------------------------
    0000 0000  0x00  NOP  no operation
    0000 0001  0x01  LDI  load immediate data to A register
    0000 0010  0x02  LDA  load data from memory to A register
    0000 0011  0x03  TAB  transfer data from A to B register
    0000 0100  0x04  ADD  add A and B, store result to A register
    0000 0101  0x05  SUB  subtract B from A, store result to A register
    0000 0110  0x06  STA  set value from A register to memory
    0000 0111  0x07  SPC  save program counter to memory
    0000 1000  0x08  LPC  load data from memory to program counter
    0000 1001  0x09  INC  increment value in memory
    0000 1010  0x0a  DEC  decrement value in memory
    0000 1011  0x0b  CMP  compare register A and B
    0000 1100  0x0c  JMP  jump if zero flag is true
    0000 1101  0x0d  STP  stop execution
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
 ================================================================
\****************************************************************/

// init LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// keypad size
const byte numRows= 4;
const byte numCols= 4;

// map keypad keys
uint8_t keymap[numRows][numCols] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { 'E', '0', 'F', 'D'}
};

// map keypad rows and columns
byte rowPins[numRows] = {10, 9, 8, 7};     // Rows 0 to 3
byte colPins[numCols] = {14, 15, 16, 17};  // Columns 0 to 3

// init kepad
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

/****************************************************************\
 ================================================================

                              GLOBALS

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
#define SPC 0x07
#define LPC 0x08
#define INC 0x09
#define DEC 0x0a
#define CMP 0x0b
#define JMP 0x0c
#define STP 0x0d
#define IN  0x0e
#define OUT 0x0f
#define BIT 0x10
#define AND 0x11
#define OR  0x12
#define XOR 0x13
#define NOT 0x14
#define SHL 0x15
#define SHR 0x16

// define RAM size
#define MEMORY_SIZE 1024

// RAM array
uint8_t  memory[MEMORY_SIZE];

// CPU registers
uint8_t  register_A = 0;
uint8_t  register_B = 0;
uint16_t  program_counter = 0;
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
  lcd.setCursor(0, 2);
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
  zero_flag = 0;
}

// print debug info
void print_registers() {
  lcd.print("I:");
  print_byte(register_A);
  lcd.print(' ');
  print_byte(register_B);
  lcd.print(' ');
  print_word(program_counter);
  lcd.print(' ');
  lcd.println(zero_flag, BIN);
  lcd.setCursor(0, 2);
}

// print instruction
void print_instruction(char *name, uint16_t value) {
  Serial.print(name);
  Serial.print(" 0x");
  Serial.println(value, HEX);
}

// execute instruction
void execute() {
  while (true) {
    // read next opcode
    uint8_t opcode = read_byte();    
    
    // execute instruction
    switch (opcode) {
      case NOP: program_counter++; break;
      case LDI: zero_flag = ((register_A = read_byte()) == 0); break;
      case LDA: zero_flag = ((register_A = memory[read_word()]) == 0); break;
      case TAB: zero_flag = ((register_B = register_A) == 0); break;
      case ADD: zero_flag = ((register_A += register_B) == 0); break;
      case SUB: zero_flag = ((register_A -= register_B) == 0); break;
      case STA: memory[read_word()] = register_A; break;
      case SPC: memory[read_word()] = program_counter; break;
      case LPC: program_counter = read_word(); break;
      case INC: zero_flag = (++memory[read_word()] == 0); break;
      case DEC: zero_flag = (--memory[read_word()] == 0); break;
      case CMP: zero_flag = ((register_A - register_B) == 0); break;
      case JMP: if (zero_flag) program_counter = read_word(); break;
      case STP: return;
      case IN: while ((register_A = myKeypad.getKey()) == NO_KEY); break;
      case OUT: lcd.print(char(register_A)); break;
      case BIT: zero_flag = ((register_A & register_B) == 0); break;
      case AND: zero_flag = ((register_A &= register_B) == 0); break;
      case OR: zero_flag = ((register_A |= register_B) == 0); break;
      case XOR: zero_flag = ((register_A ^= register_B) == 0); break;
      case NOT: zero_flag = ((register_A = ~register_A) == 0); break;
      case SHL: zero_flag = ((register_A <<= register_B) == 0); break;
      case SHR: zero_flag = ((register_A >>= register_B) == 0); break;
      default: Serial.println("Unknown opcode!"); break;
    }
  }
}


/****************************************************************\
 ================================================================

                               MAIN

 ================================================================
\****************************************************************/

// arduino setup
void setup() {
  // init serial port for debugging
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //lcd.autoscroll();
  lcd.noAutoscroll();
  lcd.blink();
  
  // init all
  reset_cpu();
  reset_memory();
  
  // put example program into memory
  uint8_t test_prog[] = {
    IN,
    ADD,
    OUT,
    LPC, 0x00, 0x00,
    STP
  };
  
  for (uint16_t i = 0; i < 100; i++) { 
    memory[i] = test_prog[i];
    if (test_prog[i] == STP) break;
  }
  
  // print greetings
  lcd.print(" 8-bit Computer");
  lcd.setCursor(0, 2);
  
}

// get user keypress
char getch() {
  char key;
  while ((key = myKeypad.getKey()) == NO_KEY);
  return key;
}

// convert ASCII character to HEX number
uint8_t ascii_to_hex(char ascii) {
  return ascii <= '9' ? (ascii - '0') : (ascii - 'A' + 10);
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
  } return addr;
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

// arduino loop
void loop() {  
  uint16_t addr = encode_word();
  lcd.print(':');
  for (int i = addr; i < addr + 4; i++) {
    memory[i] = encode_byte();
    lcd.print(' ');
    
    //Serial.print(i, HEX);
    //Serial.print(':');
    //Serial.println(memory[i], HEX);
  } memory_dump(addr);
  
  //execute();
}
 
