import numpy as np
import matplotlib.pyplot as plt


# variables for registers
reg_list = ["0000000000000000", "0000000000000000", "0000000000000000", "0000000000000000",
            "0000000000000000", "0000000000000000", "0000000000000000", "0000000000000000"]

mem_add = '00000000'  # to store keys which are all the values of program counter
pc = '00000000'  # program counter
cycle = -1  # counter variable
ques3_part1 = np.array([])
ques3_part2 = np.array([])  # np array of counter variable
li = []

for i in range(256):
    li.append('0000000000000000')


def printing():
    print(pc, reg_list[0], reg_list[1], reg_list[2], reg_list[3],
          reg_list[4], reg_list[5], reg_list[6], reg_list[7])


bin = {}  # dictionary of instructions

while(True):  # storing instructions in the list
    instruction = input()
    if instruction[0:5] == '10011':
        bin.update({mem_add: instruction})
        break
    bin.update({mem_add: instruction})
    mem_add = format(int(mem_add, 2)+1, '#010b')[2:]

counter = 0
for i in bin.values():
    li[counter] = i
    counter = counter + 1


def plot_show():
    plt.scatter(ques3_part2, ques3_part1)
    plt.xlabel('Cycle')
    plt.ylabel('Address')
    plt.title('Memory Accesses v/s Cycles')
    plt.savefig('test.png')
    plt.show()


def mem_dump():
    # function to print the memory dump once halt is encountered
    for i in li:
        print(i)
    plot_show()


