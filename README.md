# PB_2024

### [RMA] Projeto dos Bixos 2024 - SEMEAR
Este é o repositório do Projeto dos Bixos do núcleo de Robótica Móvel Autonoma [RMA] do grupo SEMEAR, vinculado à Universidade de São Paulo. Nosso time tem o objetivo de construir um robô autônomo de reconhecimento de áreas, também conhecido como robô explorador. 

  **Os códigos utilizados para executar as tarefas e análises do projeto estão documentados neste repositório.**

### Objetivos do robô:
- Deslocar-se de forma terrestre e totalmente autônoma;
- Explorar o ambiente desconhecido;
- Ter um sistema de localização minimamente preciso;
- Não colidir com os objetos;
- Gerar um mapa em tempo real do ambiente;
- Encontrar as rotas mais otimizadas ao planejar trajetórias.
- Ausência de tempo máximo para a exploração.


> O projeto abrange atuações em mecânica, eletrônica e programação, juntas elas devem funcionar em harmonia.

*[Exemplo: Perseverence, robô explorador da Nasa]*

![Perseverence, robô explorador da Nasa](https://s2.glbimg.com/BYR-XBxo73uWsG6s5jsWnZDdlRg=/620x350/e.glbimg.com/og/ed/f/original/2021/02/18/117021449_diana6.jpg)

## Ferramentas

### Ubuntu 20.04 LTS
A instalação desta distro do Linux é muito importante devido à sua grande compatibilidade com as ferramentas ROS (Robot Operating System) e o ESP-IDF (Espressif IoT Development Framework), as quais são essênciais para o nosso projeto.

Para baixar, acesse o link [Ubuntu](https://ubuntu.com/download)

### PlataformIO
PlatformIO é uma plataforma de desenvolvimento de código aberto para programação de microcontroladores e sistemas embarcados. Ela suporta uma ampla gama de placas e frameworks, facilitando a compilação e o upload de códigos para diferentes dispositivos, incluindo ESP32 que utilizamos em nossos projetos.

A PlataformIO é instalada com a extensão PlatformIO IDE através do Marketplace do Visual Studio Code. Após instalar, basta criar um novo projeto e selecionar a DOIT ESP32 DEVKIT V1 como Board e Espdif como Framework e finalizar. Assim, o projeto para a criação, compilação e testes dos códigos estará pronto. 

![PlataformIO](https://files.seeedstudio.com/wiki/platformIO/platformIO-2.png)

### ROS

## Microcontroladores

Microcontroladores são circuitos integrados que funcionam como pequenos computadores. Eles contêm um processador, memória e periféricos de entrada/saída (I/O) em um único chip. Sua principal função é controlar outros dispositivos ou sistemas automatizados. Os microcontroladores são projetados para executar tarefas específicas e repetitivas. Diferem dos microprocessadores, que são mais potentes e utilizados em computadores para executar uma ampla gama de aplicações. Uma característica importante dos microcontroladores é sua capacidade de se comunicar com periféricos externos. Eles possuem GPIOs (General Purpose Input/Output), que permitem a conexão de sensores, atuadores e outros dispositivos. Além disso, podem incluir interfaces como UARTs, SPI (Serial Peripheral Interface), I2C (Inter Integrated Circuit), ADCs (Analog to Digital Converters) e PWMs (Pulse Width Modulation), permitindo a interação com uma ampla gama de componentes e sensores.

### ESP32
microcontrolador desenvolvido pela Espressif Systems, amplamente utilizado na indústria de Internet das Coisas (IoT) devido às suas capacidades de processamento, conectividade e periféricos integrados. Suas principais características são:
- Dual-core: Equipado com dois núcleos Tensilica Xtensa® 32-bit LX6, permitindo multitarefa eficiente e performance aprimorada, com frequência de operação configurável até 240 MHz
- Conectividade: Oferece suporte integrado para Wi-Fi e Bluetooth, facilitando a construção de projetos de IoT com conexões sem fio robustas.

A ESP32 possui um pinout flexível, com um grande número de pinos GPIO que podem ser configurados para diferentes funções. alguns exemplos de periféricos são: GPIO (General Purpose Input/Output), Wi-Fi, Bluetooth, UART (Universal Asynchronous Receiver/Transmitter), SPI (Serial Peripheral Interface), I2C (Inter-Integrated Circuit), ADC (Analog-to-Digital Converter), PWM (Pulse Width Modulation), Interrupção e RTC (Real-Time Clock).

Para a programação da ESP32, utilizaremos o ESP-IDF, na PlatformIO, o qual se trata de um conjunto de ferramentas de desenvolvimento oficial da Espressif Systems, projetado especificamente para programação avançada da família ESP32.

![ESP32](https://cdn.awsli.com.br/78/78150/produto/18299352/placa_esp32_devkit_v1-xgqfiy1x77.png)

### Rasberry PI



