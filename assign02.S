#include "hardware/regs/addressmap.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/timer.h"
#include "hardware/regs/m0plus.h"

.syntax unified                                                 @ Specify unified assembly syntax
.cpu    cortex-m0plus                                           @ Specify CPU type is Cortex M0+
.thumb                                                          @ Specify thumb assembly for RP2040
.global main_asm                                                @ Provide program starting address to the linker
.align 4                                                        @ Specify code alignment

.equ    GPIO_BTN_EN_FALL_MSK, 0x00400000   @ Falling-edge event on GP21
.equ    GPIO_BTN_EN_RISE_MSK, 0x00800000   @ Rising-edge event on GP21
.equ    GPIO_BTN_EN,  21                   @ Specify pin for the "enter" button
.equ    GPIO_LED_PIN, 28                   @ Specify pin for the RGB led
.equ    GPIO_DIR_IN,   0                   @ Specify input direction for a GPIO pin
.equ    GPIO_DIR_OUT,  1                   @ Specify output direction for a GPIO pin
.equ    DFLT_ALARM_TIME, 9000000

.equ    SPACE, 1000000
.equ    NULLCH, 2000000
.equ    dottime, 3000000
.equ    nulltime, 20000000
.equ    GPIO_ISR_OFFSET, 0x74              @ GPIO is int #13 (vector table entry 29)
.equ    ALRM_ISR_OFFSET, 0x40              @ ALARM0 is int #0 (vector table entry 16)


@ Entry point to the ASM portion of the program
main_asm:
    //push    {lr}
    bl      init_button                 @ Initialise GP21
    bl      install_gpio_isr            @ Install the GPIO interrupt service routine
    bl      install_alarm_isr           @ Initialise alarm interrupts
    bl      set_alarm_time              @ Initialise the alarm timer 
    //pop     {pc}
    //main_loop here for initial development 
main_loop:
    b       main_loop     

@ Subroutine used to initialise button
init_button:
   push     {lr}                                                   
   movs     r0, #GPIO_BTN_EN          @ Load GPIO_BTN_EN pin number into r0 (GP2)
   bl       asm_gpio_init             @ Call subroutine to initialize GP21
   movs     r1, #GPIO_DIR_IN          @ Load GPIO_DIR_IN (input direction) into r1
   movs     r0, #GPIO_BTN_EN          @ Load GPIO_BTN_EN pin number into r0
   bl       asm_gpio_set_dir          @ Call subroutine to set GP21 direction to input
   movs     r0, #GPIO_BTN_EN          @ Load GPIO_BTN_EN pin number into r0
   bl       asm_gpio_set_irq          @ Call subroutine to enable falling edge & rising edge interrupt for GP21                   
   pop      {pc}           

@ Subroutine used to install the GPIO interrupt service routine
install_gpio_isr:
    ldr     r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)       @ Load address of the Vector Table Offset Register into r2
    ldr     r1, [r2]                                   @ Load the value from the Vector Table Offset Register into r16
    movs    r2, #GPIO_ISR_OFFSET                       @ Load the offset of the GPIO interrupt service routine into r2
    add     r2, r1                                     @ Add the base address of the vector table to the offset to get the address of the GPIO ISR
    ldr     r0, =gpio_isr                              @ Load the address of the GPIO ISR into r0
    str     r0, [r2]                                   @ Store the address of the GPIO ISR into the vector table at the calculated address
    movs    r0, #0                                     @ Clear r0
    movs    r1, #1                                     @ Load the value 1 into r1
    lsls    r1, r1, #13                                @ Shift the value left by 13 bits to set bit 13
    add     r0, r1                                     @ Add r0 and r1 which results in r0 with bit 13 set to avoid size errors
    ldr     r1, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)  @ Load address of the Interrupt Clear-Pending Register into r1
    str     r0, [r1]                                   @ Write 1 to the Interrupt Clear-Pending Register to disable the interrupt
    ldr     r1, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)  @ Load address of the Interrupt Set-Enable Register into r1
    str     r0, [r1]                                   @ Write 1 to the Interrupt Set-Enable Register to enable the interrupt
    bx      lr  

@ GPIO interrupt service routine
.thumb_func                     @ Required for all interrupt service routines
gpio_isr:
push    {lr}                        
    ldr     r2, =(IO_BANK0_BASE + IO_BANK0_PROC0_INTS2_OFFSET)    @ Load address of the GPIO interrupt register into r2
    ldr     r0, [r2]                                              @ Load the value from the GPIO interrupt register into r0

    ldr     r1, = GPIO_BTN_EN_FALL_MSK                            @ Load the address of GPIO_BTN_DN_MSK into r1
    cmp     r1, r0
    beq     falling_edge_case

    ldr     r1, = GPIO_BTN_EN_RISE_MSK                            @ Load the address of GPIO_BTN_DN_MSK into r1
    cmp     r1, r0
    beq     rising_edge_case

