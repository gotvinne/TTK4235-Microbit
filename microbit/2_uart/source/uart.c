#include "uart.h"
#include "gpio.h"


//Lager struct for UART på samme måte som GPIO
/* Fyll inn disse */
#define PIN_TX 24
#define PIN_RX 25
#define PIN_DISABLE 0xFFFFFFFF
#define BAUD_9600 0x00275000

#define UART_DISABLE 0
#define UART_ENABLE 4

/* Fyll inn riktig startadresse */
#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    /* Tasks */
    /* Her skal det fylles inn seks felter */
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX; 
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED[3];
	volatile uint32_t SUSPEND; //Dette stemmer 

	/* Events */
	volatile uint32_t RESERVED1[56];
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVED2[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED3;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED4[7];
	volatile uint32_t RXTO;
	/* Registers */
	volatile uint32_t RESERVED5[110];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED6[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED7[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED8;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD; //Dette er masker
	volatile uint32_t TXD;
	volatile uint32_t RESERVED9;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED10[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
    UART->ENABLE = UART_DISABLE;

    GPIO->PIN_CNF[PIN_TX] = 1;
    GPIO->PIN_CNF[PIN_RX] = 0;

    /* Konfigurer "Pin Select" for RTS, CTS, TXD, og RXD */
	//RXD og TXD 
	UART->PSELRXD = PIN_RX; //Tar vi hensyn til bit som står fra før? 
	UART->PSELTXD = PIN_TX; 

	//RTS og CTS 
	UART->PSELRTS = PIN_DISABLE;
	UART->PSELCTS = PIN_DISABLE; 

    /* Konfigurer Baudhastigheten */
	UART->BAUDRATE = BAUD_9600; 


    UART->ENABLE = UART_ENABLE;

    UART->STARTRX = 1;
}

void uart_send(uint8_t byte){
	UART->STARTTX = 1; //Starter en transmission
	UART->TXD = byte; 

	while(!UART->TXDRDY); //Denne vil gå i loop, så lenge informasjonen sendes. 
 	UART->TXDRDY = 0; //Vi må resette den for å kunne skrive nytt. 

	UART->STOPTX = 1; //Stopper transmission

}

uint8_t uart_receive(uint8_t * p_byte){
    if(!UART->RXDRDY)
        return 0;

    UART->RXDRDY = 0;
    *p_byte = UART->RXD;
    return 1;
}
