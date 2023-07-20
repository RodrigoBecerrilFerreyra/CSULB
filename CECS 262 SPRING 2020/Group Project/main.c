#include <reg51.h>

#define Green 0
#define Yellow 1
#define Red 2

// pedestrian crossing lights (outputs)
sbit pedLightNS = P1^6;
sbit pedLightEW = P1^7;

// traffic lights (outputs)
sbit redNS = P2^0;
sbit yelNS = P2^1;
sbit grnNS = P2^2;
sbit redEW = P2^3;
sbit yelEW = P2^4;
sbit grnEW = P2^5;

void delay(unsigned char);// void delay2(unsigned char);
void lightHandler(void); //void lightHandler(unsigned char*);
void outputHandler(void);

// serial communication
void UART_init();
void transmit_data(char tx_data);
void String(char *str);
//unsigned char receive_1_byte(void);


volatile unsigned char current_state_light_NS, current_state_light_EW;
volatile unsigned int timer_high, timer_low; //for saving the value of the timer during an intterupt

int main(void)
{  
  
  
  UART_init();
  
  
  
  IE = 0x85;  //enable the interrupts
  
  P1 = 0x00; P2 = 0x0C; //initialize outputs
  
  while(1)
  {
    lightHandler();
    outputHandler();
  }
}

void outputHandler(void)
{
  switch(current_state_light_NS)
  {
    case Red:
      redNS = 1; yelNS = 0; grnNS = 0;
      break;
    case Yellow:
      redNS = 0; yelNS = 1; grnNS = 0;
      break;
    case Green:
    	redNS = 0; yelNS = 0; grnNS = 1;
      break;
  }
  
  switch(current_state_light_EW)
  {
    case Red: 
			redEW = 1; yelEW = 0; grnEW = 0;
			break;
    case Yellow: 
			redEW = 0; yelEW = 1; grnEW = 0; 
      break;
    case Green: 
      redEW = 0; yelEW = 0; grnEW = 1; 
      break;      
  }
}

void delay(unsigned char seconds)
{
	unsigned char i, j;
  
  for(j = 0; j < seconds; j++)
  {
    for(i = 0; i < 20; i++) // 1 s
    {
      TMOD = 0x21; // mode 1
      TH0 = 0x3c; TL0 = 0xb0; // 0xffff - 50 000; 50 ms
      TR0 = 1; // turn timer on
      while(TF0 == 0); // do nothing until overflow
      TF0 = 0; // reset flag
    }
    TR0 = 0; // turn off timer
  }
}
/*
void delay2(unsigned char seconds)
{
	unsigned char i, j;
  
  for(j = 0; j < seconds; j++)
  {
    for(i = 0; i < 20; i++) // 1 s
    {
      TMOD = 0x11; // mode 1
      TH1 = 0x3c; TL1 = 0xb0; // 0xffff - 50 000; 50 ms
      TR1 = 1; // turn timer on
      while(TF1 == 0); // do nothing until overflow
      TF1 = 0; // reset flag
    }
    TR1 = 0; // turn off timer
  }
}
*/
void lightHandler(void)
{
  if     (current_state_light_NS == Green && current_state_light_EW == Red)
  {
    delay(6);
    current_state_light_NS = Yellow;
  }
  else if(current_state_light_NS == Yellow && current_state_light_EW == Red)
  {
    delay(2);
    current_state_light_NS = Red; current_state_light_EW = Green;
  }
  else if(current_state_light_NS == Red && current_state_light_EW == Green)
  {
    delay(6);
    current_state_light_EW = Yellow;
  }
  else if(current_state_light_NS == Red && current_state_light_EW == Yellow)
  {
    delay(2);
    current_state_light_NS = Green; current_state_light_EW = Red;
  }
  // default
  else
  {
    current_state_light_NS = Green; current_state_light_EW = Red;
    redNS = 0; yelNS = 0; grnNS = 1;
    redEW = 1; yelEW = 0; grnEW = 0;
  }
}

