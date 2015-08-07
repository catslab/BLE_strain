#include <16F1825.h>
#define CRYSTAL_FREQ 32000000
#device adc=16
//#device *=16
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES WDT_SW                   //No Watch Dog Timer, enabled in Software
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOIESO                   //Internal External SWITCH Over mode disabled
#FUSES NOSTVREN                 //Stack full/underflow will not cause reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NOPROTECT    //Code not protected from reading

#use delay (clock=CRYSTAL_FREQ)
