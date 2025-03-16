# TinyML_project

Ce projet consiste à implémenter des systèmes de Machine Learning embarqué (TinyML) en utilisant des capteurs embarqués, des modèles d'inférence légers, et plusieurs logiciels et plateformes embarquées. Le projet est divisé en deux parties principales :


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


# Partie 2 : Classification d'Objets avec Edge Impulse et Arduino

Dans cette deuxième partie, l’objectif est de créer un système d'analyse d'images permettant de **reconnaître différents composants électroniques** (par exemple, **LED**, **résistances**, **condensateurs**, etc.), capturés par la caméra **OV7670** connectée à un **Arduino Nano 33 BLE Sense**. Les résultats seront envoyés à **Node-RED** via **Bluetooth** pour effectuer un comptage et une gestion des objets détectés.

# 2.1. Étapes principales

# 2.1.1. Projet Edge Impulse (1-EdgeImpulse)
- Objectif : Créer un modèle de classification d'objets.
- Tout l’entraînement du modèle se fait sur la plateforme Edge Impulse.
- Les images capturées sont utilisées pour entraîner un modèle de classification des composants électroniques (LED, résistance, etc.).
- Après l’entraînement, un fichier C++ ou une bibliothèque est généré et exporté pour l’inférence sur Arduino.

# 2.1.2. Inférence sur Arduino avec la Caméra OV7670 (2-ArduinoCamera)
- Objectif : Implémenter l’inférence sur l’Arduino.
- Le code arduino_camera_classification.ino initialise la caméra OV7670 et récupère les images.
- Le code C++ généré par Edge Impulse (ou la bibliothèque correspondante) est ajouté au projet.
- Le code Arduino est configuré pour capturer l’image, la redimensionner et prétraiter les images selon la configuration d’Edge Impulse.
- La fonction d’inférence d'Edge Impulse est appelée pour obtenir une prédiction (par exemple, la classe de l'objet détecté : LED, Résistance, etc.).

# 2.1.3. Envoi des Résultats à Node-RED (3-NodeRED)
- Objectif : Envoyer les résultats de la classification à Node-RED.
- Les résultats de classification (type d'objet détecté) sont transmis à Node-RED via Bluetooth (BLE).
- Un flow Node-RED est configuré dans flows.json pour :
  - Recevoir les données.
  - Incrémenter un compteur associé à la classe d’objet détectée.
  - Afficher les compteurs sur un tableau de bord Node-RED pour une visualisation en temps réel.

