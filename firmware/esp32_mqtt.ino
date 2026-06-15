// Challenge FIAP CarePlus
// RM568108 – Nicolas Tanajura
// RM567396 – Pedro Chiarantano
// RM568059 – Gabriel Cutrim

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// ==========================
// WIFI
// ==========================

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==========================
// MQTT
// ==========================

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 8883;
const char* mqtt_user = "mba_12";
const char* mqtt_pass = "Mba_12000";

WiFiClientSecure espClient;
PubSubClient client(espClient);

// ==========================
// SENSORES
// ==========================

#define BPM_PIN 34
#define SPO2_PIN 35

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ==========================
// WIFI
// ==========================

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.println("Conectando ao Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ==========================
// MQTT CALLBACK
// ==========================

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

// ==========================
// MQTT RECONNECT
// ==========================

void reconnect() {

  while (!client.connected()) {

    Serial.print("Tentando conexão MQTT...");

    String clientId = "ESP32CarePlus-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {

      Serial.println(" conectado!");

      client.subscribe("ESPR/#");
      client.subscribe("ESPS/#");

    } else {

      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");

      delay(5000);
    }
  }
}

// ==========================
// SETUP
// ==========================

void setup() {

  Serial.begin(115200);

  pinMode(BPM_PIN, INPUT);
  pinMode(SPO2_PIN, INPUT);

  dht.begin();

  setup_wifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// ==========================
// LOOP
// ==========================

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  static unsigned long lastMsg = 0;

  if (millis() - lastMsg > 1000) {

    lastMsg = millis();

    // ==========================
    // LEITURA DOS SENSORES
    // ==========================

    int bpmRaw = analogRead(BPM_PIN);
    int spo2Raw = analogRead(SPO2_PIN);

    int bpm = map(bpmRaw, 0, 4095, 60, 130);

    int spo2 = map(spo2Raw, 0, 4095, 90, 100);

    float temperatura = dht.readTemperature();

    if (isnan(temperatura)) {
      temperatura = 36.5;
    }

    // ==========================
    // JSON MQTT
    // ==========================

    String payload = "{";
    payload += "\"bpm\":" + String(bpm) + ",";
    payload += "\"spo2\":" + String(spo2) + ",";
    payload += "\"temperature\":" + String(temperatura, 1);
    payload += "}";

    // ==========================
    // PUBLICAÇÃO
    // ==========================

    client.publish(
      "/careplus/health/metrics",
      payload.c_str()
    );

    // ==========================
    // SERIAL
    // ==========================

    Serial.println("================================");

    Serial.print("BPM: ");
    Serial.println(bpm);

    Serial.print("SpO2: ");
    Serial.println(spo2);

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Payload MQTT: ");
    Serial.println(payload);

    Serial.println("================================");
  }
}