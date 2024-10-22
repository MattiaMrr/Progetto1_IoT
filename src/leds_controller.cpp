#include "leds_controller.h"
#include <Arduino.h>

// Used to pulse the red led.
int fadeAmount = DEFAULT_FADE_AMOUNT;
int currIntensity = START_INTENSITY;

void initLeds(int ledPins[])
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void turnOffLed(const int ledPin)
{
    digitalWrite(ledPin, LOW);
}

void turnOnLed(const int ledPin)
{
    digitalWrite(ledPin, HIGH);
}

void turnOnGreenLeds(int ledPins[])
{
    for (int i = 1; i < LED_COUNT; i++)
    {
        turnOnLed(ledPins[i]);
    }
}

void turnOffGreenLeds(int ledPins[])
{
    for (int i = 0; i < LED_COUNT; ++i)
    {
        turnOffLed(ledPins[i]);
    }
}

void turnOnRedLed()
{
    turnOnLed(LS);
}

void turnOffRedLed()
{
    turnOffLed(LS);
}

void pulseRedLed()
{
    analogWrite(LS, currIntensity);
    currIntensity += fadeAmount;
    if (currIntensity == 0 || currIntensity == 255)
    {
        fadeAmount = -fadeAmount;
    }
}

void resetBoard(int ledpins[])
{
    turnOffGreenLeds(ledpins);
    turnOffRedLed();
}

void showDifficulty(int difficulty, int ledPins[])
{
    turnOffGreenLeds(ledPins);
    for (int i = 0; i < difficulty; i++)
    {
        turnOnLed(ledPins[i]);
    }
}