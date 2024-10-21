#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define buttons pins as constants.
#define BTN1 5
#define BTN2 4
#define BTN3 3
#define BTN4 2

// Definine constants of LED pins.
#define LS 6    // PWM pin for the pulsing RED LED.
#define L1 11   // green leds.
#define L2 10
#define L3 9
#define L4 8

// Pin used to read the potentiometer.
#define POT A0

// Define constants for the states.
#define STARTUP 0
#define DEEP_SLEEP 1
#define PREPARE_ROUND 2
#define ROUND 3
#define ROUND_WIN 4
#define GAME_OVER 5

// Define the number of buttons and green leds (which actually are always the same number).
#define BUTTON_COUNT 4
#define LED_COUNT 4

// Constants used for the pulsing of the red led.
#define DEFAULT_FADE_AMOUNT 15
#define START_INTENSITY 0
#define MAX_INTENSITY 255
#define MIN_INTENSITY 0

// Time in milliseconds for the debounce.
#define DEBOUNCE_TIME 50

// Default time for the round in milliseconds.
#define ROUND_TIME 10000 


#endif // CONSTANTS_H