while True:

    # Type A instructions begin

    if bin[pc][0:5] == '00000':  # addition instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value+reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value > 65535):  # checking condition for overflow
            reg_list[reg1] = format(
                reg1_value, '#018b')[-16:]  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '00001':  # subtraction instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value-reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value < 0):  # checking condition for neagtive answers
            reg_list[reg1] = '0000000000000000'  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '00110':  # multiply instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value*reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value > 65535):  # checking condition for neagtive answers
            reg_list[reg1] = format(
                reg1_value, '#018b')[-16:]  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01010':  # Exclusive OR instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value ^ reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value > 65535):  # checking condition for overflow
            reg_list[reg1] = format(
                reg1_value, '#018b')[-16:]  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01011':  # OR instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value | reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value > 65535):  # checking condition for overflow
            reg_list[reg1] = format(
                reg1_value, '#018b')[-16:]  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01100':  # AND instruction
        reg1 = int(bin[pc][7:10], 2)
        reg2 = int(bin[pc][10:13], 2)
        reg3 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg3_value = int(reg_list[reg3], 2)
        reg1_value = reg2_value & reg3_value
        reg_list[7] = '0000000000000000'  # resetting the flags
        if(reg1_value > 65535):  # checking condition for overflow
            reg_list[reg1] = format(
                reg1_value, '#018b')[-16:]  # extra bit ignored
            reg_list[7] = '0000000000001000'  # overflow flag made 1
        else:
            reg_list[reg1] = format(reg1_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    # Type B instructions begin

    elif bin[pc][0:5] == '00010':  # Move Immediate instruction
        reg1 = int(bin[pc][5:8], 2)
        reg_list[reg1] = '00000000'+bin[pc][8:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01000':  # Right Shift instruction
        reg1 = int(bin[pc][5:8], 2)
        imm = bin[pc][8:]
        immediate = int(imm, 2)
        a = int(reg_list[reg1], 2)
        a = a >> immediate
        reg_list[reg1] = format(a, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01001':  # Left Shift instruction
        reg1 = int(bin[pc][5:8], 2)
        imm = bin[pc][8:]
        immediate = int(imm, 2)
        a = int(reg_list[reg1], 2)
        a = a << immediate
        reg_list[reg1] = format(a, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    # Type C instructions begin

    elif bin[pc][0:5] == '00011':  # Move Register Instruction
        reg1 = int(bin[pc][10:13], 2)
        reg2 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg_list[reg1] = format(reg2_value, '#018b')[2:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '01110':  # Compare instruction
        reg1 = int(bin[pc][10:13], 2)
        reg2 = int(bin[pc][13:16], 2)
        reg1_value = int(reg_list[reg1], 2)
        reg2_value = int(reg_list[reg2], 2)

        reg_list[7] = '0000000000000000'  # resetting the flags

        if(reg1_value == reg2_value):
            reg_list[7] = "0000000000000001"

        if(reg1_value > reg2_value):
            reg_list[7] = "0000000000000010"

        if(reg1_value < reg2_value):
            reg_list[7] = "0000000000000100"

        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]
        # reg7='000000000000000' #resetting the flags

    elif bin[pc][0:5] == '01101':  # Invert Instruction
        reg1 = int(bin[pc][10:13], 2)
        reg2 = int(bin[pc][13:16], 2)
        temp = reg_list[reg2]
        temp2 = ''
        for i in range(len(temp)):
            if(temp[i] == '0'):
                temp2 = temp2 + '1'
            else:
                temp2 = temp2 + '0'
        reg_list[reg1] = temp2
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '00111':  # Divide Instruction
        reg1 = int(bin[pc][10:13], 2)
        reg2 = int(bin[pc][13:16], 2)
        reg2_value = int(reg_list[reg2], 2)
        reg1_value = int(reg_list[reg1], 2)
        quotient = int(reg1_value/reg2_value)
        remainder = int(reg1_value % reg2_value)
        reg_list[0] = format(quotient, '#010b')[2:]
        reg_list[1] = format(remainder, '#010b')[2:]
        while(len(reg_list[0]) < 16):
            reg_list[0] = '0' + reg_list[0]
        while(len(reg_list[1]) < 16):
            reg_list[1] = '0' + reg_list[1]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    # Type D instructions begin

    elif bin[pc][0:5] == '00100':  # Load Instruction
        reg1 = int(bin[pc][5:8], 2)
        address = bin[pc][8:]
        reg_list[reg1] = li[int(address, 2)]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        ques3_part1 = np.append(ques3_part1, int(address, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    elif bin[pc][0:5] == '00101':  # Store Instruction
        reg1 = int(bin[pc][5:8], 2)
        address = bin[pc][8:]
        # bin[address]=reg_list[reg1]
        li[int(address, 2)] = reg_list[reg1]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        ques3_part1 = np.append(ques3_part1, int(address, 2))
        pc = format(int(pc, 2)+1, '#010b')[2:]

    # Type E instructions begin

    elif bin[pc][0:5] == '01111':  # Unconditional jump Instruction
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        pc = bin[pc][8:]
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)

    elif bin[pc][0:5] == '10001':  # greater jump Instruction

        if(reg_list[7] == '0000000000000010'):
            temp_pc = bin[pc][8:]
        else:
            temp_pc = format(int(pc, 2)+1, '#010b')[2:]
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        pc = temp_pc

    elif bin[pc][0:5] == '10000':  # lower jump Instruction
        if(reg_list[7] == '0000000000000100'):
            temp_pc = bin[pc][8:]
        else:
            temp_pc = format(int(pc, 2)+1, '#010b')[2:]
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        pc = temp_pc

    elif bin[pc][0:5] == '10010':  # equal jump Instruction
        if(reg_list[7] == '0000000000000001'):
            temp_pc = bin[pc][8:]
        else:
            temp_pc = format(int(pc, 2)+1, '#010b')[2:]
        ques3_part1 = np.append(ques3_part1, int(pc, 2))
        cycle = cycle+1
        ques3_part2 = np.append(ques3_part2, cycle)
        reg_list[7] = '0000000000000000'  # resetting the flags
        printing()
        pc = temp_pc

    elif bin[pc] == '1001100000000000':  # Halt instruction
        reg_list[7] = '0000000000000000'
        printing()
        mem_dump()
        break
