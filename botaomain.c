// DESENVOLVIDO POR ALEXANDER A.
// ESTE EXEMPLO FUNCIONA DA SEGUINTE FORMA:
//
// - AO PRESSIONAR O BOTAO CONECTADO AO PINO RB0,
//   PISCA O LED1 CONECTADO AO PINO RA2,
//
// - AO PRESSIONAR NOVAMENTE O BOTAO CONECTADO AO PINO RB0,
//   PISCA O LED2 CONECTADO AO PINO RA3,
//
// - AO PRESSIONAR NOVAMENTE O BOTAO CONECTADO AO PINO RB0,
//   PISCA O LED1 E LED2 ALTERNADAMENTE,
//
// - AO PRESSIONAR NOVAMENTE O BOTAO CONECTADO AO PINO RB0,
//   DESLIGA-SE OS LED.

#include <xc.h>
#include <pic16f628a.h>

#pragma config BOREN = ON    // turn on boren
#pragma config WDTE  = OFF   // turn off watchdog timer
#pragma config CP    = OFF   // turn off code protection
#pragma config PWRTE = ON    // turn on power reset
#pragma config LVP   = OFF   // turn off burn in high voltage
#pragma config MCLRE = OFF   // turn off use pin 5 to Master Clear
#pragma config FOSC  = 0b100 // use internal oscillator and
                             // I/O function on RA6 and RA7 pins

#define _XTAL_FREQ 4000000   // 4.000.000 Hz = 4 MHz
#define BOTAO      PORTBbits.RB0
#define LED1       PORTAbits.RA2
#define LED2       PORTBbits.RB3

void state(int number);

void main( void ){
    // configuracao. freq. do oscilador interno em 4 MHz
    PCONbits.OSCF = 1;

    // configuracao registrador OPTION
    // 1 - NOT_RBPU    -> desativa resistores pull-up
    // 0 - INTDEG      -> int. ativa em borda de descida em RB0
    // 0 - TOCS        -> clock do TIMER 0 eh interno
    // 0 - TOSE        -> borda de subida no TIMER 0 em RA4
    // 0 - PSA         -> prescaler associado ao TIMER 0
    // 0 - PS2,PS1,PS0 -> TIMER 0 com razao 1:2
    OPTION_REG = 0b10000000; // 0b10000000 = 0200 = 128 = 0x80

    // modifica o comportamento dos pinos de PORTA
    // 1 - pino RA7 como entrada
    // 1 - pino RA6 como entrada
    // 1 - pino RA5 como entrada
    // 1 - pino RA4 como entrada
    // 0 - pino RA3 como entrada
    // 0 - pino RA2 como saida
    // 1 - pino RA1 como entrada
    // 1 - pino RA0 como entrada
    TRISA = 0b11110011; // 0b11110011 

    // modifica o comportamento dos pinos de PORTB
    // 1 - pino RB7 como entrada
    // 1 - pino RB6 como entrada
    // 1 - pino RB5 como entrada
    // 1 - pino RB4 como entrada
    // 1 - pino RB3 como entrada
    // 1 - pino RB2 como entrada
    // 1 - pino RB1 como entrada
    // 1 - pino RB0 como entrada
    TRISB = 0b11111111; // 0b11 = 0377 = 255 = 0xFF

    // define modo de operacao dos comparadores analog. desligados
    CMCON = 0b00000111; // 0b00000111 = 07 = 7 = 0x07

    // configuracoes de interrupcoes
    // 0 - GIE  -> desativa todas as interrupcoes (chave geral)
    // 0 - EEIE -> desativa int. da EEPROM
    // 0 - T0IE -> desativa int. do TMR0
    // 0 - INTE -> desativa int. do RB0/INT
    // 0 - RBIE -> desativa int. mudanca RB<7:4>
    // 0 - T0IF -> flag de transbordo DO TMR0
    // 0 - INTF -> flag de resposta int. RB0/INT
    // 0 - RBIF -> flag de resposta int. em RB<7:4>
    INTCON = 0b00000000; // 0b00000000 = 0 = 0 = 0x00
    
    int buttonstate = 0;

    // rotinas
    LED1 = 0;
    LED2 = 0;

	while( 1 ){
		
		if( BOTAO !=1 ){     
            
            if( buttonstate <4 ){
                buttonstate++;
            }
			else {
				buttonstate = 0;
			}
			
			while( BOTAO != 1 ){
				__delay_ms(10);
			}

		}
		
		state(buttonstate);
		__delay_ms(50);
	}
}

void state(int number){
	switch(number){
		case 0:
			LED1 = 0;
			LED2 = 0;
			break;
		case 1:
			LED1 = 0;
			__delay_ms(50);
			LED1 = 1;
			__delay_ms(50);
			LED2 = 0;
			break;
		case 2:
			LED1 = 0;
			LED2 = 0;
			__delay_ms(50); 
			LED2 = 1;
			__delay_ms(50); 
			break;   
		case 3:
			LED1 = 0;
			__delay_ms(50); 
			LED1 = 1;
			__delay_ms(50); 
			LED2 = 0;
			__delay_ms(50); 
			LED2 = 1;
			__delay_ms(50); 
			break;
	    default:
			LED1 = 0;
			LED2 = 0;
			break;
	
	}//end switch
}