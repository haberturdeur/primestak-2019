#include <Arduino.h>
#include "pins.h"
#include "periferie.h"
#include <Servo.h>



const int potvalues1[11] = {};
const int potvalues2[11] = {};

pot Ciselnik1(POT1, potvalues1, 5);
pot Ciselnik2(POT2, potvalues2, 5);

void setup() {
  nastav_zamek();
  nastav_tlacitka();
  nastav_ledky();
}

void loop() {
  if(je_zmacknute_tlacitko(tlacitko1)){
    rozsvit(L_Y);
  }else{
    zhasni(L_Y);
  }
  if(je_zmacknute_tlacitko(tlacitko2)){
    odemkni();
  }else
  {
    zamkni();
  }
  
  
}