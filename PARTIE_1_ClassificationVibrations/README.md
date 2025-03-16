# Partie 1 : Classification des Vibrations avec Arduino

Dans cette première partie, l’objectif est de créer un système capable de générer différentes vibrations (par exemple, via une application de vibration de smartphone), de collecter les données de vibrations avec la carte Arduino Nano 33 BLE et son IMU intégré, d’entraîner un modèle TensorFlow Lite pour reconnaître et classer ces vibrations, puis de déployer et effectuer l'inférence en temps réel sur la carte Arduino.

# 1.1. Étapes principales

# 1.2.1. Génération et Collecte des Données (1-DataGeneration_Arduino)
- Objectif : Générer des vibrations et collecter des données.
- Le code Arduino data_generation.ino initialise l’IMU (accéléromètre, gyroscope, etc.) sur l’Arduino Nano 33 BLE.
- Les données brutes (accélération, gyroscope) sont lues et transmises via Serial.
- Un étiquetage est effectué pour associer les données à des types de vibrations spécifiques (par exemple, vibration liée à une LED, résistance, etc.).

# 1.2.2. Entraînement (2-Training)
- Objectif : Entraîner un modèle de classification.
- Le notebook Jupyter training_vibrations.ipynb permet d’importer et de traiter les données collectées.
- Un modèle de classification est entraîné à l’aide d’un réseau de neurones simple, SVM, ou tout autre algorithme compatible avec TensorFlow Lite.
- Le modèle entraîné est ensuite exporté au format .tflite pour être déployé sur l’Arduino.

# 1.2.3. Inférence sur Arduino (3-Inference_Arduino)
- Objectif : Déployer le modèle sur l’Arduino pour effectuer des inférences en temps réel.
- Le modèle .tflite est inclus dans le sketch inference_vibrations.ino.
- Les données de l’IMU sont lues en temps réel sur l’Arduino.
- Un prétraitement des données est effectué de manière identique à celui utilisé lors de l’entraînement.
- La vibration courante est classée et le résultat est affiché via Serial.

