Pour réaliser ce projet, veuillez suivre les étapes suivantes:

# 1. Téléchargement du programme sur l’Arduino  
1. Vérifier que la carte Arduino Nano 33 BLE Sense est bien connectée à l'ordinateur.  
2. Ouvrir l’IDE Arduino et téléverser le fichier data_generation.ino qui se trouve dans : 
   PARTIE_1_ClassificationVibrations/1-DataGeneration_Arduino/
3. Ouvrir le moniteur série pour s'assurer que les données de l’accéléromètre s'affichent correctement sous forme de valeurs numériques.  

# 2. Collecte des données avec le programme Python  
Une fois le programme Arduino en marche, il faut enregistrer les données dans un fichier CSV en ouvrant et exécutant le script Python serial_data_to_csv.py qui se trouve dans : 
   PARTIE_1_ClassificationVibrations/1-DataGeneration_Arduino/  
1. Indiquer le nom du fichier CSV qui contiendra les données.  
2. Cliquer sur "Démarrer" pour lancer l'enregistrement des données.  
3. Une notification apparaîtra une fois le processus terminé.  
Le fichier CSV est maintenant prêt et peut être visualisé avec un éditeur de texte ou un tableur.
4. Répéter l'opération pour chaque classe.

# 3. Préparation des données pour l’entraînement du modèle  
Les fichiesr CSV généré doit être placé dans le dossier prévu pour l'entraînement.  
1. Ouvrir  et exécuter les cellules du notebook :  
   PARTIE_1_ClassificationVibrations/2-Training/code_entrainement/link_to_notebook colab.md  
2. Suivre les étapes du Notebook pour prétraiter les données, entraîner le modèle et le sauvegarder.  
NB: Ce Notebook est basé sur un code étudié en cours, avec des modifications adaptées au projet.  

# 4. Génération du modèle et intégration à Arduino  
1. À la fin de l'entraînement, un fichier model.h est généré. Il se trouve dans:
   PARTIE_1_ClassificationVibrations/3-Inference_Arduino/ 
2. Ouvrir l'IDE Arduino et charger le fichier inference_vibrations.ino.  
3. Téléverser le code sur l’Arduino pour tester la classification en temps réel.  

# 5. Test du modèle avec l’Arduino  
1. Ouvrir le moniteur série dans l'IDE Arduino.  
2. Observer les résultats affichés en temps réel.  

L'Arduino va analyser les vibrations détectées et afficher leur classification.  

