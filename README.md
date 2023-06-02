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
