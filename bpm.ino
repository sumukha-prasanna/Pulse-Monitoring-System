#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>     

const int buzzer = 11;
const int PulseWire = 0;       
const int LED13 = 13;         
int Threshold = 550;           
                               
PulseSensorPlayground pulseSensor;  


void setup() {   

  Serial.begin(9600);          

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       
  pulseSensor.setThreshold(Threshold);   

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");    
  }

  pinMode(buzzer,OUTPUT);
}


int myBPM;
void loop() {

 myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
  if((myBPM>10 && myBPM<50) || myBPM>120){
    analogWrite(buzzer, 25);
    delay(1000);                     
    analogWrite(buzzer, 0);  
    delay(1000);  
  }

}

  delay(100);                   
}

  
