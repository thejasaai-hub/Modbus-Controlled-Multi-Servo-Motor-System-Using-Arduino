#include<ModbusRtu.h>       //Library for using Modbus in Arduino
#include <Servo.h>          //Library for using Servo Motor
Servo servo;                //Initilize servo object for class Servo
Servo servo1;                
Servo servo2;                        
Servo servo3;
Modbus bus;                          //Define Object bus for class modbus 

uint16_t modbus_array[] = {0,0,0,0};    //Array initilized with four 0 values

void setup()
{
  servo.attach(6);                //Servo PWM pin 6
  servo1.attach(9);
  servo2.attach(10);               
  servo3.attach(11);
  
  bus = Modbus(2,1,4);            //Modbus slave ID as 1 and 1 connected via RS-485 and 4 connected to DE & RE pin of RS-485 Module 

  bus.begin(9600);                //Modbus slave baudrate at 9600
}
void loop()
{
  bus.poll(modbus_array,sizeof(modbus_array)/sizeof(modbus_array[0]));       //Used to receive or write value from Master 
  int pwm = modbus_array[0]; //Depends upon value in modbus_array[1] written by Master Modbus
  int pwm1= modbus_array[1];
  int pwm2= modbus_array[2]; 
  int pwm3= modbus_array[3];
  servo.write(pwm);          //Write Received value (0 to 180) from Modbus Master
  servo1.write(pwm1); 
  servo2.write(pwm2); 
  servo3.write(pwm3); 
  delay(200); 
}

