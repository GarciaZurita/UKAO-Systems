// --- Librerías necesarias ---
#include <Wire.h>                // Librería para comunicación I2C (pantalla LCD)
#include <LiquidCrystal_I2C.h>   // Librería para manejar pantallas LCD con módulo I2C

// --- Configuración de la pantalla LCD ---
// Dirección I2C: 0x26, tamaño: 20 columnas x 4 filas
LiquidCrystal_I2C lcd(0x26, 20, 4);

// --- Definición de pines ---
#define SENSOR_PULSO A0     // Entrada analógica para el sensor de pulso (o potenciómetro)
#define LED_VERDE 6         // LED que indica estado ESTABLE
#define LED_AMARILLO 7      // LED que indica estado de RIESGO
#define LED_ROJO 8          // LED que indica estado CRÍTICO
#define LED_AZUL 9          // LED que indica estado de MUERTO
#define BUZZER 5            // Pin del buzzer piezoeléctrico

// --- Datos del paciente ---
String nombre = "Carlos Mendez";            // Nombre del paciente
int edad = 35;                              // Edad del paciente
String tipoSangre = "O+";                   // Tipo de sangre
String alergias = "Penicilina";             // Alergia registrada
String condiciones = "Hipertension";        // Condición médica existente
String contactoEmergencia = "5548123987";   // Número de contacto en caso de emergencia
String ubicacion = "19.4326,-99.1332";      // Ubicación GPS (ejemplo: CDMX)

// --- Variables para funcionamiento ---
int pulso = 0;           // Variable donde se guarda el valor del pulso leído
String estado = "";      // Variable que almacena el estado del paciente (ESTABLE, RIESGO, etc.)

// --- Umbrales (rangos de pulso en BPM) ---
#define PULSO_NORMAL_MIN 60     // Límite inferior del rango normal
#define PULSO_NORMAL_MAX 80     // Límite superior del rango normal
#define PULSO_RIESGO_ALTO 100   // Pulso máximo considerado riesgo
#define PULSO_RIESGO_BAJO 40    // Pulso mínimo considerado riesgo
#define PULSO_MUERTE_ALTO 120   // Pulso extremo alto que indica posible muerte
#define PULSO_MUERTE_BAJO 30    // Pulso extremo bajo que indica muerte

// --- Función de configuración inicial ---
void setup() {
  Serial.begin(9600);    // Inicia comunicación serial (para depuración en el monitor serial)
  lcd.init();            // Inicializa la pantalla LCD
  lcd.backlight();       // Enciende la luz de fondo de la pantalla

  // Configuración de los pines de entrada y salida
  pinMode(SENSOR_PULSO, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // --- Mensaje de inicio en pantalla ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SISTEMA DE TRIAGE");   // Título del sistema
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);                      // Espera 2 segundos

  // --- Mostrar datos personales del paciente ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Paciente:");           // Nombre
  lcd.setCursor(0, 1);
  lcd.print(nombre.substring(0, 20));  // Muestra hasta 20 caracteres
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Edad: ");              // Edad y tipo de sangre
  lcd.print(edad);
  lcd.setCursor(0, 1);
  lcd.print("Sangre: ");
  lcd.print(tipoSangre);
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alerg: ");             // Alergias y condiciones médicas
  lcd.print(alergias.substring(0, 14));
  lcd.setCursor(0, 1);
  lcd.print("Cond: ");
  lcd.print(condiciones.substring(0, 14));
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Contacto:");           // Contacto de emergencia
  lcd.setCursor(0, 1);
  lcd.print(contactoEmergencia);
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ubicacion:");          // Ubicación GPS
  lcd.setCursor(0, 1);
  lcd.print(ubicacion);
  delay(2500);

  lcd.clear();                      // Limpia la pantalla antes de iniciar lecturas
}

// --- Bucle principal del programa ---
void loop() {
  // --- Lectura del sensor ---
  int valor = analogRead(SENSOR_PULSO);   // Lee el valor analógico (0–1023)
  pulso = map(valor, 0, 1023, 20, 130);   // Convierte a rango de 20–130 BPM simulados

  // --- Apagar todos los LEDs y el buzzer antes de actualizar estado ---
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AZUL, LOW);
  noTone(BUZZER);

  // --- Clasificación del estado del paciente según el pulso ---
  if (pulso >= PULSO_NORMAL_MIN && pulso <= PULSO_NORMAL_MAX) {
    // Estado normal
    estado = "ESTABLE";
    digitalWrite(LED_VERDE, HIGH);     // Enciende LED verde
  }
  else if ((pulso > PULSO_NORMAL_MAX && pulso <= PULSO_RIESGO_ALTO) ||
           (pulso >= PULSO_RIESGO_BAJO && pulso < PULSO_NORMAL_MIN)) {
    // Estado de riesgo (pulso ligeramente alto o bajo)
    estado = "RIESGO";
    digitalWrite(LED_AMARILLO, HIGH);  // Enciende LED amarillo
    tone(BUZZER, 700);                 // Suena alarma de tono medio
  }
  else if ((pulso > PULSO_RIESGO_ALTO && pulso < PULSO_MUERTE_ALTO) ||
           (pulso > PULSO_MUERTE_BAJO && pulso < PULSO_RIESGO_BAJO)) {
    // Estado crítico (pulso muy alto o muy bajo)
    estado = "CRITICO";
    digitalWrite(LED_ROJO, HIGH);      // Enciende LED rojo
    tone(BUZZER, 1000);                // Suena alarma de tono más agudo
  }
  else if (pulso <= PULSO_MUERTE_BAJO || pulso >= PULSO_MUERTE_ALTO) {
    // Estado de muerte (sin signos vitales o pulso extremo)
    estado = "SIN SIGNOS VITALES";
    digitalWrite(LED_AZUL, HIGH);      // Enciende LED azul
    tone(BUZZER, 2000);                // Alarma con tono alto y continuo
  }

  // --- Mostrar en pantalla el pulso y el estado actual ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulso: ");
  lcd.print(pulso);
  lcd.print(" bpm");                   // Muestra el pulso actual

  lcd.setCursor(0, 1);
  lcd.print("Estado: ");
  lcd.print(estado);                   // Muestra el estado del paciente
  delay(2000);

  // --- Mostrar ubicación en pantalla ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ubicacion:");
  lcd.setCursor(0, 1);
  lcd.print(ubicacion);                // Muestra coordenadas GPS
  delay(2000);
}
