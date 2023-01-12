#include<SoftwareSerial.h>
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>
SoftwareSerial mySerial(D1,D2); //rx, Tx pins


//Enter your wifi name and password
const char* ssid = "abcd";
const char* password = "abcd123"; 

int slot;

WiFiClient client;

unsigned long myChannelNumber = 1962315; //Your Channel Number
const char * myWriteAPIKey = "ESXG666I8VIOMCG3";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //to begin hardware pins
  mySerial.begin(9600); //beginning serial pins with a baud rate of 9600...transfering data

  Serial.print("Connect to wifi ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while(WiFi.status()!=WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

   Serial.println("WiFi connected successfully");
   Serial.print("NODEMCU IP Address: ");
   Serial.println(WiFi.localIP());
    ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  String msg = mySerial.readStringUntil('\r');
  Serial.println(msg);
  slot = msg.toInt();
  
  ThingSpeak.writeField(myChannelNumber,1,msg,myWriteAPIKey); //update in thingspeak

  delay(100);
}
