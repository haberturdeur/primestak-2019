#include <Arduino.h>
#include "pins.h"
#include "periferie.h"
#include <Servo.h>

const int potvalues1[POCET_HODNOT_POT] = {129, 518, 899};
const int potvalues2[POCET_HODNOT_POT] = {147, 497, 887};

pot Ciselnik1(POT1, potvalues1, 40);
pot Ciselnik2(POT2, potvalues2, 40);

int heslo[2] = {1,1};

void setup()
{
  nastav_zamek();
  nastav_tlacitka();
  nastav_ledky();
  Serial.begin(9600);
}

void loop()
{
  if (je_zmacknute_tlacitko(tlacitko1))
  {
    rozsvit(L_Y);
  }
  else
  {
    zhasni(L_Y);
  }
  // if (je_zmacknute_tlacitko(tlacitko2))
  // {
  //   odemkni();
  // }
  // else
  // {
  //   zamkni();
  // }

  if((Ciselnik1.getValue()==1)&&(Ciselnik2.getValue()==1)){
    odemkni();
  }else{
    zamkni();
  }

  Serial.println(Ciselnik1.getValue());
  Serial.println(Ciselnik2.getValue());
  Serial.println("-------------------");
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  Serial.println("-------------------");
}
