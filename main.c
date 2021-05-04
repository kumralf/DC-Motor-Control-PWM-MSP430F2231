#include <msp430g2231.h>

#define BUTTON1      BIT4 // Port 1.3
#define BUTTON2      BIT5
#define PWM          BIT2 // Port 1.0

void main (void) {

    // Watchdog setup
    WDTCTL = WDTPW + WDTHOLD;

    // LED initial setup
    P1DIR |= PWM;               
    P1SEL |= PWM; //Select pin 1.2 as our PWM output
    
    // Button setup
    P1DIR &= ~BUTTON1;               // button is an input
    P1OUT |= BUTTON1;                // pull-up resistor
    P1REN |= BUTTON1;                // resistor enabled

    P1DIR &= ~BUTTON2;               // button is an input
    P1OUT |= BUTTON2;                // pull-up resistor
    P1REN |= BUTTON2;                // resistor enabled
    
      
    TACCR0 = 20000;
   TACCR1 = 10000;
   TACCTL1 = OUTMOD_7;
   TACTL = TASSEL_2 + MC_1 + ID_0;
    while(1)
    {
        if((P1IN & BUTTON1)!=BUTTON1)
        {
      TACCR1 += 1000;
      if(TACCR1 >= 19000) TACCR1 = 19000;
      while((P1IN & BUTTON1)!=BUTTON1);
        }
        
        else if((P1IN & BUTTON2)!=BUTTON2)
        {  
        TACCR1 -=1000;
      if(TACCR1 <= 1000) TACCR1 = 1000;
      while((P1IN & BUTTON2)!=BUTTON2);
        }
        
    }
}