#define BT_BAUDRATE 9600

///////////////////////////////////////////////////////////////////////////
//      I/O configuration
///////////////////////////////////////////////////////////////////////////
#define   PA_DefData      0b00100000
#define   PA_DefTRIS      0b00000000

   //  5   LED
   //  4   NC
   //  3   MCLR
   //  2   NC
   //  1   PGEC
   //  0   PGED

#define   PC_DefData      0b00000000
#define   PC_DefTRIS      0b00100010

   // 5     RX
   // 4     TX
   // 3     NC
   // 2     CS
   // 1     IN
   // 0     CLK
   

///////////////////////////////////////////////////////////////////////////
//      GPS module connection
///////////////////////////////////////////////////////////////////////////
  
#USE RS232(BAUD=BT_BAUDRATE, UART1, ERRORS)


///////////////////////////////////////////////////////////////////////////
//      Define the register map for this processor
///////////////////////////////////////////////////////////////////////////

#BYTE SSP1STAT = 0x214
#BYTE SSP1CON1 = 0x215
#BYTE SSP1CON2 = 0x216
#BYTE SSP1BUF  = 0x211

#BYTE APFCON0 = 0x11D

#BYTE PORTA = 0x00C
#BYTE TRISA = 0x08C
#BYTE LATA  = 0x10C

#BYTE PORTC = 0x00E
#BYTE TRISC = 0x08E
#BYTE LATC  = 0x10E

///////////////////////////////////////////////////////////////////////////
//      Map the SPI port
///////////////////////////////////////////////////////////////////////////

#define GPS_SPISTAT      SSP1STAT
#define GPS_SPICON1      SSP1CON1
#define GPS_SPIBUF       SSP1BUF

//////////////////////////////////////////////////////////////////////////
//      Define Register Bits
//////////////////////////////////////////////////////////////////////////

#BIT SPI_WCOL=GPS_SPICON1.7
#BIT SPI_SSPOV=GPS_SPICON1.6
#BIT SPI_SSPEN=GPS_SPICON1.5
#BIT SPI_CKP=GPS_SPICON1.4
#BIT SPI_SSPM3=GPS_SPICON1.3
#BIT SPI_SSPM2=GPS_SPICON1.2
#BIT SPI_SSPM1=GPS_SPICON1.1
#BIT SPI_SSPM0=GPS_SPICON1.0

#BIT SPI_SMP=GPS_SPISTAT.7
#BIT SPI_CKE=GPS_SPISTAT.6
#BIT SPI_BF=GPS_SPISTAT.0

///////////////////////////////////////////////////////////////////////////
//      SPI connection to Main
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//      Status LED
///////////////////////////////////////////////////////////////////////////
#define  LED_Status_PIN LATA.5
#bit     LED = LED_Status_PIN

///////////////////////////////////////////////////////////////////////////
//      Bluetooth Enable 
///////////////////////////////////////////////////////////////////////////
#define  BT_WKUP_PIN LATC.3
#bit     BT_EN = BT_WKUP_PIN

///////////////////////////////////////////////////////////////////////////
//      ADC Pins
///////////////////////////////////////////////////////////////////////////
#define ADC_CLK_PIN  LATC.0
#define ADC_IN_PIN   PORTC.1
#define ADC_CS_PIN   LATC.2

#bit  ADC_CLK = ADC_CLK_PIN
#bit  ADC_IN = ADC_IN_PIN
#bit  ADC_CS = ADC_CS_PIN
