#include <Arduino.h>

void round_game(int buttonPins[], int ledPins[]) {

    //Generazione numero casuale
    int userNumber = 0;
    randomSeed(micros());
    int random_number = rand() % 16; 

    bool flag = true;
    bool ledState[4] = {LOW, LOW, LOW, LOW}; 
    bool lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH};

    Serial.print("Numero casuale generato: ");
    Serial.println(random_number);

    while (flag == true) {
        userNumber = 0; 

        //controlla stato bottoni
        for (int i = 0; i < 4; i++) {
            int currentButtonState = digitalRead(buttonPins[i]);

            //transizione da HIGH a LOW e viceversa dei led
            if (currentButtonState == LOW && lastButtonState[i] == HIGH) {
                ledState[i] = !ledState[i];
                digitalWrite(ledPins[i], ledState[i]);
            }

            //aggiorna ultimo stato del bottone
            lastButtonState[i] = currentButtonState;
        }

        for (int i = 0; i < 4; i++) {
            if (ledState[i] == HIGH) {
                userNumber |= (1 << i);
            }
        }

        //controllo se il giocatore ha vinto
        if (userNumber == random_number) {
            flag = false;
        }

        delay(50);
    }
}