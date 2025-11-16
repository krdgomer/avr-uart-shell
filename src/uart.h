
#define FOSC 16000000UL  // Most Arduinos are 16MHz, not 1.8MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Transmit_str(char* str);