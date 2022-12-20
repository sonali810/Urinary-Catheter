
#include <Adafruit_NeoPixel.h> // plugin for the Neopixel library
int dataPin = 6; //what pin dose the LED data cable connect to on the board eg.D6
#define numberOfPixels  12 //how meny NeoPixels are on the Led strip
#define maximumBrightness 255 //the maximum brightness of the pixel is 255 
Adafruit_NeoPixel ledRing = Adafruit_NeoPixel(numberOfPixels, dataPin); //over here we are telling the controller that we have a "ledRing" 
                                                                         
/* Change these values based on your calibration values */
int lowerThreshold = 500;
int upperThreshold = 550;

// Sensor pins
#define sensorPower 7
#define sensorPin A0
#define trigPin 13
#define echoPin 12

const int buzzer=11;

// Value for storing water level
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  ledRing.begin();
  pinMode(buzzer, OUTPUT);
}

void loop() {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * (.034/2);
  Serial.println(distance);
  
  int level = readSensor();
 
  if (level == 0) {
    Serial.println("Water Level: Empty");
    Green(); 
  }
  else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    Green(); 
  }
  else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    Yellow();
  }
  else if (level > upperThreshold && distance > 10) {
    Serial.println("Water Level: High");
    Red();
    digitalWrite(buzzer, HIGH);   // turn the alarm on (HIGH is the voltage level)
    delay(1000); // wait for a second
    digitalWrite(buzzer, LOW); // turn the LED off by making the voltage LOW
    delay(1000);
  }

  else if(level > upperThreshold && distance >= 0 && distance <= 10) {
      Red();     
  }
 
  delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  Serial.println(val);
  digitalWrite(sensorPower, LOW);
  return val;
}

void Green()// this is the "customLight" method, think of it as some type of box that groups tasks together
  {
    setLightsToColour(0,10,0);// this is calling the "SetLightsToColour" method,it needs to know how much Red ,Blue and Green Light 
  } 
  
void Yellow()// this is the "customLight" method, think of it as some type of box that groups tasks together
  {
    setLightsToColour(10,3,0);// this is calling the "SetLightsToColour" method,it needs to know how much Red ,Blue and Green Light 
  }   

void Red()// this is the "customLight" method, think of it as some type of box that groups tasks together
  {
    setLightsToColour(10,0,0);// this is calling the "SetLightsToColour" method,it needs to know how much Red ,Blue and Green Light 
  }  
   
void setLightsToColour(int red, int green, int blue)//this is the "setLightsToColour" method, it needs 3 values for (red,green,blue) so it knows how much to add to each one
  {
     for (uint8_t i = 0; i < numberOfPixels; i++)// this makes sure that every pixel gets its colour changed from 0 to "numberOfPixels"
     {
        ledRing.setPixelColor(i, ledRing.Color(red, green, blue));// this is telling the led pixel to change its red green blue to what you have given "setLightToColour()" method
     }
     ledRing.show();// this tells the ledRing to show the changes 
  }
