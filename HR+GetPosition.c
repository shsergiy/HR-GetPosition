#include <msp430.h>

#define ROTATE_RESET	0
#define ROTATE_0		600
#define ROTATE_45       675
#define ROTATE_90		1650
#define ROTATE_130		1950
#define ROTATE_180		2700

#define servo_rotate(arg1) \
	for (i=0; i<30; i++) {	\
		P1OUT |= BIT5;		\
		__delay_cycles(arg1);	\
		P1OUT &= ~BIT5;			\
		__delay_cycles(20000);	\
	}

int i;

int read_distance_sensor_cm()
{
    int echo_pulse_duration;
    int distance;

    P1OUT |= BIT1;
    __delay_cycles(20);
    P1OUT &= ~BIT1;

    while ((P1IN & BIT2) == 0);
    TA1R = 0;
    while ((P1IN & BIT2) > 0);
    echo_pulse_duration = TA1R;
    distance = 0.017 * echo_pulse_duration;
    return distance;
}

void Find_Position()
{
	   if (read_distance_sensor_cm() < 50)
	   {
		   while(read_distance_sensor_cm()<50)
	        	P1OUT |= BIT0;

	   }
	        else
	        {
	        	P1OUT &= ~BIT0;
	        }

}

int main()
{

    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = 0b00000011 | BIT5;

    TA1CTL = TASSEL_2 + ID_0 + MC_2;


    while(1)
    {	servo_rotate(ROTATE_0);
    	Find_Position();
    	servo_rotate(ROTATE_45);
    	Find_Position();
    	servo_rotate(ROTATE_90);
    	Find_Position();
    	servo_rotate(ROTATE_130);
    	Find_Position();
    	servo_rotate(ROTATE_180);
	    Find_Position();

    }
}

