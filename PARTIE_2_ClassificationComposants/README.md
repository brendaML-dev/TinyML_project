# Partie 2 : Classification d'Objets avec Edge Impulse et Arduino
L’objectif est de créer un système d'analyse d'images permettant de reconnaître différents composants électroniques (par exemple, LED, résistances, condensateurs, etc.), capturés par la caméra OV7670 connectée à un Arduino Nano 33 BLE Sense. Les résultats seront envoyés à Node-RED via Bluetooth pour effectuer un comptage et une gestion des objets détectés.

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


