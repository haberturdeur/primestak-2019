#pragma once
#include <Arduino.h>
#include "pins.h"
#include <Servo.h>

#define ZACATECNIK 1

#define SERVO_P S1
#define MIN 0
#define MAX 180
#define ZAMCENO 180
#define ODEMCENO 0
#define CAS_POHYBU_SERVA 150

#define POCET_HODNOT_POT 3

enum stav_LED : byte
{   
    NESVIT,
    SVIT,
    ZABLIKEJ,
    ERROR= 254, 
    READ = 255
};
static stav_LED state_now_r = NESVIT;
static stav_LED state_now_y = NESVIT;
static stav_LED state_now_g = NESVIT;
static stav_LED state_now_b = NESVIT;

bool zamknuto = 0;

Servo mojeservo;

class pot
{
private:
    int pin;

    int values[POCET_HODNOT_POT];
    int value;
    int tolerance;

public:
    int pom;
    pot(uint8_t p, const int v[POCET_HODNOT_POT], const int t);
    int getValue();
};

pot::pot(uint8_t p, const int v[POCET_HODNOT_POT], const int t)
{
    pin = p;
    tolerance = t;
    for (int i = 0; i < POCET_HODNOT_POT; i++)
    {
        values[i] = v[i];
    }
}

int pot::getValue()
{
    pom = analogRead(pin);
    int low;
    int high;
    value = -1;
    for (int i = 0; i < POCET_HODNOT_POT; i++)
    {
        low = values[i] - tolerance;
        high = values[i] + tolerance;
        if ((low < pom) && (high > pom))
        {
            value = i;
            //Serial.println(i);
        }
        // Serial.println(low);
        // Serial.println(high);
        // Serial.println("");
    }
    //Serial.println(value);
    return value;
}

void zablikej(uint8_t led)
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(100);
    }
}

void rozsvit(uint8_t led)
{
    digitalWrite(led, HIGH);
}
void zhasni(uint8_t led)
{
    digitalWrite(led, LOW);
}

bool je_zmacknute_tlacitko(uint8_t btn)
{
    return !digitalRead(btn);
}

void nastav_zamek()
{
    mojeservo.attach(SERVO_P, MIN, MAX);
    pinMode(SERVO_P, OUTPUT);
}
void nastav_tlacitka()
{
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
}
void nastav_ledky()
{
    pinMode(L_Y, OUTPUT);
    pinMode(L_G, OUTPUT);
    pinMode(L_R, OUTPUT);
}

stav_LED cervena_led(stav_LED state_to_set = READ)
{
    const byte led = L_R;
    switch (state_to_set)
    {
    case SVIT:
            digitalWrite(led, HIGH);
            state_now_r = SVIT;
        break;
    case NESVIT:
            digitalWrite(led, LOW);
            state_now_r = NESVIT;
        break;
    case ZABLIKEJ:
            for (int i = 0; i < 3; i++)
            {
                digitalWrite(led, HIGH);
                delay(50);
                digitalWrite(led, LOW);
                delay(100);
            }
            state_now_r = NESVIT;
        break;
    case READ:
            return state_now_r;
    default:
            return ERROR;
        break;
    }
    return state_now_r;
}

stav_LED zluta_led(stav_LED state_to_set = READ)
{
    const byte led = L_Y;
    switch (state_to_set)
    {
    case SVIT:
            digitalWrite(led, HIGH);
            state_now_y = SVIT;
        break;
    case NESVIT:
            digitalWrite(led, LOW);
            state_now_y = NESVIT;
        break;
    case ZABLIKEJ:
            for (int i = 0; i < 3; i++)
            {
                digitalWrite(led, HIGH);
                delay(50);
                digitalWrite(led, LOW);
                delay(100);
            }
            state_now_y = NESVIT;
        break;
    case READ:
            return state_now_y;
    default:
            return ERROR;
        break;
    }
    return state_now_y;
}

stav_LED zelena_led(stav_LED state_to_set = READ)
{
    const byte led = L_G;
    switch (state_to_set)
    {
    case SVIT:
            digitalWrite(led, HIGH);
            state_now_g = SVIT;
        break;
    case NESVIT:
            digitalWrite(led, LOW);
            state_now_g = NESVIT;
        break;
    case ZABLIKEJ:
            for (int i = 0; i < 3; i++)
            {
                digitalWrite(led, HIGH);
                delay(50);
                digitalWrite(led, LOW);
                delay(100);
            }
            state_now_g = NESVIT;
        break;
    case READ:
            return state_now_g;
    default:
            return ERROR;
        break;
    }
    return state_now_g;
}

stav_LED modra_led(stav_LED state_to_set = READ)
{
    const byte led = L_B;
    switch (state_to_set)
    {
    case SVIT:
            digitalWrite(led, HIGH);
            state_now_b = SVIT;
        break;
    case NESVIT:
            digitalWrite(led, LOW);
            state_now_b = NESVIT;
        break;
    case ZABLIKEJ:
            for (int i = 0; i < 3; i++)
            {
                digitalWrite(led, HIGH);
                delay(50);
                digitalWrite(led, LOW);
                delay(100);
            }
            state_now_b = NESVIT;
        break;
    case READ:
            return state_now_b;
    default:
            return ERROR;
        break;
    }
    return state_now_b;
}

void zamkni()
{
    if (ZACATECNIK)
    {
        if (je_zmacknute_tlacitko(SW3))
        {
            mojeservo.write(ZAMCENO);
            delay(CAS_POHYBU_SERVA);
            zamknuto = !zamknuto;
            rozsvit(L_G);
            Serial.println("zammceno");
        }
        else
        {
            zablikej(L_R);
        }
    }
    else
    {
        mojeservo.write(ZAMCENO);
        delay(CAS_POHYBU_SERVA);
        rozsvit(L_G);
    }
}

void odemkni()
{
    if (ZACATECNIK)
    {
        if (je_zmacknute_tlacitko(SW3))
        {
            mojeservo.write(ODEMCENO);
            delay(CAS_POHYBU_SERVA);
            zamknuto = !zamknuto;
            zhasni(L_G);
            Serial.println("odemceno");
        }
        else
        {
            zablikej(L_R);
        }
    }
    else
    {
        mojeservo.write(ODEMCENO);
        delay(CAS_POHYBU_SERVA);
        zhasni(L_G);
    }
}
