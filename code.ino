#define BLYNK_TEMPLATE_ID "TMPL6zCvNsSj5"
#define BLYNK_TEMPLATE_NAME "Air Quality"
#define BLYNK_AUTH_TOKEN "use_you_auth_token"


#define BLYNK_PRINT Serial
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <BH1750.h>
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "use_you_auth_token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi Note 10S";
char pass[] = "12345678";

#define MQ2 34

int sensorValue = 0;
boolean state = false;


int DCMTOR = 15;
int IN1 = 2;
int motorSpeed = 0;

BH1750 lightMeter;

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(MQ2, INPUT);
  pinMode(IN1, OUTPUT);
  digitalWrite(IN1, HIGH);
  
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));
  // pinMode(V3, OUTPUT);
  // pinMode(V4, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 //  pinMode(buz, OUTPUT);

  // pinMode(12, HIGH);
  // pinMode(14, HIGH);
  // pinMode(9, HIGH);


  timer.setInterval(1000L, sendUptime);
}

void sendUptime()
{
  

  sensorValue = analogRead(MQ2);
  Blynk.virtualWrite(V0, sensorValue);
  Serial.println(sensorValue);

  if (sensorValue > 490)
  {
    Blynk.logEvent("polution_alert");
    //digitalWrite(buz,HIGH);
  }
  

  //light sensor  

  float lux = lightMeter.readLightLevel();
  Blynk.virtualWrite(V2, lux);
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);

  if(lux < 1000.00)
  {
    Blynk.logEvent("lightdamage");
  }



}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1) {
  int data = param.asInt();
  int motorSpeed = map(data,  0, 4095, 0, 255);
  analogWrite(DCMTOR,motorSpeed);
  delay(150);
  }


