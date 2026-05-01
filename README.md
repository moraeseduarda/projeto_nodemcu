# Atividade 2 - Sistemas Embarcados: Sistema de Alarme de Segurança Inteligente

Projeto consiste em um Sistema de Alarme de Segurança Inteligente desenvolvido com o NODEMCU (ESP8266). O sistema monitora a luminosidade do ambiente e dispara um alerta sonoro e visual caso detecte entrada de luz.

Esse projeto possui configuração dinâmica via rede, onde o limite de sensibilidade é baixado de um arquivo de configuração hospedado nesse repositório.

## 🛠️ Hardware Utilizado

- Microcontrolador: NodeMCU ESP-12E (ESP8266)
- Sensor: LDR (Resistor Dependente de Luz) para leitura analógica
- Atuador Sonoro: Buzzer Ativo/Passivo
- Saída Visual: LED Verde (Estado Seguro) e LED - Vermelho (Alerta de Intrusão).
    - Componentes Auxiliares: 
    - Resistores de $220\Omega$ (LEDs), 
    - Resistor de $10k\Omega$ (divisor de tensão do LDR) 
    - Protoboard

## 🚀 Requisitos Atendidos
- Leitura de Sensor: Uso do sensor LDR no pino analógico A0.

- Exibição de Dados: Monitoramento em tempo real dos valores de luminosidade e do limite configurado via Monitor Serial (115200 baud).

- Acionamento de Atuador: Disparo de um Buzzer através da função tone().

- Saída Visual: LEDs coloridos que indicam se o sistema está em vigilância (Verde) ou se o atuador foi acionado (Vermelho).

- Lógica de Programação: O atuador só é acionado se a leitura do LDR for superior ao limite estabelecido, simulando uma situação real de segurança.

- Modificação de Lógica via Rede (IoT): Integração com Wi-Fi e protocolo HTTP para baixar um arquivo de configuração (config.txt) hospedado no GitHub. O valor contido no arquivo define o parâmetro de sensibilidade do alarme sem necessidade de reprogramar o código.

## 💻 Funcionamento do Código
Ao iniciar, o NodeMCU:
1. Conecta-se ao ponto de acesso Wi-Fi configurado (Roteador móvel)
2. Realiza uma requisição HTTP GET para o repositório no GitHub
3. Lê o conteúdo do arquivo config.txt e converte para um valor inteiro (limiteLuz)
4. Entra em um loop de monitoramento comparando a leitura do pino A0 com o valor obtido pela rede.

## 📁 Estrutura do Repositório

- sistemaLuz/projeto_nodemcu.ino: Código fonte da aplicação.
- config.txt: Arquivo de configuração remota contendo o parâmetro de limite de luz.
- README.md: Documentação do projeto.

## Exemplo de uso do Monitor Serial:

```cpp
Conectando ao Wi-Fi
..........
Conectado!
Baixando configuração de: ...
Novo limite configurado via rede: 700
--- Sistema Iniciado e Monitorando ---
Luz Atual: 120 | Limite Configurado: 700 (Status: SEGURO)
Luz Atual: 850 | Limite Configurado: 700 (Status: ALERTA!)

