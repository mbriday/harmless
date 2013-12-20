volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

//volatile unsigned int *a = (unsigned int *)0x101f1000;

void c_entry() {
 
 /* big loop ! */
 unsigned long int i = 0; 
 volatile unsigned int a = 42;
 while(i <= 1000000) {
 	a = a+i - a <<5;
 	a *= i-a%3;
 	i++;
 }
 
 print_uart0("q\n");
}
