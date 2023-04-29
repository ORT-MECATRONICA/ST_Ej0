//Octavio Leven y Nicolás Golonbek

// Inclusion de librerias
#include <U8g2lib.h>

/* ----------------------------------------------------------------------------------------------------- */

// Definicion de constructores y variables globales

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/* ----------------------------------------------------------------------------------------------------- */
void  printBMP_OLED(void );


void setup() 
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
}
  
void loop() 
{
 printBMP_OLED();
    delay(2000);
}

void printBMP_OLED(void)
{
    float temp1,temp2,temp3,temp4;
    temp1=21.5;
    temp2=22.5;
    char stringtemp1[5];  
    char stringtemp2[5];
  u8g2.clearBuffer();          // clear the internal memory
    
    u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
    u8g2.drawStr(4,15,"Hola mundo");  // write something to the internal memory
    
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
   

   u8g2.sendBuffer();      // transfer internal memory to the display


}
