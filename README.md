# CarePlus IoT - Monitoramento de Saúde

## 📌 Descrição do Projeto
Este projeto simula um sistema IoT de monitoramento de sinais vitais utilizando ESP32, MQTT e Node-RED Dashboard. Os dados de frequência cardíaca (BPM) e saturação de oxigênio (SpO2) são gerados pelo dispositivo e enviados via MQTT para visualização em tempo real.

## Integrantes
RM568108 – Nicolas Tanajura 
RM567396 – Pedro Chiarantano 
RM568059 – Gabriel Cutrim

---

## 🏗️ Arquitetura

- ESP32 (Wokwi Simulation)
- Broker MQTT (broker.hivemq.com)
- Node-RED Dashboard
- Comunicação via MQTT topic: /careplus/health/metrics

Fluxo:
ESP32 → MQTT Broker → Node-RED → Dashboard

---

## 📡 Tecnologias usadas

- Arduino / ESP32
- MQTT (HiveMQ)
- Node-RED
- Dashboard UI (node-red-dashboard)

---

## 📊 Dados enviados

Exemplo de payload:

```json
{
  "bpm": 78,
  "spo2": 97
}
