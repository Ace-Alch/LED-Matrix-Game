
//ARM INSTRUCTIONS
//Instructions are conditional
//32-bit instruction


//How to load data from memory:
//LDR R0, =variable 	(Load address to register. You can use any global variable defined in main.c, or variable found here)
//LDR R1, [R0] 			(Load data from address, in this case 32-bit data)
//LDRB R1, [R0] 		(Load data from address, in this case 8-bit data)
//******
//LDR R0, =0x123456		(Load address to register, Use only if you know the memory address)
//LDR R1, [R0]			(load data from address, in this case 32-bit data)
//LDRB R1, [R0]			(load data from address, in this case 8-bit data)

//How to store data to memory:
//STR R1,[R0]			(R1 contains the data and R0 contains the address where  to store, 32-bit)
//STRB R1,[R0]			(R1 contains the data and R0 contains the address where  to store, 8-bit)




.data
dir: .byte 1        // 1 for left->right, 0 for right->left
pos: .byte 0        // Position of the current LED

.text

.global blinker

blinker:
    LDR R0, =0x41200000      // GPIO output register address

    // Start with LD0 to LD3 - FORWARD
light_forward:
    MOV R1, #0x1             // 0x1 = 0001, lights up LD0
    STR R1, [R0]
    MOV R2, #0x0100000       // Delay for visibility, after each lighting
delay_loop0:
    SUBS R2, R2, #1
    BNE delay_loop0

    MOV R1, #0x2             // 0x2 = 0010, lights up LD1
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop1:
    SUBS R2, R2, #1
    BNE delay_loop1

    MOV R1, #0x4             // 0x4 = 0100, lights up LD2
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop2:
    SUBS R2, R2, #1
    BNE delay_loop2

    MOV R1, #0x8             // 0x8 = 1000, lights up LD3
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop3:
    SUBS R2, R2, #1
    BNE delay_loop3

    // LD3 to LD0 - BACKWARD
light_reverse:
    MOV R1, #0x4             // 0x4 = 0100, lights up LD2
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop4:
    SUBS R2, R2, #1
    BNE delay_loop4

    MOV R1, #0x2             // 0x2 = 0010, lights up LD1
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop5:
    SUBS R2, R2, #1
    BNE delay_loop5

    MOV R1, #0x1             // 0x1 = 0001, lights up LD0
    STR R1, [R0]
    MOV R2, #0x0100000
delay_loop6:
    SUBS R2, R2, #1
    BNE delay_loop6

    B light_forward          // Repeat the sequence - go to line with function "light_forward"

