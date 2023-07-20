#ifndef TM4C_UART0_H
#define TM4C_UART0_H

void outputString(const char*);
void outputChar(const char);
void outputNewLine(void);
char getInputChar(void);
void getInputString(char*, int);

#endif
