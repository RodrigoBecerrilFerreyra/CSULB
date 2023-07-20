#include <reg51.h>
void main(void) {
unsigned char mynum[]="ABCDEF"; //RAM space
unsigned char z;
for (z=0;z<=6;z++)
P1=mynum[z];
}