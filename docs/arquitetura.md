# 🏗️ Arquitetura do Sistema CarePlus IoT

---

## 📌 Visão Geral

O CarePlus é uma solução IoT para monitoramento de sinais vitais em tempo real. Utilizando um ESP32 simulado no Wokwi, sensores virtuais geram dados de frequência cardíaca (BPM), saturação de oxigênio (SpO2) e temperatura corporal, que são enviados via protocolo MQTT para um broker público. O Node-RED recebe essas informações e as apresenta em um dashboard interativo para acompanhamento do paciente.

---

## 🔄 Arquitetura Lógica

### 📦 Componentes do Sistema

### 🤖 ESP32 (Wokwi)

Responsável pela coleta e envio dos dados dos sensores simulados.

Sensores utilizados:

* Potenciômetro 1 → Frequência Cardíaca (BPM)
* Potenciômetro 2 → Saturação de Oxigênio (SpO2)
* DHT22 → Temperatura Corporal

Funções:

* Leitura dos sensores
* Formatação dos dados em JSON
* Publicação via MQTT

---

### ☁️ Broker MQTT (HiveMQ)

Atua como intermediário entre os dispositivos e a aplicação.

Funções:

* Receber mensagens publicadas pelo ESP32
* Distribuir os dados para os clientes inscritos
* Implementar o modelo Publish/Subscribe

Tópico utilizado:

```text
/careplus/health/metrics
```

---

### 🔧 Node-RED

Responsável pelo processamento dos dados recebidos.

Funções:

* Assinar o tópico MQTT
* Converter mensagens JSON
* Processar métricas de saúde
* Alimentar o dashboard em tempo real
* Registrar histórico das leituras

---

### 📊 Dashboard UI

Interface de monitoramento em tempo real.

Recursos disponíveis:

* Gauge de Frequência Cardíaca (BPM)
* Gauge de Saturação de Oxigênio (SpO2)
* Gauge de Temperatura Corporal
* Gráfico histórico de BPM
* Gráfico histórico de SpO2
* Tabela com histórico das leituras

---

## 📡 Estrutura do Payload

Exemplo de mensagem enviada pelo ESP32:

```json
{
  "bpm": 92,
  "spo2": 96,
  "temperature": 37.3
}
```

---

## 🔁 Fluxo de Dados

```text
Sensores Simulados
       ↓
      ESP32
       ↓ MQTT
Broker HiveMQ
       ↓
    Node-RED
       ↓
 Dashboard UI
```

---

## 🎯 Aplicação na Saúde

A solução demonstra como dispositivos IoT podem ser utilizados para monitoramento remoto de pacientes, permitindo o acompanhamento contínuo de indicadores importantes de saúde e auxiliando na tomada de decisões de forma rápida e eficiente.
