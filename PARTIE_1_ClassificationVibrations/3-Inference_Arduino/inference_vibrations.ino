#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>

// Includes nécessaires pour TensorFlow Lite
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Inclusion du modèle (à créer séparément)
#include "vibrations_model.h"

// Définition des composants TensorFlow Lite
namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
  
  // Créer un résolveur d'opérations qui supporte toutes les opérations TensorFlow Lite
  tflite::AllOpsResolver resolver;
  
  // Mémoire pour les tenseurs
  constexpr int kTensorArenaSize = 8 * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
}

// Buffer pour stocker les valeurs des capteurs
float input_data[3];  // X, Y, Z

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Initialisation du capteur IMU
    if (!IMU.begin()) {
        Serial.println("Erreur : Impossible d'initialiser l'IMU !");
        while (1);
    }
    
    // Configurer le système de rapport d'erreurs
    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;
    
    // Charger le modèle
    model = tflite::GetModel(g_vibrations_model);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        TF_LITE_REPORT_ERROR(error_reporter,
                           "Version du modèle %d incompatible avec la version supportée %d.",
                           model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }
    
    // Créer l'interpréteur
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;
    
    // Allouer la mémoire pour les tenseurs
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Erreur d'allocation mémoire pour les tenseurs !");
        return;
    }
    
    // Obtenir les pointeurs vers les tenseurs d'entrée et de sortie
    input = interpreter->input(0);
    output = interpreter->output(0);
    
    Serial.println("Système prêt ! Attente de vibrations...");
}

void loop() {
    // Lire les données de l'IMU
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(input_data[0], input_data[1], input_data[2]);

        // Normaliser les données (comme lors de l'entraînement)
        for (int i = 0; i < 3; i++) {
            input_data[i] = input_data[i] / 10.0; // Ajuste selon ton dataset
        }

        // Placer les données dans le modèle
        for (int i = 0; i < 3; i++) {
            input->data.f[i] = input_data[i];
        }

        // Faire l'inférence
        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
            Serial.println("Erreur pendant l'inférence !");
            return;
        }

        // Lire les résultats
        int prediction = -1;
        float max_value = 0.0;
        
        for (int i = 0; i < 3; i++) {
            if (output->data.f[i] > max_value) {
                max_value = output->data.f[i];
                prediction = i;
            }
        }

        // Afficher le résultat
        Serial.print("Vibration détectée : Classe ");
        Serial.print(prediction);
        Serial.print(" (confiance: ");
        Serial.print(max_value);
        Serial.println(")");
    }

    delay(100);
}
