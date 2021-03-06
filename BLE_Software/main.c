#ZERO_RAM
#include <main.h>
#include "platform.h"

#define DELAY 1000

#USE FAST_IO (A)
#USE FAST_IO (C)

int1 flag_ADC = 0;
unsigned int16 ADC_result=0;
int16 timer_ADC = 0;
#define temps_ADC 250 // in ms

#int_TIMER0
void  TIMER0_isr(void) 
{
   if (timer_ADC++ == temps_ADC )
   {
      timer_ADC = 0;
      flag_ADC = 1;
   }
      
   clear_interrupt(INT_TIMER0);
}

void init_pic(void)
{
   // initialise port A
   LATA = PA_DefData;
   TRISA = PA_DefTRIS;
   // initialise port C
   LATC = PC_DefData;
   TRISC = PC_DefTRIS;
   APFCON0 = 0x0;
   
   //setup_timer_2 (T2_DIV_BY_16, 250, 10); //500 us overflow, 5.0 ms interrupt
   setup_comparator (NC_NC_NC_NC); // This device COMP currently not supported by the PICWizard
   setup_oscillator (OSC_8MHZ|OSC_PLL_ON) ;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);      //1.0 ms overflow

   setup_timer_4(T4_DISABLED,0,1);
   setup_timer_6(T6_DISABLED,0,1);
}

void ADS()
{
   LED=1;
   ADC_result = 0;
   unsigned int8 i;
   // Start a conversion with a lo pulse on ADC_CONVERT
   //ADC_CS = 0; // LOWER NOT-CS
   ADC_CLK = 0; //  clock low
   delay_cycles(4);
   ADC_CS = 0; // START CONVERT not CS line
   delay_cycles(4);

   for ( i = 0 ; i < 8 ; i++ )
   {
      ADC_CLK = 1;      
      delay_cycles(4);
      IF ( !ADC_IN ) 
         BREAK;
      ELSE 
         ADC_CLK = 0;
      delay_cycles(4);
   }

//   IF (8==i) BADDIE(51); // GLOBAL TIMED OUT WARN
   ADC_CLK = 0;   // produce a new lo-to-high clock
   delay_cycles(4);      // wait for a bit

   // now read data
   for (i=0;i<16;i++){
   ADC_CLK = 1;  // now after rising edge
   delay_cycles(8);      // OR input pin with 16bit int
   ADC_result |= ADC_IN; //   OR input pin with 16bit int
   ADC_CLK = 0;   // produce a new lo-to-high clock
   if (i !=15) 
      ADC_result=ADC_result<<1;         // and shift that bit along toward MSB
   delay_cycles(4);
  }
  // PREP FOR NEXT CYCLE
  ADC_CLK = 0;
  delay_cycles(8);
  ADC_CS = 1; // SHUT OFF CONVERTER 
  LED = 0;
}

void main()
{
   init_pic();
   BT_EN = 1;
   ADC_CS = 1;
   delay_ms(500);
   
   
   //Puts module into transparent UART mode immediately
   // Can do it with melody smart app 
   //command trs then wrt so store it
   printf("TRS\r");
   delay_ms(250);
   printf("READY !\r");
    delay_ms(250);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   //Example blinking LED program
   while(true)
   {
      
      if (flag_ADC)
      {
         flag_ADC=0;
         ADS();
         printf("ADC:%LX\r",ADC_result);
      }
      
   }

}
