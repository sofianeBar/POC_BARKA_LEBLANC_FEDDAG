#include <ESP32Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "driver/rtc_io.h"

#define PIN_SG90 23    // Broche de sortie utilisée pour le servomoteur
#define PIN_BUZZER 5   // Broche du buzzer

// Déclaration du servomoteur
Servo sg90;

// Déclaration du pavé numérique
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'C','D','E','F'},
  {'B','9','6','3'},
  {'0','8','5','2'},
  {'A','7','4','1'}
};

byte rowPins[ROWS] = {26, 25, 33, 32}; 
byte colPins[COLS] = {13, 12, 14, 27}; 

// Créer une instance du pavé numérique
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Variable pour stocker la séquence de touches
String inputCode = "";
const String secretCode = "1111";  // Le code secret
int attemptCount = 0;               // Compteur de tentatives

// Créer une instance de l'écran LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresse I2C de l'écran

void setup() {
  // Initialisation du servomoteur
  sg90.setPeriodHertz(50); // Fréquence PWM pour le SG90
  sg90.attach(PIN_SG90, 500, 2400); // Largeur d'impulsion minimale et maximale (µs) pour le SG90

  // Initialisation du port série pour le débogage
  Serial.begin(9600);

  // Initialisation du buzzer
  pinMode(PIN_BUZZER, OUTPUT); // Configure la broche du buzzer comme une sortie
  digitalWrite(PIN_BUZZER, LOW); // Assure que le buzzer est éteint au départ

  // Initialisation de l'écran LCD
  lcd.init();                   // Initialiser l'écran LCD
  lcd.backlight();             // Allumer le rétroéclairage
  lcd.setCursor(0, 0);         // Positionner le curseur à la première ligne
  lcd.print("Tentatives: 0");  // Afficher le nombre de tentatives
}

void enterDeepSleep() {
  Serial.println("Entrée en mode deep sleep...");
  // Configurer le deep sleep pour 10 secondes
  esp_sleep_enable_timer_wakeup(10 * 1000000); // 10 secondes
  // Désactiver le servomoteur et le buzzer pour économiser de l'énergie
  sg90.detach();
  digitalWrite(PIN_BUZZER, LOW);
  lcd.noBacklight(); // Éteindre le rétroéclairage
  esp_deep_sleep_start(); // Mettre l'ESP32 en deep sleep
}

void loop() {
  // Lire les touches du pavé numérique
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print("Touche pressée : ");
    Serial.println(customKey);  // Affiche la touche pressée dans le moniteur série
    inputCode += customKey;     // Ajoute la touche au code entré

    // Si la longueur du code atteint 4
    if (inputCode.length() == 4) {
      // Vérifier si le code secret "1111" est entré
      if (inputCode == secretCode) {
        Serial.println("Code correct, activation du servomoteur!");

        // Faire bouger le servomoteur
        // Rotation de 0 à 180°
        for (int pos = 0; pos <= 180; pos += 1) {
          sg90.write(pos);
          delay(10);  // Délai pour un mouvement en douceur
        }
        // Rotation de 180° à 0°
        for (int pos = 180; pos >= 0; pos -= 1) {
          sg90.write(pos);
          delay(10);  // Délai pour un mouvement en douceur
        }

        // Réinitialiser le code après l'activation
        inputCode = "";
        
        // Afficher "COFFRE OUVERT" sur l'écran LCD
        lcd.clear();  // Effacer l'écran
        lcd.setCursor(0, 0);
        lcd.print("COFFRE OUVERT");

        // Éteindre le buzzer
        digitalWrite(PIN_BUZZER, LOW);

        // Réinitialiser le compteur d'essai et mettre à jour l'affichage
        attemptCount = 0; // Réinitialiser le compteur
        lcd.setCursor(0, 1); // Positionner le curseur à la deuxième ligne
        lcd.print("Tentatives: 0   "); // Effacer et réinitialiser l'affichage

      } else {
        Serial.println("Code incorrect !");
        
        // Incrémenter le compteur de tentatives
        attemptCount++;
        
        // Afficher le nombre de tentatives sur l'écran LCD
        lcd.setCursor(0, 0);
        lcd.print("Tentatives: "); // Afficher "Tentatives: "
        lcd.print(attemptCount);   // Afficher le nombre d'essais
        lcd.print("   ");          // Espaces pour effacer les anciens chiffres si besoin
        
        // Activer le buzzer pendant 3 secondes
        digitalWrite(PIN_BUZZER, HIGH); // Active le buzzer
        delay(3000);                     // Garde le buzzer activé pendant 3 secondes
        digitalWrite(PIN_BUZZER, LOW);  // Désactive le buzzer
        
        // Réinitialiser le code après une tentative
        inputCode = "";
      }
    }
    
    // Si aucune touche n'est pressée pendant 10 secondes, entrer en deep sleep
    delay(10000); // Délai pour détecter l'inactivité
    enterDeepSleep(); // Entrer en mode deep sleep
  }
}
