/*
 * DYNAMIC AUTONOMOUS EMERGENCY BRAKING RC CAR PROJECT
 * 
 * Designed, constructed, implemented by: Can ÖZCİVELEK
 * Start Date: 24/09/2018
 * This project was  designed to make a remote  controlled car  constantly scan the road ahead
 * and apply emergency braking  when it encounters an obstacle. It makes use  of an ultrasonic
 * sensor to measure distance ahead, a  Hall Effect sensor attached to one of the wheels along
 * with a  neodymium  magnet to measure the  RPM and sends  that data to the  micro-controller 
 * (Arduino UNO) and  determine when to stop. The braking distance dynamically varies based on
 * the speed.
 * 
*/

//Importing libraries
#include<Servo.h>


////START - VARIABLE DEFINITIONS////////////////////////
////////////////////////////////////////////////////////

//Variables & pin numbers for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;
long      duration;
int       distance;

//Variables for servo motor
Servo servo1;
float pos = 0.0;

//Variables for RPM calculation
volatile byte half_revolutions;
unsigned int  rpm;
unsigned long timeold;

////////////////////////////////////////////////////////
////END - VARIABLE DEFINITIONS//////////////////////////



////START - MAIN FUNCTION///////////////////////////////
////////////////////////////////////////////////////////
void setup()
{
    //Establishing serial connection through COM3 port
    Serial.begin(9600);

    //Variable settings for servo motor
    servo1.attach(5);           //Attaching servo motor to Arduino pin 5

    //Variable settings for the ultrasonic sensor
    pinMode(trigPin, OUTPUT);   //Sets the trigPin as an Output
    pinMode(echoPin, INPUT);    //Sets the echoPin as an Input

    //Initializing variables for RPM calculation
    half_revolutions  = 0;
    rpm               = 0;
    timeold           = 0;
}
////////////////////////////////////////////////////////
////END - MAIN FUNCTION/////////////////////////////////



////START - LOOP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////
void loop()
{
    ////START - MEASURE RPM/////////////////////////////
    //Initialize the intterrupt pin (Arduino digital pin 2)
    attachInterrupt(0, magnet_detect, RISING);
    if(half_revolutions >= 2)
    {   
        rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
        timeold = millis();
        half_revolutions = 0;
    }
    //Show calculated RPM on the serial monitor
    Serial.print("RPM: ");
    Serial.println(rpm, DEC);
    ////END - MEASURE RPM///////////////////////////////


    ////START - MEASURE DISTANCE////////////////////////
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance in cm
    distance = duration * 0.034 / 2;
    
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    ////END - MEASURE DISTANCE//////////////////////////
    

    ////START - If checks to decide when to apply brakes
    if(rpm >= 0 && rpm < 15 && distance < 35)
    {
        pos = 135;            //Hard Brake
        servo1.write(pos);    
        delay(3000);          //Wait for 3 seconds after brake
        rpm = 0;
        pos = 90;             //Release brakes
        servo1.write(pos);
    }

    else if(rpm >= 15 && rpm < 50 && distance < 40)
    {
        pos = 140;            //Hard Brake
        servo1.write(pos);    
        delay(3000);          //Wait for 3 seconds after brake
        rpm = 0;
        pos = 90;             //Release brakes
        servo1.write(pos);
    }

    else if(rpm >= 50 && rpm < 90 && distance < 80)
    {
        pos = 140;            //Hard Brake
        servo1.write(pos);    
        delay(3000);          //Wait for 3 seconds after brake
        rpm = 0;
        pos = 90;             //Release brakes
        servo1.write(pos);
    }

    else if(rpm >= 90 && distance < 100)
    {
        pos = 140;            //Hard Brake
        servo1.write(pos);    
        delay(3000);          //Wait for 3 seconds after brake
        rpm = 0;
        pos = 90;             //Release brakes
        servo1.write(pos);
    }
    ////END - If checks to decide when to apply brakes
}
////////////////////////////////////////////////////////
////END - LOOP FUNCTION/////////////////////////////////



////START - MAGNET DETECTION FUNCTION///////////////////
////////////////////////////////////////////////////////
//This function is called whenever a magnet/interrupt is detected by the sensor
void magnet_detect()
{
   half_revolutions++;
}
////////////////////////////////////////////////////////
////END - MAGNET DETECTION FUNCTION/////////////////////

/*----------MAGNET DETECTION FUNCTION - END------------*/












































