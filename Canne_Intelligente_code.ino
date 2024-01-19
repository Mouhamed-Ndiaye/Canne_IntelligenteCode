const int pirPin = 27;       // Broche GPIO où le capteur PIR est connecté
const int ultrasonTrig = 12; // Broche GPIO du signal de déclenchement de l'ultrason
const int ultrasonEcho = 13; // Broche GPIO du signal de retour de l'ultrason
const int buzzerPin = 14;    // Broche GPIO où le buzzer est connecté

int previousMotionState = LOW; // État précédent du mouvement

void setup() {
    Serial.begin(115200);
    pinMode(pirPin, INPUT);
    pinMode(ultrasonTrig, OUTPUT);
    pinMode(ultrasonEcho, INPUT);
    pinMode(buzzerPin, OUTPUT);
}

void loop() {
    // Détection d'obstacle avec le capteur ultrason
    digitalWrite(ultrasonTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonTrig, LOW);

    int distance = pulseIn(ultrasonEcho, HIGH) * 0.034 / 2;

    if (distance < 50) { // Si la distance est inférieure à 50 cm, considérez cela comme un obstacle
        Serial.println("Obstacle détecté !");
        tone(buzzerPin, 2000); // Émet un son de 2000 Hz sur le buzzer
        delay(1000);           // Attendez une seconde pour le son
        noTone(buzzerPin);     // Arrêtez le son
        return; // Sortez de la boucle pour éviter la détection de mouvement
    }

    // Détection du mouvement avec le capteur PIR
    int motionDetected = digitalRead(pirPin);

    if (motionDetected == HIGH && previousMotionState == LOW) {
        Serial.println("Mouvement détecté !");
        tone(buzzerPin, 1000); // Émet un son de 1000 Hz sur le buzzer
        delay(1000);           // Attendez une seconde pour le son
        noTone(buzzerPin);     // Arrêtez le son
    }

    // Mettez à jour l'état précédent
    previousMotionState = motionDetected;

    delay(100); // Ajout d'un délai pour éviter les fausses détections
}
