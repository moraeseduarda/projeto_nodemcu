#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Configurações do Wi-Fi
const char* ssid = "Du";
const char* password = "duda1234";

const char* urlConfig = "https://raw.githubusercontent.com/moraeseduarda/projeto_nodemcu/refs/heads/main/config.txt"; 

// Definição dos Pinos
const int pinoLDR = A0;
const int pinoBuzzer = D6;
const int pinoLedVerde = D2;
const int pinoLedVermelho = D5;

// Variáveis de Controle
int leituraLDR = 0;
int limiteLuz = 500; // Valor padrão caso o download falhe

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configuração dos Pinos
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);
  pinMode(pinoLedVermelho, OUTPUT);

  // 1. Conexão ao Wi-Fi
  Serial.print("Conectando ao Wi-Fi");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");

// 2. Download da Configuração via GitHub (HTTPS)
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    
    HTTPClient http;
    Serial.print("Baixando configuração de: ");
    Serial.println(urlConfig);

    if (http.begin(client, urlConfig)) {
      int httpCode = http.GET(); 

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        limiteLuz = payload.toInt(); // Converte o texto do arquivo para número
        Serial.print("Novo limite configurado via rede: ");
        Serial.println(limiteLuz);
      } else {
        Serial.printf("Falha ao baixar. Erro HTTP: %d\n", httpCode);
      }
      http.end();
    }
  }
  
  Serial.println("--- Sistema Iniciado e Monitorando ---");
}

void loop() {
  leituraLDR = analogRead(pinoLDR);

  Serial.print("Luz: ");
  Serial.print(leituraLDR);
  Serial.print(" | Limite Configurado: ");
  Serial.println(limiteLuz);

  // Lógica de acionamento (Simulação de Alarme de Segurança)
  if (leituraLDR > limiteLuz) {
    // ESTADO DE ALERTA (Luz detectada / Intrusão)
    digitalWrite(pinoLedVermelho, HIGH); // LED Vermelho liga
    digitalWrite(pinoLedVerde, LOW); // LED Verde desliga
    tone(pinoBuzzer, 1000); // Aciona Atuador (Buzzer)
  } else {
    // ESTADO SEGURO (Escuro / Tudo fechado)
    digitalWrite(pinoLedVermelho, LOW);
    digitalWrite(pinoLedVerde, HIGH); // LED Verde indica sistema OK
    noTone(pinoBuzzer); // Desliga Atuador
  }

  delay(500);
}