void EWbutton() interrupt 0//ISR for button NS
{
  //switch case statement that will turn on pedestrian light based on what state we are in
  if (current_state_light_NS == Green) // assume that ns is red while ew is green otherwise code sucks and we need to change something
  {//
    //unsigned char i; unsigned char arr[1];
    TR0 = 0; //turn off timer 0 
    timer_high = TH0; timer_low = TL0; //save
    delay(1); // delay 1 second then go to yellow
    current_state_light_NS = Yellow; outputHandler();
    delay(2); //delay for 1 s and turn to red
    current_state_light_NS = Red; current_state_light_EW = Green; outputHandler(); // this is when this traffic light turns green
    
    pedLightEW = 1; //parallel direction
    
    // display on LCD
    String("Seconds left for EW : \n\n\r");
    
    String("6\n\r"); delay(1);
    String("5\n\r"); delay(1);
    String("4\n\r"); delay(1);
    String("3\n\r"); delay(1);
    String("2\n\r"); delay(1);
    String("1\n\r"); delay(1);
    
    pedLightEW = 0;
    current_state_light_EW = Yellow; outputHandler();
    // Ped light blinking
    delay(1); pedLightEW = 1;
    delay(1); pedLightEW = 0;
    String("STOP\n\n\r");
    // current state: NS is Yellow, EW is Red
    lightHandler(); outputHandler();
    TH0 = timer_high; TL0 = timer_low; //load
    TR0 = 1; //turn on timer 0
  }
}

void NSbutton() interrupt 2//ISR for button EW
{
  //switch case statement that will turn on pedestrian light based on what state we are in
  if (current_state_light_EW == Green) // assume that ns is red while ew is green otherwise code sucks and we need to change something
  {//
    TR0 = 0; //turn off timer 0 
    timer_high = TH0; timer_low = TL0; //save
    delay(1); // delay 1 second then go to yellow
    current_state_light_EW = Yellow; outputHandler();
    delay(2); //delay for 1 s and turn to red
    current_state_light_EW = Red; current_state_light_NS = Green; outputHandler(); // this is when this traffic light turns green
    
    pedLightNS = 1; //parallel direction
    
    // display on LCD
    String("Seconds left for NS : \n\n\r");
    
    String("6\n\r"); delay(1);
    String("5\n\r"); delay(1);
    String("4\n\r"); delay(1);
    String("3\n\r"); delay(1);
    String("2\n\r"); delay(1);
    String("1\n\r"); delay(1);
    
    pedLightNS = 0;
    current_state_light_NS = Yellow; outputHandler();
    // Ped light blinking
    delay(1); pedLightNS = 1;
    delay(1); pedLightNS = 0;
    String("STOP\n\n\r");
    // current state: NS is Yellow, EW is Red
    lightHandler(); outputHandler();
    TH0 = timer_high; TL0 = timer_low; //load
    TR0 = 1; //turn on timer 0
  }
}




 void UART_init() //function to initialize the UART
{
	TMOD = 0x21; //timer 1, 8 bit auto reload mode
	TH1 = 0xFD; //load value for 9600 baud rate
	SCON = 0x50; //Mode 1, reception enable
	TR1 = 1; //starting timer 1

}

void transmit_data(char tx_data)
{
	SBUF = tx_data; //load char into SBUF register
	while (TI == 0); //waiting until stop bit transmit
	TI = 0;					//clearing TI flag
	

}

void String(char *str)
	
{
	int i;
	for (i = 0; str[i]!= 0; i++) //send each char of string till the NULL
	{
		transmit_data(str[i]); //Call transmit data function
	}

}


/*unsigned char receive_1_byte(void)
	
{
	unsigned char received_byte;
	while (RI==0); // wait to receive one byte from serial port
	received_byte = SBUF;
	RI = 0; 
	return received_byte;
	

}
*/
