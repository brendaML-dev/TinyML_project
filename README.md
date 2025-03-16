# TinyML_project

Ce projet consiste à implémenter des systèmes de Machine Learning embarqué (TinyML) en utilisant des capteurs embarqués, des modèles d'inférence légers, et plusieurs logiciels et plateformes embarquées. Le projet est divisé en deux parties principales :

1. Partie 1 : Classification des Vibrations avec Arduino :
Cette partie consiste à créer un système capable de générer différentes vibrations (par exemple, via une application de vibration de smartphone), à collecter les données de vibrations avec la carte Arduino Nano 33 BLE et son IMU intégré, à entraîner un modèle TensorFlow Lite pour reconnaître et classer ces vibrations, puis à déployer et effectuer l'inférence en temps réel sur la carte Arduino.


2. Partie 2 : Classification d'Objets avec Edge Impulse et Arduino :
Dans cette deuxième partie, l’objectif est de créer un système d'analyse d'images permettant de reconnaître différents composants électroniques (par exemple, LED, résistances, condensateurs, etc.), capturés par la caméra OV7670 connectée à un Arduino Nano 33 BLE Sense. Les résultats seront envoyés à Node-RED via Bluetooth pour effectuer un comptage et une gestion des objets détectés.

