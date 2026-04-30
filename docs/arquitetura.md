# 🏗️ Arquitetura do Sistema CarePlus IoT

---

## 📌 Visão Geral

O sistema simula um ambiente de monitoramento de saúde via IoT, onde um dispositivo **ESP32** gera sinais vitais (BPM e SpO2), envia via **MQTT** para um broker público, e o **Node-RED** consome esses dados para exibição em um dashboard em tempo real.

---

## 🔄 Arquitetura Lógica

### 📦 Componentes do Sistema

---

### 🤖 ESP32 (Wokwi)
- Gera dados simulados de sinais vitais
- Frequência cardíaca (BPM)
- Saturação de oxigênio (SpO2)
- Publica mensagens via MQTT

---

### ☁️ Broker MQTT (HiveMQ)
- Atua como middleware de comunicação **publish/subscribe**
- Recebe mensagens do ESP32
- Distribui para os consumidores inscritos

---

### 🔧 Node-RED
- Assina o tópico MQTT `/careplus/health/metrics`
- Converte payload JSON
- Processa dados (BPM e SpO2)
- Envia para o dashboard

---

### 📊 Dashboard UI
- Exibe métricas em tempo real
- Gauge de Frequência Cardíaca (BPM)
- Gauge de SpO2
- Interface visual para monitoramento

---

## 🔁 Fluxo de Dados

ESP32 → MQTT Broker → Node-RED → Dashboard UI