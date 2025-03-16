Pour entrainer le modèle sur edge impulse veuillez suivre les étapes suivantes: 

# 1. Préparation des données  
J'ai utilisé un dataset d'images de composant electronique fourni en cours disponible sur https://github.com/ShawnHymel/computer-vision-with-embedded-machine-learning/raw/master/Datasets/electronic-components-png.zip

# 2. Téléversement du dataset sur Edge Impulse  
1. Créer un projet Edge Impulse 
   - Aller sur Edge Impulse Studio et créer un nouveau projet.  

2. Importer les images 
   - Aller dans Data Acquisition  
   - Cliquer sur Upload existing data
   - Sélectionner toutes les images d’une catégorie (ex. résistances)  
   - Cocher Automatically split between training and testing
   - Entrer un label correspondant à la classe des images (ex. “resistor”)  
   - Valider avec Begin upload
   - Répéter cette étape pour chaque classe  

3. Vérifier la répartition des données
   - Retourner dans Data Acquisition  
   - S’assurer d’un bon équilibre entre les ensembles d'entraînement et de test  

# 3. Création de l’Impulse  
1. Accéder à Impulse Design 
   - Définir la taille des images : 28x28 (ou adapter selon vos images)  
   - Régler le mode de redimensionnement (crop, étirement, etc.)  

2. Ajouter les blocs de traitement et d’apprentissage 
   - Ajouter un Image processing block
   - Ajouter un Classification (Keras) learning block
   - Enregistrer l’Impulse  

# 4. Extraction des caractéristiques  
1. Aller dans l’onglet Image sous Impulse Design 
2. Modifier Color depth en Grayscale  
3. Enregistrer les paramètres  
4. Lancer la génération des caractéristiques avec Generate features 
Edge Impulse va convertir les images en niveaux de gris et les redimensionner à 28x28 pixels.  

# 5. Entraînement du modèle  
1. Aller dans NN Classifier 
2. Modifier les paramètres :  
   - Number of training cycles : entre 100 et 200 
   - Ajuster les filtres, les tailles de noyau, les couches de convolution et le dropout si nécessaire  
3. Lancer l’entraînement avec Start training 
4. Analyser la performance du modèle  
Ajustez les hyperparamètres si nécessaire pour améliorer l’exactitude.  

# 6. Déploiement du modèle sur l’Arduino  
1. Une fois l'entraînement terminé, aller dans Deployment 
2. Sélectionner Arduino Library (.zip)  
3. Télécharger et extraire la bibliothèque Edge Impulse  
4. Copier les fichiers dans :  
   PARTIE_2_ClassificationComposants/2-ArduinoCamera/
5. Ouvrir arduino_camera_classification.ino dans l'IDE Arduino  
6. Téléverser le programme sur l’Arduino Nano 33 BLE Sense  


