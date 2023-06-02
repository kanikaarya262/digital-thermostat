/*
 * thermostat.c
 *
 * Created: 01-06-2023 23:07:19
 * Author : Hp
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <util/delay.h>
#include <time.h>
#include "LCD16x2_4bit.h"

void temp_control(int desired_temp,int current_temp)
{
	float kp =3;//assuming for proportional controll;
	float kd=0;// can implement pid controll algortith for temp control
	float ki=0;
	if(desired_temp<current_temp)
	{
		PORTC=0x00;//ensure that heater is off
		int error=current_temp-desired_temp;
		PORTB = 0x0A;
					/* Else rotate DC motor Anticlockwise */
		//OCR0 = (error*kp);	/* Read ADC and map it into 0-255 to write in OCR0 register */
	}	
	else if(desired_temp>current_temp)
	{
		int error= desired_temp-current_temp;
		PORTC=0xff;//turn the relay on
	}	
	else
	{
		PORTC=0x00;
	}
	
}

void disp_num(int numb)            //displays number on LCD
{
	unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
	unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb

	if(numb<0)    {
		numb = -1*numb;          // Make number positive
		LCD_Char('-');   // Display a negative sign on LCD
	}
	TenthDigit = (numb/10);                    // Find out Tenth Digit

	if( TenthDigit != 0)                    // If it is zero, then don't display
	LCD_Char(TenthDigit+0x30);    // Make Char of TenthDigit and then display it on LCD
	UnitDigit = numb - TenthDigit*10;
	LCD_Char(UnitDigit+0x30);    // Make Char of UnitDigit and then display it on LCD
}


float simulated_temperature(float min_change, float max_change,float current_temperature)
{
	float change = ((float)rand() / RAND_MAX) * (max_change - min_change) + min_change;
	return current_temperature + change;
}
void main(void)
{
	DDRC=0xff;
	DDRD=0x00;
	PORTD=0xff;//ENABLE PULL UP
	float Tmax=40;
	float Tmin =10;
	float min_change = -5;
	float max_change = +5;
	srand(time(NULL)); 
	LCD_Init();
	int c = 20;
	DDRA = 0xFF;	
	//TCNT0 = 0;			/* Set timer0 count zero */
	//TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);/* Set Fast PWM with Fosc/64 Timer0 clock */
    /* Replace with your application code */
    while (1) 
    {
		float current_temp = ((float)rand() / RAND_MAX) * (Tmax - Tmin) + Tmin;
		float sensor1_temp=simulated_temperature(min_change,max_change,current_temp);
		float sensor2_temp=simulated_temperature(min_change,max_change,current_temp);
		float avg_temp=(sensor1_temp+sensor2_temp)/2;
		int temp = (int)avg_temp;
		LCD_String_xy(1,0,"current:");
		_delay_ms(1000);
		disp_num(temp);
		_delay_ms(1000);
		if (bit_is_clear(PIND,6))  //when button one  is pressed
		{
			if(c<40)
			{
				c++;
			}
			else
			{
				c=0;
			}
		}

		if (bit_is_clear(PIND,7))  // when button 2  is pressed
		{
			if (c>20)
			{
				c--; // increment integer ‘d’ by one if its less than 21
			}
			else
			{
				c=20;
			}
		}
		
		LCD_Command(0xC0);
		LCD_String_xy(2,0,"desired_temp: ");
		disp_num(c);
		_delay_ms(1000);
		temp_control(c,temp);
    }
}

