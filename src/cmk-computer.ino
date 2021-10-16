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
byte memory[MEMORY_SIZE];


// CPU registers
byte register_A = 0;
byte register_B = 0;
byte program_counter = 0;
bool zero_flag = 0;
bool carry_flag = 0;

/****************************************************************\
 ================================================================

                              MEMORY

 ================================================================
\****************************************************************/

// clear RAM
void reset_memory() {
  for (int i = 0; i < MEMORY_SIZE; i++)
    memory[i] = 0;
}

// read byte from memory
byte read_memory() {
  byte value = memory[program_counter];
  program_counter++;
  return value;
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

// execute instruction
void execute() {
  byte opcode = read_memory();
  
  Serial.println(opcode, HEX);
  
  switch (opcode) {
    case NOP: program_counter = 0; break;
    case LDI: break;
    case LDA: break;
    case TAB: break;
    case ADD: break;
    case SUB: break;
    case STA: break;
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
}


/****************************************************************\
 ================================================================

                               MAIN

 ================================================================
\****************************************************************/

void setup() {
  // init serial port for debugging
  Serial.begin(9600);
  
  // reset CPU
  reset_cpu();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  //lcd.print("hello, world!");
  
  // put example program into memory
  memory[0] = LDI; memory[1] = 0x45;      // LDI $45
  execute();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
 
  
  
}
 
