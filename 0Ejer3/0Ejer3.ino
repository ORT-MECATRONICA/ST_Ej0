//Octavio Levan y Nicolás Golonbek

#include "DHT.h"
#include <Adafruit_Sensor.h>


#define DHTTYPE DHT11
#define PIN_DHT 23
DHT dht(PIN_DHT, DHTTYPE);

float lecturaHumedad;
#define PIN_RELE 18//seteo el pin del rele

void setup() {
  dht.begin(); //inicializo el sensor de temperatura
  pinMode(PIN_RELE, OUTPUT); //configuro el pin del rele como output
  Serial.begin(9600);
}

void loop() {
  lecturaHumedad = dht.readTemperature(); //leemos la temperatura
  Serial.println(lecturaHumedad);
  
  if (lecturaHumedad > 28){  //comprovamos si la temperatura supera el valor humbral
    digitalWrite(PIN_RELE, HIGH);   //prendemos el rele
   Serial.print("RELAY ON");
  }
  if (lecturaHumedad < 28){  //comprovamos si la temperatura supera el valor humbral
    digitalWrite(PIN_RELE, LOW);   //apago el rele
  }
}
