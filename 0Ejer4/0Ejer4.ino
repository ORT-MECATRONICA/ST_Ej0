#include <SPI.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define DHTTYPE DHT11
#define DHTPIN 23
DHT dht(DHTPIN, DHTTYPE);
#define PIN_BTN1 34
#define PIN_BTN2 35
#define ANCHO_P 128
#define ALTO_P 64

Adafruit_SSD1306 display(ANCHO_P, ALTO_P, &Wire, -1);

int estado;
#define PANTALLA1 0
#define COMPROBACION_BTN_1 1
#define PANTALLA2 2
#define COMPROBACION_BTN_2 3
#define COMPROBACION_BTN_SUMA 4
#define COMPROBACION_BTN_RESTA 5
float temp;
int VU = 27;
int lecturaBtn1;
int lecturaBtn2;
int flag;
long tiempoActual;

void setup() {
  Serial.begin (9600);
  dht.begin(); //inicializo el sensor de temperatura
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Inicializamos el oled
  display.clearDisplay(); // Borrar imagen en el OLED

  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
  flag = 1;
  estado = PANTALLA1;
}

void loop() {
  temp = dht.readTemperature(); //leemos la temperatura


  switch (estado) {
    case PANTALLA1:
      display.setTextSize(1); // Tamaño del texto
      display.setTextColor(WHITE); // Definir color del texto (WHITE-BLACK)
      display.setCursor(5, 25);
      display.println("VR:");
      display.setCursor(10, 25);
      display.println(temp);
      display.setCursor(5, 35);
      display.println("VU:"); // Escribimos en el buffer el texto con la posición (X,Y) en la pantalla
      display.setCursor(10, 35);
      display.println(VU);
      display.clearDisplay();

      if (digitalRead(PIN_BTN1) == 0 && digitalRead(PIN_BTN2) == 0) {
        estado = COMPROBACION_BTN_1;
        Serial.println(PANTALLA2);
      }
      break;
    case COMPROBACION_BTN_1:
      if (digitalRead(PIN_BTN1) == 1 && digitalRead(PIN_BTN2) == 1) {
        if (flag == 1) {
          estado = PANTALLA2;
          Serial.print("pantalla2");
          flag = 2;
        } else if (flag == 2) {
          estado = PANTALLA1;
          Serial.print("pantalla1");
          flag = 1;
        }
        Serial.print("pantalla2");
      }
      break;
    case PANTALLA2:
     if (digitalRead(PIN_BTN1) == 0 && digitalRead(PIN_BTN2) == 0) {
        estado = COMPROBACION_BTN_1;
      }
     if (digitalRead(PIN_BTN1) == 0){
      tiempoActual = millis();
      if (digitalRead(PIN_BTN1) == 0 && millis() - tiempoActual > 200) {
        estado = COMPROBACION_BTN_SUMA;
      }
     }
     if (digitalRead(PIN_BTN2) == 0) {
        tiempoActual = millis();
      if (digitalRead(PIN_BTN2) == 0 && millis() - tiempoActual > 200) {
        estado = COMPROBACION_BTN_RESTA;
      }
     }
      display.setCursor(5, 35);
      display.println("VU:"); // Escribimos en el buffer el texto con la posición (X,Y) en la pantalla
      display.setCursor(10, 35);
      display.println(VU);
      display.clearDisplay();

      
      break;
    /*case COMPROBACION_BTN_2:
        delay(10);
        if (digitalRead(PIN_BTN1) == 1 && digitalRead(PIN_BTN2) == 1) {
          estado = PANTALLA1;
        }
        break;*/
    case COMPROBACION_BTN_SUMA:
      if (digitalRead(PIN_BTN1) == 1) {
        VU = VU + 1;
        estado = PANTALLA2;
      }
      break;
    case COMPROBACION_BTN_RESTA:
      if (digitalRead(PIN_BTN2) == 1) {
        VU = VU - 1;
        estado = PANTALLA2;
      }
      break;
  }
  Serial.println(estado);
  //Serial.println(VU);
}
