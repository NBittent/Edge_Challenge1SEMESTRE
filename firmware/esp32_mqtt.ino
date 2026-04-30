//Challenge FIAP CarePlus 
//RM568108 – Nicolas Tanajura RM567396 – Pedro Chiarantano RM568059 – Gabriel Cutrim

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi para o Wokwi  
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do HiveMQ Cloud  
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 8883;
const char* mqtt_user = "mba_12";
const char* mqtt_pass = "Mba_12000";  

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("\nConectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");  
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    String clientId = "ESP32Client-";  
    clientId += String(random(0xffff), HEX);  

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Conectado ao HiveMQ!");
      // Ajustar o código da turma
      client.subscribe("ESPR/#");  
      client.subscribe("ESPS/#");  
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");  
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {  
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  espClient.setInsecure(); // Necessário para porta 8883  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// ... (parte inicial do código permanece igual)

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();

    // GERANDO O INTEIRO ALEATÓRIO
    int bpm = random(60, 100);
    int spo2 = random(95, 100);

    // CONVERTENDO PARA STRING (MQTT só aceita texto ou bytes)
    String payload = "{";
    payload += "\"bpm\":" + String(bpm) + ",";
    payload += "\"spo2\":" + String(spo2);
    payload += "}";

    // PUBLICANDO NO TÓPICO da turma
    // Ajustar a turma e seu nome
    client.publish("/careplus/health/metrics", payload.c_str());

    Serial.print("Mensagem enviada: ");
    Serial.println(payload);
  }
}