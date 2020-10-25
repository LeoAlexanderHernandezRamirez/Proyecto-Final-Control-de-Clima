//Team Microvid 7B Base en C PROYECTO FINAL GG v2


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 8000000


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44
   int volatile RESULTHI=0;
   int volatile RESULTLO=0;           //Variables
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void delay(unsigned int time)
{
    for(int i=0;i<1000;i++){
       asm("nop"); 
    }
                         //Delay
}                           ///Delay

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44

void main(void) {
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //Configuraciones del ADC
    
    //Reloj
    OSCCON= 0b01110100;
    /////////////////////////////////////////////////////////////////////////////////////////////////7
  
    ANSEL = 0b00000001;                 // activamos la entrada analogica 
    ANSELH= 0x00;
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    ADCON1 = 0b00000000;                //justificamos a la derecha
    ADCON0 = 0b00000001;                // colocamos a 8 y activamos las lecturas de adc
    
    //////////////////////////////////////////////////////////////////////////////////////////////
                
    PORTA = 0x00;                       //limpiamos el porta
    TRISA = 0xFF;                       //lo colocamos como entrada
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    PORTB = 0x00;                       //limpiamos el portb y lo ponemos como salida
    TRISB = 0x00;
    TRISD= 0b11000000;
    PORTD=0x00;
    
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //configuraciones para el usart
    
    INTCON = 0b11000000;                //activamos las interrupciones globales y por perifericos (opcional)
    PIE1 = 0b00000000;                  //Activamos RECIE para recepcion de datos y TXIE para la transmision de datos (REVISAR)
    
    //////////////////////////////////////////////////////////////////////////////////
    
    PORTC = 0x00;                       //limpiamos el portC
    TRISC = 0b10000000;                 //lo colocamos RX como entrada y los demas como salida incluyendo TX
    /////////////////////////////////////////////////////////////////////////////
    
    TXEN = 1;
    SYNC = 0;                      //Activamos la transmision en modo asincrono mediante la modificacion del registro TXSTA y RCSTA
    SPEN =1;
    BRGH=1;
 
    CREN=1;

    SPBRG=8;                       // GRACIAS A LA CONFIGURACION DE LOS PINES SYNC, BRGH Y BGR16 Y DEBIDO A QUE EL OSILADOR ESTA TRABAJANDO A 8MHZ, TRABAJARA A 57600BPS

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
   ////////////////////////////////////////////////////////////////////////////////////////////////////
    delay (1000);                //tiempo de adquisicion
                  //Activamos la conversion de adc
     
    while (1){
    
    for(int i=0;i<50;i++){
    ADCON0 = 0b01000011; 
    while(ADCON0bits.GO_nDONE){
     PORTB=ADRESH;
     PORTD=ADRESL;
     
     char HI[50];
     char LO[50];
     
     HI[i]=ADRESH ;
     LO[i] =ADRESL ;
    
     }
    char g[10]={54,65, 55,50,52,51,49,48,32};
    //aqui se encuentra un codigo representativo de encendido
     for(int o=0;o<10;o++){
    while(TXSTAbits.TRMT==1){          //TRANMISION DEL CODIGO DE ENCENDIDO 
        TXREG=g[o];
        } 
   
        while(TXSTAbits.TRMT ==0){
            continue;
         } 
     
    }  
    __delay_ms(10000);
     }
     }
    return;
}