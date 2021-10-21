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
import json

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
    'DBG': 0x0d,
    'IN' : 0x0e,
    'OUT': 0x0f,
    'BIT': 0x10,
    'AND': 0x11,
    'OR' : 0x12,
    'XOR': 0x13,
    'NOT': 0x14,
    'SHL': 0x15,
    'SHR': 0x16,
    'CLS': 0x17,
    'SDL': 0x18,
    'SDR': 0x19,
    'CRS': 0x1a,
    'NCR': 0x1b,
    'UDG': 0x1c,
    'SPR': 0x1d,
    'POS': 0x1e
}

# program labels
labels = {}

# check input file
if len(sys.argv) == 1:
    print('No input files!\nUsage: asm.py prog.asm')
    sys.exit(1)

# get input file name
filename = sys.argv[1];

# open asm source file
with open(filename) as input_file:
    # read source code
    src = [l.upper() for l in input_file.read().split('\n')]
    program = []
    byte_count = -1

    # init labels
    for line in src:
        if line != '':
            if line.strip()[0] == ';': continue
            try:
                byte_count += len(line.split(';')[0].split())
                try:
                    if len(line.split(';')[0].split()[1]) == 6: byte_count += 1
                    if line.split(';')[0].split()[1][0].isalpha():
                        if line.split()[0] in ['LDA', 'STA', 'LPC', 'JMP']:
                            byte_count += 1
                
                except:
                    pass
                
                if ':' in line:
                    labels[line[:-1]] = f'{byte_count:#0{6}x}'
                    byte_count -= 1
                
                if 'BYTE' in line or 'WORD' in line: byte_count -= 1
                
            except IndexError:
                pass

    # assemble code
    for line in src:
        if line != '':
            try:
                if ':' in line: continue
                if line.strip()[0] == ';': continue
                opcode = line.split()[0]
                
                try: program.append(opcodes[opcode])
                except:
                    if opcode != 'BYTE' and opcode != 'WORD':
                        print('Unknown opcode:', opcode);
                        sys.exit(1)
                  
                arg = line.split()[1]                
                if ('0x00') in arg and len(arg) == 6: program.append(0);
                
                try:
                    value = int(arg, 16)
                
                except:
                    try:
                        if ('0x00') in labels[arg] and len(labels[arg]) == 6:
                            if opcode in ['LDA', 'STA', 'LPC', 'JMP']:
                                program.append(0);
                        
                        value = int(labels[arg], 16)
                    
                    except:
                        print('Label "' + arg + '" doesn\'t exist!');
                        sys.exit(1)

                if value > 0xff:
                    program.append(value >> 8)
                    program.append(value & 0x00FF)
                
                else:
                    program.append(value)

            except IndexError:
                pass

print('\nYOUR PROGRAM LABELS:')
print(json.dumps(labels, indent=2))
print('\nYOUR PROGRAM BYTES:');
print(' '.join([f'{i:#0{4}x}' for i in  program]).replace('0x', '').replace(' ', '').upper())
print('\n1. Type "FFFD" on CMK computer to load the program');
print('2. Open Arduino IDE => Serial Monitor')
print('3. Copy and paste above bytes to Arduino Serial Monitor ans click "send"');
print('4. Type "FFFF" on CMK computer to run the program');
print('\nEnjoy epic 8-bit computing experience!\n');
