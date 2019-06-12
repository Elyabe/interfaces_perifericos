#include "DHT.h"

#define DHTPIN A1 // o sensor dht11 foi conectado ao pino A1 no nosso tutorial
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
Serial.println("DHTxx test!");
dht.begin();
}

void loop() 
{
float umidade = dht.readHumidity();
float temperatura = dht.readTemperature();
// Se as variáveis temperatura e umidade não forem valores válidos, acusará falha de leitura.
if (isnan(temperatura) || isnan(umidade)) 
{
Serial.println("Falha na leitura do dht11...");
} 
else 
{

//Imprime os dados no monitor serial
Serial.print("Umidade: ");
Serial.print(umidade);
Serial.print(" %t"); //quebra de linha
Serial.print("Temperatura: ");
Serial.print(temperatura);
Serial.println(" °C");

if ( umidade >= 90 )
{ digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
}
}
