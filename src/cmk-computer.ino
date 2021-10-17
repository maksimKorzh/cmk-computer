/****************************************************************\
 ================================================================

                           8-bit computer
                      
                                 by
                     
                          Code Monkey King

================================================================
\****************************************************************/

// LCD driver
#include <LiquidCrystal.h>

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
     bin  hex  asm description
    ----------------------------------------------------------
    0000  0x0  NOP  no operation
    0001  0x1  LDI  load immediate data to A register
    0010  0x2  LDA  load data from memory to A register
    0011  0x3  TAB  transfer data from A to B register
    0100  0x4  ADD  add A and B, store result to A register
    0101  0x5  SUB  subtract B from A, store result to A register
    0110  0x6  STA  set value from A register to memory
    0111  0x7  SPC  save program counter to memory
    1000  0x8  LPC  load data from memory to program counter
    1001  0x9  INC  increment value in memory
    1010  0xa  DEC  decrement value in memory
    1011  0xb  JMP  unconditional jump
    1100  0xc  JZ   jump if zero flag is true
    1101  0xd  JC   jump if carry flag is true
    1110  0xe  IN   read character from keypad
    1111  0xf  OUT  output character to LCD
 ================================================================
\****************************************************************/

// init LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
#define JMP 0x0b
#define JZ  0x0c
#define JC  0x0d
#define IN  0x0e
#define OUT 0x0f

// define RAM size
#define MEMORY_SIZE 1024

// RAM array
uint8_t  memory[MEMORY_SIZE];


// CPU registers
uint8_t  register_A = 0;
uint8_t  register_B = 0;
uint8_t  program_counter = 0;
bool zero_flag = 0;
bool carry_flag = 0;

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
  
  Serial.println(value, HEX);
  
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
  carry_flag = 0;
}

// print debug info
void print_registers() {
  Serial.print("Register A: ");
  Serial.println(register_A, HEX);
  Serial.print("Register B: ");
  Serial.println(register_B, HEX);
  Serial.print("Program counter: ");
  Serial.println(program_counter, HEX);
  Serial.print("Zero flag: ");
  Serial.println(zero_flag, BIN);
  Serial.print("Carry flag: ");
  Serial.println(carry_flag, BIN);
  Serial.println();
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
      case NOP:
        program_counter = 0;
        Serial.println("All done");
        return;
      
      case LDI:
        register_A = read_byte();
        zero_flag = (register_A == 0);
        break;
      
      case LDA:
        register_A = memory[read_word()];
        zero_flag = (register_A == 0);
        break;
      
      case TAB: break;
      case ADD: break;
      case SUB: break;
      
      case STA:
        memory[read_word()] = register_A;
        break;
      
      
      case SPC: break;
      case LPC: break;
      case INC: break;
      case DEC: break;
      case JMP: break;
      case JZ: break;
      case JC: break;
      case IN: break;
      case OUT: break;
      default: Serial.println("Unknown opcode!"); break;
    }
    
    print_registers();
  }
}


/****************************************************************\
 ================================================================

                               MAIN

 ================================================================
\****************************************************************/

void setup() {
  // init serial port for debugging
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.blink();

  // Print a message to the LCD.
  //lcd.print("hello, world!");
  
  // init all
  reset_cpu();
  reset_memory();
  
  // put example program into memory
  uint8_t test_prog[] = {
    LDI, 0x32,            // load 0x45 to A register
    STA, 0x01, 0x00,
    LDI, 0x45,
    STA, 0x01, 0x01,
    LDI, 0x00,
    STA, 0x01, 0x02,  
    LDA, 0x01, 0x00,
    LDA, 0x01, 0x01,
    LDA, 0x01, 0x02,
    0xFF
  };
  
  for (uint16_t i = 0; i < 100; i++) { 
    if (test_prog[i] == 0xFF) break;
    memory[i] = test_prog[i];
  }
  
  
  execute();
  memory_dump(0x0100);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
  
 
  
  
}
 
