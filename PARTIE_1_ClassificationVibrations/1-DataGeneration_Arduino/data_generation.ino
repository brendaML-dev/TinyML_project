/*
  IMU Vibration Detection
  This example uses the on-board IMU to start reading acceleration and gyroscope
  data from on-board IMU and prints it to the Serial Monitor for one second
  when vibration is detected.
  You can also use the Serial Plotter to graph the data.
  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.
*/

#include <Arduino_LSM9DS1.h>

const float seuilVibration = 1.2; // Seuil de vibration 
const int nbEchantillons = 119;  // Nombre d'échantillons à collecter

int echantillonsLus = nbEchantillons;
float prevAX = 0, prevAY = 0, prevAZ = 0; // Valeurs précédentes de l'accélération

void setup() {
  Serial.begin(9600);  // Démarrer la communication série
  while (!Serial);  // Attendre que la connexion série soit prête

  if (!IMU.begin()) {  // Vérifier si l'IMU est bien initialisé
    Serial.println("Échec de l'initialisation de l'IMU !");
    while (1);  // Boucle infinie en cas d'erreur
  }

  // Afficher l'entête des données
  Serial.println("aX,aY,aZ,gX,gY,gZ,vibration");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // Attendre qu'une vibration soit détectée
  while (echantillonsLus == nbEchantillons) {
    if (IMU.accelerationAvailable()) {  // Vérifier si des données d'accélération sont disponibles
      // Lire les données d'accélération
      IMU.readAcceleration(aX, aY, aZ);

      // Calculer la variation d'accélération (vibration)
      float deltaAX = fabs(aX - prevAX);
      float deltaAY = fabs(aY - prevAY);
      float deltaAZ = fabs(aZ - prevAZ);
      
      // Mettre à jour les valeurs précédentes
      prevAX = aX;
      prevAY = aY;
      prevAZ = aZ;
      
      // Somme des variations d'accélération
      float vibration = deltaAX + deltaAY + deltaAZ;

      // Vérifier si la vibration dépasse le seuil
      if (vibration >= seuilVibration) {
        // Réinitialiser le nombre d'échantillons lus
        echantillonsLus = 0;
        break;  // Sortir de la boucle
      }
    }
  }

  // Vérifier si tous les échantillons nécessaires ont été lus
  while (echantillonsLus < nbEchantillons) {
    // Vérifier si les données d'accélération et de gyroscope sont disponibles
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // Lire les données d'accélération et de gyroscope
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);
      
      // Calculer la vibration (variation de l'accélération)
      float deltaAX = fabs(aX - prevAX);
      float deltaAY = fabs(aY - prevAY);
      float deltaAZ = fabs(aZ - prevAZ);
      float vibration = deltaAX + deltaAY + deltaAZ;
      
      // Mettre à jour les valeurs précédentes
      prevAX = aX;
      prevAY = aY;
      prevAZ = aZ;

      // Incrémenter le nombre d'échantillons lus
      echantillonsLus++;

      // Afficher les données sous forme de CSV
      Serial.print(aX, 3);  // Afficher la valeur de l'accélération en X
      Serial.print(',');
      Serial.print(aY, 3);  // Afficher la valeur de l'accélération en Y
      Serial.print(',');
      Serial.print(aZ, 3);  // Afficher la valeur de l'accélération en Z
      Serial.print(',');
      Serial.print(gX, 3);  // Afficher la valeur du gyroscope en X
      Serial.print(',');
      Serial.print(gY, 3);  // Afficher la valeur du gyroscope en Y
      Serial.print(',');
      Serial.print(gZ, 3);  // Afficher la valeur du gyroscope en Z
      Serial.print(',');
      Serial.println(vibration, 3);  // Afficher la valeur de la vibration

      // Si tous les échantillons ont été lus, ajouter une ligne vide
      if (echantillonsLus == nbEchantillons) {
        Serial.println();
      }
    }
  }
}
