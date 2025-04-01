#include <TimerOne.h>

#define BUTTON_PIN 2      // Gumb na digitalnom pinu 2 (INT0)
#define LED_RED 8         // LED dioda za vanjski prekid
#define LED_BLUE 9        // LED dioda za timer prekid
#define TEMP_SENSOR A0    // LM35 senzor na analognom pinu A0

volatile bool buttonPressed = false;  // Flag za gumb prekid
volatile bool timerEvent = false;     // Flag za timer prekid
volatile float temperature = 0;         // Globalna varijabla za temperaturu

void buttonISR() {
    buttonPressed = true;  // Postavi flag za gumb prekid
}

void timerISR() {
    timerEvent = true;  // Postavi flag za timer prekid
}

void setup() {
    Serial.begin(9600);
    
    pinMode(BUTTON_PIN, INPUT_PULLUP);  
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);  // Vanjski prekid

    Timer1.initialize(500000);  // Timer prekid svakih 500ms
    Timer1.attachInterrupt(timerISR);
}

void loop() {
    if (buttonPressed) {
        buttonPressed = false;  // Reset flag
        digitalWrite(LED_RED, HIGH);
        Serial.println("Gumb pritisnut! Visoki prioritet prekida!");
        delay(1500);
        digitalWrite(LED_RED, LOW);
    }

    if (timerEvent) {
        timerEvent = false;  // Reset flag
        const float BETA = 3950;
        int analogValue = analogRead(TEMP_SENSOR);
        temperature = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15; // Očitaj temperaturu
        digitalWrite(LED_BLUE, HIGH);
        Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.println(" °C");
        delay(1500);
        digitalWrite(LED_BLUE, LOW);
    }
}
