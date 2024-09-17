 
<h1 align="center">[RMA] Projeto dos Bixos 2024 - SEMEAR</h1>


<p align="center">Este é o repositório do Projeto dos Bixos do núcleo de Robótica Móvel Autonoma [RMA] do grupo SEMEAR, vinculado à Universidade de São Paulo. Nosso time tem o objetivo de construir um robô autônomo de reconhecimento de áreas, também conhecido como robô explorador.</p>

**Os códigos utilizados para executar as tarefas e análises do projeto estão documentados neste repositório.**

### Objetivos do robô:
Deslocar-se de forma terrestre e totalmente autônoma; Explorar o ambiente desconhecido; Ter um sistema de localização minimamente preciso; Não colidir com os objetos; Gerar um mapa em tempo real do ambiente; Encontrar as rotas mais otimizadas ao planejar trajetórias. Ausência de tempo máximo para a exploração.


> O projeto abrange atuações em mecânica, eletrônica e programação, juntas elas devem funcionar em harmonia.


## Ferramentas

### Ubuntu 20.04 LTS
A instalação desta distro do Linux é muito importante devido à sua grande compatibilidade com as ferramentas ROS (Robot Operating System) e o ESP-IDF (Espressif IoT Development Framework), as quais são essênciais para o nosso projeto.

Para baixar, acesse o link [Ubuntu](https://ubuntu.com/download)

### PlataformIO
PlatformIO é uma plataforma de desenvolvimento de código aberto para programação de microcontroladores e sistemas embarcados. Ela suporta uma ampla gama de placas e frameworks, facilitando a compilação e o upload de códigos para diferentes dispositivos, incluindo ESP32 que utilizamos em nossos projetos.

A PlataformIO é instalada com a extensão PlatformIO IDE através do Marketplace do Visual Studio Code. Após instalar, basta criar um novo projeto e selecionar a DOIT ESP32 DEVKIT V1 como Board e Espdif como Framework e finalizar. Assim, o projeto para a criação, compilação e testes dos códigos estará pronto. 

### ROS

## Microcontroladores

Microcontroladores são pequenos computadores em um chip, contendo processador, memória e periféricos de I/O. Eles controlam dispositivos automatizados e executam tarefas específicas. Uma característica chave é a comunicação com periféricos externos via GPIOs, permitindo conexão com sensores e atuadores. Além disso, possuem diversas interfaces para interagir com diversos componentes.

### ESP32
microcontrolador desenvolvido pela Espressif Systems, amplamente utilizado na indústria de Internet das Coisas (IoT) devido às suas capacidades de processamento, conectividade e periféricos integrados. Suas principais características são:
- Dual-core: Equipado com dois núcleos Tensilica Xtensa® 32-bit LX6, permitindo multitarefa eficiente e performance aprimorada, com frequência de operação configurável até 240 MHz.
- Conectividade: Oferece suporte integrado para Wi-Fi e Bluetooth, facilitando a construção de projetos de IoT com conexões sem fio robustas.

A ESP32 possui um pinout flexível, com um grande número de pinos GPIO que podem ser configurados para diferentes funções. alguns exemplos de periféricos são: GPIO, Wi-Fi, Bluetooth, UART, SPI, I2C, ADC, PWM, Interrupção e RTC.

Para a programação da ESP32, utilizaremos o ESP-IDF, na PlatformIO, o qual se trata de um conjunto de ferramentas de desenvolvimento oficial da Espressif Systems, projetado especificamente para programação avançada da família ESP32.

### Rasberry PI



