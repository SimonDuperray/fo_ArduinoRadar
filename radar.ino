#include <LiquidCrystal.h> // on inclut la bibliothèque nous permettant d'écrire sur l'écran lcd

#define buzzer 8 // on précise que le buzzer est branché sur le pin 8 de l'Arduino
#define led 9 // on précise que la led est branchée sur le pin 9 de l'Arduino
#define echoPin 10 // on précise que le pin echo du module à ulrasons est branché sur le pin 10 de l'Arduino
#define trigPin 11 // on précise que le pin trig du module à ulrasons est branché sur le pin 11 de l'Arduino

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // on définit les pins sur lesquels sont branchés l'écran lcd

void setup() { // on initialise nos données dans la boucle setup qui se lance une seule fois
  Serial.begin(9600); // on initialise la liaison série pour afficher des valeurs sur le moniteur série
  //9600 est un flux représentant le nombre d'infos transmis en une seconde (ici 9600 bauds)
  pinMode(led, OUTPUT); // on déclare notre led en tant que sortie
  pinMode(echoPin, INPUT); // on déclare le pin echo en tant qu'entrée...
  pinMode(trigPin, OUTPUT); // ... et le pin trig en tant que sortie
  lcd.begin(16, 2); // on déclare le type d'écran que l'on va utiliser (ici 16x2)
}

void loop() { // la boucle void loop se répétera à l'infini tant que la carte est sous tension
  long duree, distance; // on déclare les variables qui contiendront les données reçues par le capteur à ultrasons
  digitalWrite(trigPin, LOW); // on éteint le pin trig
  delayMicroseconds(2);  // on attend 2 µs
  digitalWrite(trigPin, HIGH); // on envoie une savle d'ultrasons pendant 10 µs
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); // puis on éteint le pin
  
  // On calcule le temps pour l'aller retour du signal
  duree = pulseIn(echoPin, HIGH);
  distance = duree*340/(2*10000);
  Serial.println(distance); // on affiche (au début du projet) la distance sur le moniteur série pour s'assurer du bon fonctionnement du capteur
  delay(50); 

  // On affiche la distance sur l'écran lcd
  lcd.setCursor(1, 0);
  lcd.print("Radar de recul");
  lcd.setCursor(0, 1);
  lcd.print("Dist :");
  lcd.setCursor(7, 1);
  lcd.print(distance);
  lcd.setCursor(14, 1);
  lcd.print("cm");
  delay(100);
  lcd.clear();

  if(distance < 10) // si la distance est inférieure à 10cm...
  {
    digitalWrite(led, HIGH); // ... alors on allume la led
    tone(buzzer, 500, 100); // ... et on active le buzzer
  }
  else // sinon
  {
    digitalWrite(led, LOW); // la led reste éteinte
  }
}
