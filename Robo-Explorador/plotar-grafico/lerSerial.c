#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyACM0"  // Substitua pela sua porta serial
#define BAUD_RATE B115200            // Taxa de transmissão (115200 bps)
#define BUFFER_SIZE 1024

int main() {
    int serial_fd;
    FILE *file;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Abrir a porta serial
    serial_fd = open(SERIAL_PORT, O_RDONLY | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("Erro ao abrir a porta serial");
        return EXIT_FAILURE;
    }
    printf("Porta serial %s aberta com sucesso.\n", SERIAL_PORT);

    // Configurar a porta serial
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("Erro ao obter atributos da porta serial");
        close(serial_fd);
        return EXIT_FAILURE;
    }

    cfsetospeed(&tty, BAUD_RATE);
    cfsetispeed(&tty, BAUD_RATE);

    // Configurações de 8N1
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8 bits de dados
    tty.c_iflag &= ~IGNBRK;                         // Ignorar sinal de break
    tty.c_lflag = 0;                                // Modo não-canônico
    tty.c_oflag = 0;                                // Sem processamento de saída
    tty.c_cc[VMIN]  = 1;                            // Tempo mínimo de leitura
    tty.c_cc[VTIME] = 1;                            // Tempo máximo de leitura (0.1s)

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Desabilitar controle de fluxo de software
    tty.c_cflag |= (CLOCAL | CREAD);                // Habilitar recepção
    tty.c_cflag &= ~(PARENB | PARODD);              // Sem paridade
    tty.c_cflag &= ~CSTOPB;                         // 1 bit de parada
    
    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("Erro ao configurar a porta serial");
        close(serial_fd);
        return EXIT_FAILURE;
    }
    printf("Porta serial %s configurada com sucesso.\n", SERIAL_PORT);

    // Abrir o arquivo para escrita
    file = fopen("valores.txt", "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        close(serial_fd);
        return EXIT_FAILURE;
    }
    printf("Arquivo valores.txt aberto para escrita.\n");

    printf("Iniciando leitura da porta serial e salvando em valores.txt...\n");

    // Ler da porta serial e escrever no arquivo
    for(int i=0; i<80; i++) {
        bytes_read = read(serial_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Adicionar terminação de string
            // Escrever no arquivo usando fprintf

            if (fprintf(file, "%s", buffer) < 0) {
                perror("Erro ao escrever no arquivo");
                break;
            }
            fflush(file); // Assegura que os dados sejam escritos imediatamente
            // Imprimir no console
            printf("%s", buffer);
        } else if (bytes_read < 0) {
            perror("Erro ao ler da porta serial");
            break;
        }
        // Opcional: adicionar uma condição para sair do loop, por exemplo, após um número de leituras
    }

    // Fechar recursos
    fclose(file);
    close(serial_fd);
    printf("Recursos fechados. Programa encerrado.\n");

    return EXIT_SUCCESS;
}


