#include <TimerOne.h>

#define BUTTON_HIGH 2    // Tipka - visoki prioritet (INT0)
#define BUTTON_MED 3     // Tipka - srednji prioritet (INT1)
#define BUTTON_LOW 4     // Tipka - niski prioritet
#define LED_HIGH 8       // LED za tipku visokog prioriteta
#define LED_MED 9        // LED za tipku srednjeg prioriteta
#define LED_LOW 10       // LED za tipku niskog prioriteta
#define LED_DIST 11      // LED indikator za udaljenost

#define TRIG_PIN 5       // HC-SR04 Trigger pin
#define ECHO_PIN 6       // HC-SR04 Echo pin

volatile bool buttonHighPressed = false;
volatile bool buttonMedPressed = false;
volatile bool timerEvent = false;

long duration;
float distance;

void buttonHighISR() {
    buttonHighPressed = true;
}

void buttonMedISR() {
    buttonMedPressed = true;
}

void timerISR() {
    timerEvent = true;
}

void setup() {
    Serial.begin(9600);
    
    pinMode(BUTTON_HIGH, INPUT_PULLUP);
    pinMode(BUTTON_MED, INPUT_PULLUP);
    pinMode(BUTTON_LOW, INPUT_PULLUP);
    
    pinMode(LED_HIGH, OUTPUT);
    pinMode(LED_MED, OUTPUT);
    pinMode(LED_LOW, OUTPUT);
    pinMode(LED_DIST, OUTPUT);
    
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(BUTTON_HIGH), buttonHighISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_MED), buttonMedISR, FALLING);
    
    Timer1.initialize(1000000); // 1 sekunda
    Timer1.attachInterrupt(timerISR);
}

void loop() {
    // Visoki prioritet (prekid)
    if (buttonHighPressed) {
        buttonHighPressed = false;
        digitalWrite(LED_HIGH, HIGH);
        Serial.println("Visoki prioritet prekida!");
        delay(500);
        digitalWrite(LED_HIGH, LOW);
    }

    // Srednji prioritet (prekid)
    if (buttonMedPressed) {
        buttonMedPressed = false;
        digitalWrite(LED_MED, HIGH);
        Serial.println("Srednji prioritet prekida!");
        delay(500);
        digitalWrite(LED_MED, LOW);
    }

    // Niski prioritet (polling)
    if (digitalRead(BUTTON_LOW) == LOW) {  // Ručno provjeravamo stanje tipke
        digitalWrite(LED_LOW, HIGH);
        Serial.println("Niski prioritet prekida!");
        delay(500);
        digitalWrite(LED_LOW, LOW);
    }

    // Timer prekid svakih 1 sekundu
    if (timerEvent) {
        timerEvent = false;
        measureDistance();
        Serial.print("Udaljenost: ");
        Serial.print(distance);
        Serial.println(" cm");
        if (distance < 10) {
            digitalWrite(LED_DIST, HIGH);
        } else {
            digitalWrite(LED_DIST, LOW);
        }
    }
}

void measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
}