falling_edge_case:
    ldr     r2, =(IO_BANK0_BASE + IO_BANK0_INTR2_OFFSET)          @ Load address of the GPIO interrupt register into r2
    ldr     r1, =GPIO_BTN_EN_FALL_MSK                             @ Load the address of GPIO_BTN_EN_FALL_MSK into r1
    str     r1, [r2]                                              @ Clears the interrupt

    bl      pressed_time
    ldr     r5, =SPACE
    cmp     r0, r5
    bgt     space
finished:

    bl      start_timestamp
    b       done

rising_edge_case:
    ldr     r2, =(IO_BANK0_BASE + IO_BANK0_INTR2_OFFSET)          @ Load address of the GPIO interrupt register into r2
    ldr     r1, =GPIO_BTN_EN_RISE_MSK                             @ Load the address of GPIO_BTN_EN_RISE_MSK into r1
    str     r1, [r2]                                              @ Clears the interrupt

    bl      pressed_time
    //      Compare to either dash or dot time

    ldr     r5,=dottime                                           @ Load time for considering a dot(3s)
    cmp     r0,r5                                                 @ Compare the returned value
    ble     dot                                                   @ If it is less or equal consider it a dot
    bgt     dash                                                  @ If greater consider a dash

    b       done 

dot:
    movs    r0, #1
    bl      addtoanswer                                           @ Add a dot to the answer array
    ldr     r0,=msgdot                                            @ Print the dot on the console
    bl      printf
    b       done

dash:
    movs    r0,#2                           
    bl      addtoanswer                                           @ Add a dash to the answer array
    ldr     r0,=msgdash                                           @ Print the dash on the console
    bl      printf
    b       done

space:
    movs    r0, #3
    bl      addtoanswer
    ldr     r0, =msgspace
    bl      printf
    b       finished 

null:
   movs    r0,  #4
   bl      addtoanswer

   b       done

done:
    pop     {pc} 


@ Subroutine used to install the Alarm interrupt service handler
install_alarm_isr:
        ldr     r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)            @ Loading the address of the RAM vector table into r2.
        ldr     r1, [r2]                                        @ Load the vlaue sotred at the address in r2 into r1.
        movs    r2, #ALRM_ISR_OFFSET                            @ Load ALRM_ISR_OFFSET into r2.
        add     r2, r1                                          @ Add r1 and r0, store result in r0.
        ldr     r0, =alarm_isr                                  @ Load the address of alarm_isr into r2.
        str     r0, [r2]                                        @ Store the value "address" in r0 into the address location stored in r2.

        movs    r0, #1                                          @ Load '1' into r0.
        ldr     r1, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)       @ Load the address of "..." into r1.
        str     r0, [r1]                                        @ Store 1 at the address loaciton stored in r1.
        ldr     r1, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)       @ Load the address of "..." into r0.
        str     r0, [r1]                                        @ Store 1 into the address loaction stored in r1.
        
        bx      lr                                              @ Branch back from subroutine.

@ Subroutine used to initialise the time elapsed
set_alarm_time:
    ldr     r2, =TIMER_BASE                   @ Load the base address of the timer registers into r2
    movs    r1, #1                            @ Move the value 1 into r1 to enable the timer interrupt
    str     r1, [r2, #TIMER_INTE_OFFSET]      @ Store the value of r1 into the TIMER_INTE_OFFSET register to enable the timer interrupt
    ldr     r1, [r2, #TIMER_TIMELR_OFFSET]    @ Load the value of the TIMER_TIMELR_OFFSET register into r1 
    ldr     r3, =ltimer                       @ Load the address of timeout into r3
    ldr     r0, [r3]                          @ Load the current value of timeout into r0
    add     r1, r0                            @ Add the current timer value to the value loaded from TIMER_TIMELR_OFFSET 
    str     r1, [r2, #TIMER_ALARM0_OFFSET]    @ Store the new alarm time into the TIMER_ALARM0_OFFSET register
    bx      lr                                @ Return from subroutine

@ SVC interrupt service handler routine
.thumb_func                     @ Required for all interrupt service routines
alarm_isr:
        push    {lr}                                     @ Push return address onto the stack.
        
        ldr     r2, =(TIMER_BASE + TIMER_INTR_OFFSET)    @ Load the address of the TIMER_BASE into r2.
        movs    r1, #1                                   @ Load '1' into r1.
        str     r1, [r2]                                 @ Store 1 at the offset address calculated.
        
        //TODO: check if there is time stored
 
        pop     {pc}
             
.align 4
msgdot:    .asciz "."
msgdash:   .asciz "-"
msgspace:  .asciz " "


@ Set data alignment
.data
ltimer: .word   DFLT_ALARM_TIME
    .align 4