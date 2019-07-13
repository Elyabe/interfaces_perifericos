#include "DHT.h"
#include <SD.h>
#include <SPI.h>
#include <Servo.h>

// Pino A1
#define DHTPIN A1 
#define DHTTYPE DHT11
// Porta Digital PWM 6 
#define SERVO 6 

// Limiar temperatura para mover servo
#define LIMIAR_UMIDADE 60

DHT dht(DHTPIN, DHTTYPE);

// Variável Servo
Servo servo; 


// Posição Servo
int pos; 
File arquivo;
String msg;
float temp, umid;

void setup() {
  servo.attach(SERVO);
  servo.write(0);
  
  Serial.begin(115200);
  delay(500);

  dht.begin();  
}

void loop() 
{
    
    temp = dht.readTemperature();
    umid = dht.readHumidity();
    msg = temp + String(" ") + umid;
    
    Serial.println( msg ); 
    

    if ( umid >= LIMIAR_UMIDADE )
    {
        for(pos = 0; pos < 180; pos++)
        {
          servo.write(pos);
          delay(5);
        }
        
      delay(5);
      
      for(pos = 180; pos >= 0; pos--)
      {
        servo.write(pos);
        delay(5);
      }
      
    }
    
}
