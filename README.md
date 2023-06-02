# DIGITAL THERMOSTAT
## Design and simulation of digital thermostat(vyorius Embedded Test)
To complete this task i used atmega32 microcontroller for simulation purpose proteus vsm was used,the following file will have description of designing steps for programming i used microchipstudio ide.
atmega 32 is 8 bit microcontroller part of AVR family equiped with 32 kb flash, risc architecture also with 32 i/o pins and many more features made a suitable choice for this application, attiny 424 or similar microcontrollers and similar microcontrollers can also be used along with lcd drivers. but for simplicity i used atmega 32.
following were the requirements of the task:
-**programming language**:c/c++
-**Temperature Simulation**:build a function give random temperature values that can be used as different sensor values
-**User interaction**: interface allowing user to set temperature
-**Control logic**: controlling motor tu run dc motor for cooling purpose and switching on realy tu turn heater on. The duration ,speed and selection of device depends on desired temperature and current temperature
-**Feedback Display**: interface 16x2 lcd to display current and desired temperature.
the details of accomplishment of each requirement is described below:
###Temperature simulation algorithm

```
***C CODE***
float simulated_temperature(float min_change, float max_change,float current_temperature)
{
	float change = ((float)rand() / RAND_MAX) * (max_change - min_change) + min_change;
	return current_temperature + change;
}
...
void main()
{
float Tmax=40;
float Tmin = 10;
float max_change=5;
flaot min_change=-5;
...
while(1)
{
float current_temp=((float)rand() / RAND_MAX) * (Tmax - Tmin) + Tmin;
Sensor_1= simulated_temperature(min_change,max_change,current_temp);
Sensor_2= simulated_temperature(min_change,max_change,current_temp);
float avg_temp= (sensor_1+sensor_2)/2;
..
}
}
```
in this task i used simulated temperature that returns random temperature values which is utilized as various sensor reading and used as temperature of surroundings in the project althoug for practical purpose multiple lm35 temperature sensors  can be used whose readings can be extracted by averaging finally giving us the avg temperature of surroundings 
### User interface:
two push buttons are interfaced with one to increase the temperature and other to decrease the temperature pressing the push button incremets the count value that is used to set the desired temperature bu the user:

```
void main()
{ 
..
DDRD=0x00;
PORTD=0xff;
int c=20
...
while(1)
{
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
}
}
```
in this algorithm the count value is set to minimum of 20 (can be modified according to our functionality, port d is set to input mode pull up registers are enabled when push button is pressesed 0 is detected in that pin and count value is increased or decreased accordingly.
### CONTROL LOGIC
for controlling the temperature dc moror along with relay is interfaced relay can be used to turn the heater on whenever the desired temperature is more than the current temperature and dc motor will will be turned on whenever the desired temperature is less than current temperatiure the speed of motor is controlled using timer
whose puwm signal depeneds proportinally to the error between desired and current temperature
:
```
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
	    OCR0 = (error*kp);	/* Read ADC and map it into 0-255 to write in OCR0 register */
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
void main()
{
DDRC =Oxff;
DDRB=0xff;
TCNT0 = 0;			/* Set timer0 count zero */
TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);/* Set Fast PWM with Fosc/64 Timer0 clock */
   
   while()
   {
   ..
   temp_control(c,temp);
   }
}
```
### feedback and display:
for feedback temperature is being constantly meadured and updated along with calculation of error between present and desired temperature also for display 16x2 lcd is used to print current as well as desired display
### simulation:
proteus simulation:

<img width="422" alt="Screenshot 2023-06-02 175023" src="https://github.com/kanikaarya262/digital-thermostat/assets/93133854/113d5341-da21-40b3-ba2e-5361efa65882">
