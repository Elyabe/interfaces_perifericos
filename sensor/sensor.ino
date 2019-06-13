#include "DHT.h"
#include <SD.h>
#include <SPI.h>
#include <Servo.h>

// Não utilizamos mais
//#include <DueFlashStorage.h>

// Pino A1
#define DHTPIN A1 
#define DHTTYPE DHT11
// Porta Digital PWM 6 
#define SERVO 6 

DHT dht(DHTPIN, DHTTYPE);
Servo s; // Variável Servo
DueFlashStorage dueFlashStorage;

int pos; // Posição Servo
File arquivo;

// The struct of the configuration.
struct Amostra {
  float temperatura[100];
  float umidade[100];
  int id;
//  int32_t bigInteger;
//  char* message;
//  char c;
};

// initialize one struct
Amostra amostras[2];
int i = 0, x = 0;

void setup() {
  s.attach(SERVO);
  s.write(0);
  
  Serial.begin(115200);
  delay(500);

  dht.begin();  
}


String msg;

void loop() 
{
    
    if ( i < 100 )
      x = 0;
    else
    { 
      i = 0;
      x = 1;
     }
    
    amostras[ x ].temperatura[i] = dht.readTemperature();   
    amostras[ x ].umidade[i] = dht.readHumidity();

    msg = amostras[ x ].temperatura[i] + String(" ") +  amostras[ x ].umidade[i];
    Serial.println( msg ); 
    

    if ( amostras[ x ].umidade[i] >= 70 )
    {
        for(pos = 0; pos < 90; pos++)
        {
          s.write(pos);
        delay(5);
        }
      delay(5);
        for(pos = 90; pos >= 0; pos--)
        {
          s.write(pos);
          delay(5);
        }
    }
    
}
