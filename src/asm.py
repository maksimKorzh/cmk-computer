###############################################
#
#           8-bit computer assembler
#
#                      by
#
#               Code Monkey King
#
###############################################

# packages
import sys

# define opcodes
opcodes = {
    'NOP': 0x00,
    'LDI': 0x01,
    'LDA': 0x02,
    'TAB': 0x03,
    'ADD': 0x04,
    'SUB': 0x05,
    'STA': 0x06,
    'SPC': 0x07,
    'LPC': 0x08,
    'INC': 0x09,
    'DEC': 0x0a,
    'CMP': 0x0b,
    'JMP': 0x0c,
    'STP': 0x0d,
    'IN' : 0x0e,
    'OUT': 0x0f,
    'BIT': 0x10,
    'AND': 0x11,
    'OR' : 0x12,
    'XOR': 0x13,
    'NOT': 0x14,
    'SHL': 0x15,
    'SHR': 0x16,
    'CLS': 0x17
}

# check input file
if len(sys.argv) == 1:
    print('No input files!\nUsage: asm.py prog.asm')
    sys.exit(1)

# get input file name
filename = sys.argv[1];

# open asm source file
with open(filename) as input_file:
    # read source code
    src = input_file.read().split('\n')
    program = []

    # loop over lines
    for line in src:
        if line is not None:
            try:
                program.append(opcodes[line.split()[0]])
                value = int(line.split()[1], 16)
                
                if value > 0xff:
                    program.append(value >> 8)
                    program.append(value & 0x00FF)
                    pass
                
                else:
                    program.append(value)
                
            except IndexError:
                pass

with open('prog.bin', 'wb') as output_file:
    output_file.write(bytes(program))

print('\nYour program bytes:\n');
print(' '.join([f"{i:#0{4}x}" for i in  program]))
print('\n1. Type "FFFD" on CMK computer to load the program');
print('2. Open Arduino IDE => Serial Monitor')
print('3. Open file "prog.bin" using text editor and copy it\'s content')
print('4. Paste bytes to Arduino Serial Monitor ans click "send"');
print('5. Type "FFFF" on CMK computer to run the program');
print('\nEnjoy epic 8-bit computing experience!\n');
