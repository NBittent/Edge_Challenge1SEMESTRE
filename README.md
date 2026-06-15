# CarePlus IoT - Monitoramento de Saúde

## 📌 Descrição do Projeto

O CarePlus é uma solução IoT para monitoramento de sinais vitais em tempo real. O projeto utiliza um ESP32 simulado no Wokwi para coletar dados de sensores virtuais e enviá-los via protocolo MQTT para um broker HiveMQ. O Node-RED recebe essas informações e as apresenta em um dashboard interativo para acompanhamento dos indicadores de saúde.

Os dados monitorados incluem:

* Frequência Cardíaca (BPM)
* Saturação de Oxigênio (SpO2)
* Temperatura Corporal

---

## 👥 Integrantes

* RM568108 – Nicolas Tanajura
* RM567396 – Pedro Chiarantano
* RM568059 – Gabriel Cutrim

---

## 🏗️ Arquitetura

### Componentes

* ESP32 (Simulação no Wokwi)
* Sensores Virtuais

  * Potenciômetro (BPM)
  * Potenciômetro (SpO2)
  * DHT22 (Temperatura)
* Broker MQTT (HiveMQ)
* Node-RED
* Dashboard Web

### Fluxo de Dados

```text
Sensores → ESP32 → MQTT Broker → Node-RED → Dashboard
```

### Tópico MQTT

```text
/careplus/health/metrics
```

---

## 📡 Tecnologias Utilizadas

* Arduino IDE
* ESP32
* MQTT
* HiveMQ
* Node-RED
* Wokwi Simulator
* Dashboard UI

---

## 📊 Dados Enviados

Exemplo de payload MQTT:

```json
{
  "bpm": 92,
  "spo2": 96,
  "temperature": 37.3
}
```

---

## 📈 Funcionalidades

* Monitoramento de BPM em tempo real
* Monitoramento de SpO2 em tempo real
* Monitoramento de temperatura corporal
* Dashboard com gauges interativos
* Gráficos históricos das métricas
* Registro das leituras em tabela
* Comunicação em tempo real via MQTT

---

## 🚀 Como Executar

### 1. Simulação Wokwi

1. Abra o projeto no Wokwi.
2. Inicie a simulação.
3. Ajuste os potenciômetros e o sensor para gerar novas leituras.

### 2. Node-RED

1. Importe o fluxo fornecido no repositório.
2. Configure o broker MQTT:

   * Host: broker.hivemq.com
   * Porta: 1883
3. Faça o Deploy do fluxo.

### 3. Dashboard

Acesse:

```text
http://localhost:1880/dashboard
```

ou a URL configurada no Node-RED.

---

## 🎯 Aplicação

O projeto demonstra como tecnologias IoT podem ser utilizadas para monitoramento remoto de pacientes, permitindo a coleta, transmissão e visualização de sinais vitais em tempo real por meio de uma arquitetura baseada em MQTT.
