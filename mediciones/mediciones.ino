#include <WiFi.h>// Biblioteca WiFi para ESP32
#include <HTTPClient.h>

const char* ssid = "nh";         // SSID de tu red WiFi
const char* password = "123456789";     // Contraseña de tu red WiFi
const char* serverUrl = "http://192.168.137.1/Tinaco/index.php"; // Dirección IP del servidor
const int port = 8005;                 // Puerto del servidor
const int watchdog = 5000;           // Frecuencia del watchdog
unsigned long previousMillis = millis();

// Pines del puente H
int pinIN1 = 25; // Entrada 1 del puente H
int pinIN2 = 26; // Entrada 2 del puente H
int pinENA = 27; // Enable (puede usarse para control de velocidad)

int Led = 2;

//Pines de los sensores 
const int pinEco = 12;
const int pinGatillo = 13;

const int pinEco_dos = 33;
const int pinGatillo_dos = 32;

//variables glovales 
int porc;
long tiempo;
float distancia;

int porc_dos;
long tiempo_dos;
float distancia_dos;

int modo = 1; // Inicialmente en automático (1)
int nivel = 100;


// Sensor 1 (Tinaco)
void medir_sensor_uno() {
  digitalWrite(pinGatillo, LOW);
  delayMicroseconds(2);
  digitalWrite(pinGatillo, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinGatillo, LOW);

  tiempo = pulseIn(pinEco, HIGH, 30000); // Máximo 30 ms para evitar bloqueos
  if (tiempo > 0) {
    distancia = float(tiempo * 0.0343) / 2;
  } else {
    distancia = -1; // Valor inválido si no hay respuesta
  }
  delay(10);
}

void porcentaje_uno() {
  if (distancia > 0) {
    porc = map(distancia, 5, 15, 100, 0);
    porc = constrain(porc, 0, 100); // Limitar el rango a 0-100%
  } else {
    porc = -1; // Sin medición válida
  }
}

// Sensor 2 (Cisterna)
void medir_sensor_dos() {
  digitalWrite(pinGatillo_dos, LOW);
  delayMicroseconds(2);
  digitalWrite(pinGatillo_dos, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinGatillo_dos, LOW);

  tiempo_dos = pulseIn(pinEco_dos, HIGH, 30000); // Máximo 30 ms
  if (tiempo_dos > 0) {
    distancia_dos = float(tiempo_dos * 0.0343) / 2;
  } else {
    distancia_dos = -1; // Valor inválido
  }
  delay(10);
}

void porcentaje_dos() {
  if (distancia_dos > 0) {
    porc_dos = map(distancia_dos, 5, 9, 100, 0);
    porc_dos = constrain(porc_dos, 0, 100); // Limitar el rango
  } else {
    porc_dos = -1; // Sin medición válida
  }
}

// Control de la bomba usando puente H
void encender_bomba() {
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinENA, 255); // Velocidad máxima
  Serial.println("Bomba encendida");
}

void apagar_bomba() {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinENA, 0);
  Serial.println("Bomba apagada");
}

// Enviar datos a la base de datos
void enviar_datos(int nivel_tinaco, int nivel_cisterna) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "?tinaco=" + nivel_tinaco +
                 "&cisterna=" + nivel_cisterna;

    http.begin(url); // Inicia la conexión HTTP
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("Datos enviados: " + url);
      Serial.println("Respuesta del servidor: " + http.getString());
    } else {
      Serial.println("Error al enviar datos: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi no conectado");
  }
}

// Leer el modo de la base de datos
void leer_modo() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(String(serverUrl) + "?accion=leer_modo"); // URL para leer el modo
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      modo = response.toInt(); // Leer el modo (1 = Automático, 0 = Manual)
      Serial.println("Modo leído: " + String(modo));
    } else {
      Serial.println("Error al leer el modo: " + String(httpResponseCode));
    }

    http.end();
  }
}

//leer nivel del agua seleccionado
void seleccionNivel (){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(String(serverUrl) + "?level=seleccionNivel"); // URL para leer el modo
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      nivel = response.toInt(); 
      Serial.println("Modo leído: " + String(nivel));
    } else {
      Serial.println("Error al leer el nivel: " + String(httpResponseCode));
    }

    http.end();
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(pinEco, INPUT);
  pinMode(pinGatillo, OUTPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW); // Relé apagado inicialmente

  pinMode(pinEco_dos, INPUT);
  pinMode(pinGatillo_dos, OUTPUT);

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);

  apagar_bomba(); // Apagar la bomba al inicio

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. Dirección IP: " + WiFi.localIP().toString());
}

void loop() {
  
  leer_modo(); // Leer el modo actual

  // Sensor 1
  medir_sensor_uno();
  porcentaje_uno();
  Serial.print("Sensor 1 - Distancia: ");
  if (distancia >= 0) {
    Serial.print(distancia);
    Serial.print(" cm, Porcentaje: ");
    Serial.print(porc);
    Serial.println(" %");
  } else {
    Serial.println("Medición no válida.");
  }

  // Sensor 2
  medir_sensor_dos();
  porcentaje_dos();
  Serial.print("Sensor 2 - Distancia: ");
  if (distancia_dos >= 0) {
    Serial.print(distancia_dos);
    Serial.print(" cm, Porcentaje: ");
    Serial.print(porc_dos);
    Serial.println(" %");
  } else {
    Serial.println("Medición no válida.");
  }


  if (modo == 1) { // Modo automático
    // Control del relé
    if (porc >= 0 && porc <= 50) { // Si el nivel del tinaco es bajo
      digitalWrite(Led, HIGH); // Encender el relé
      encender_bomba();
    } else if (porc == nivel) { // Si el nivel del tinaco está lleno
      digitalWrite(Led, LOW); // Apagar el relé
      apagar_bomba();
    }
  } else if (modo == 0) { // Modo manual
    // En el modo manual, el estado de la bomba será controlado por la base de datos.
    // El ESP32 no toma decisiones aquí.
  }
  enviar_datos(porc, porc_dos); // Enviar datos al servidor
  delay(1000); // Esperar un segundo antes de la siguiente iteración
}
