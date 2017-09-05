/* 
 * File:   felipe_andre_1.c
 * Author: Andre e Felipe
 *
 * Created on 25 de Maio de 2017, 09:11
 */

#include <stdio.h>
#include <stdlib.h>

// DSPIC33EP256MC502 Configuration Bit Settings

#include <xc.h>

#ifndef __dsPIC33E__
#define __dsPIC33E__
#endif

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are enabled)

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Source Selection (Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL))
#pragma config PWMLOCK = OFF            // PWM Lock Enable bit (PWM registers may be written without key sequence)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

void conf_remappable_pins(){
    __builtin_write_OSCCONL(OSCCON & ~(1<<6));          // Unlock Registers
    RPINR14bits.QEA1R = 0x2F;                           // Assign QEI1-A To Pin RP147
    RPINR14bits.QEB1R = 0x2E;                           // Assign QEI1-B To Pin RP146
    __builtin_write_OSCCONL(OSCCON | (1<<6));           // Lock Registers
}

void conf_QEI(void){
    QEI1CONbits.QEIEN = 1;     // enable QUEI1
    QEI1CONbits.PIMOD = 0b110; // module count mode for pos count

    QEI1IOCbits.FLTREN = 1;    // enable digital filters
    QEI1IOCbits.QFDIV = 0b010; // specify digital filter on 1:4 clock

    QEI1STATbits.POSOVIEN = 0; // position overflow interrupt disabled
    QEI1STATbits.VELOVIEN = 0; // velocity overflow interrupt disabled

    // talvez seja necessario as seguintes confs

//    QEI1CONbits.CNTPOL = 0;    // counter direction positive
//
//    QEI1IOCbits.QCAPEN = 1;    // triggers position capture on positive edge
//    QEI1IOCbits.SWPAB = 0;     // disable phase a / b swap
//
//    QEI1STATbits.POSOVIRQ = 1; // detect position overflow (status bit)
//    QEI1STATbits.VELOVIRQ = 1; // detect velocity overflow (status bit)
}

int main(void) {
    //    Configurações de reset
   if (RCONbits.POR == 1 && RCONbits.BOR == 1){  // Verifica se o reset foi por Power on
        // configure the modules of the system
//        conf_clock_XC();
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.POR = 0;  // Zera POR
        RCONbits.BOR = 0;  // Zera BOR
   } else if  (RCONbits.POR == 0 && RCONbits.BOR == 1){ // Verifica se o reset foi por queda de tensão
//        conf_clock_XC();
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.BOR = 0;    // Zera BOR
   } else if (RCONbits.EXTR == 1){ // Verifica se o reset foi externo
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.EXTR = 0;
   } else  if (RCONbits.SWR == 1){ // verifica se o reset foi for software
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.SWR = 0;
   } else if (RCONbits.WDTO == 1){ // verifica reset pelo Watchdog Time
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.WDTO = 0;
   } else if (RCONbits.TRAPR == 1){  // verifica reset pelo trap
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        onf_PortB_pins();
//        onf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.TRAPR = 0;
   } else if (RCONbits.CM == 1){  // verifica reset por falha de configuração
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.CM = 0;
   } else if (RCONbits.IOPUWR == 1 ){  // verifica reset operação ilegal de periférico
        conf_remappable_pins();
//        disable_modules();
//        conf_PWMs();
        conf_QEI();
//        conf_INT1R();
//        conf_PortB_pins();
//        conf_ADCs();
//        conf_comparators();
//        conf_I2C_1();
//        conf_I2C_2();
        RCONbits.IOPUWR = 0;
   }

//   /* Create the first task at priority 1... */
//    xTaskCreate( vTaskFunction, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL );
//
//    /* ... and the second task at priority 2.  The priority is the second to
//    last parameter. */
//    xTaskCreate( vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL );
//
//    /* Start the scheduler so our tasks start executing. */
//    vTaskStartScheduler();
//
//    for( ;; );


    return (EXIT_SUCCESS);
}

