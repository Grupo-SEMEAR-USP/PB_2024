#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// tamanho da janela do gráfico
#define WIDTH 1200
#define HEIGHT 1200

// limites do gráfico
#define LIM_ESQ -5.0
#define LIM_DIR 200.0
#define LIM_BAIXO -5.0
#define LIM_CIMA 200.0


// Função para salvar a tela em um arquivo BMP
void salvaBMP(const char *filename, int width, int height) {
    FILE *f;
    unsigned char *img = (unsigned char *)malloc(3 * width * height); // Buffer de imagem

    // Ler os pixels da janela atual
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);

    // Criar um arquivo BMP
    f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Erro ao criar o arquivo BMP.\n");
        free(img);
        return;
    }

    unsigned char bmpfileheader[14] = {
        'B', 'M',        // Tipo de arquivo
        0, 0, 0, 0,      // Tamanho do arquivo (ajustado mais tarde)
        0, 0, 0, 0,      // Reservado
        54, 0, 0, 0      // Offset da imagem
    };
    
    unsigned char bmpinfoheader[40] = {
        40, 0, 0, 0,     // Tamanho do cabeçalho
        0, 0, 0, 0,      // Largura da imagem
        0, 0, 0, 0,      // Altura da imagem
        1, 0,            // Planos de cor (sempre 1)
        24, 0,           // Bits por pixel (24 bits = RGB)
        0, 0, 0, 0,      // Compressão (sem compressão)
        0, 0, 0, 0,      // Tamanho da imagem (pode ser 0 sem compressão)
        0, 0, 0, 0,      // Resolução horizontal (não usada)
        0, 0, 0, 0,      // Resolução vertical (não usada)
        0, 0, 0, 0,      // Cores na paleta (não usada)
        0, 0, 0, 0       // Cores importantes (não usada)
    };

    // Preenche a largura e altura nos cabeçalhos BMP
    bmpinfoheader[4] = (unsigned char)(width);
    bmpinfoheader[5] = (unsigned char)(width >> 8);
    bmpinfoheader[6] = (unsigned char)(width >> 16);
    bmpinfoheader[7] = (unsigned char)(width >> 24);
    bmpinfoheader[8] = (unsigned char)(height);
    bmpinfoheader[9] = (unsigned char)(height >> 8);
    bmpinfoheader[10] = (unsigned char)(height >> 16);
    bmpinfoheader[11] = (unsigned char)(height >> 24);

    // Calcula o tamanho do arquivo BMP
    int filesize = 54 + 3 * width * height;  // 54 é o cabeçalho, 3 é para RGB
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    // Escreve os cabeçalhos no arquivo
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);

    // A imagem no OpenGL é invertida verticalmente, então invertemos ao salvar
    for (int y = 0; y < height; y++) {
        fwrite(img + (y * width * 3), 3, width, f);
    }

    fclose(f);
    free(img);

    printf("Imagem salva como %s\n", filename);
}

void teclado(unsigned char key, int x, int y) {
    if (key == 's') {
        salvaBMP("grafico.bmp", WIDTH, HEIGHT);  // Salva o gráfico quando a tecla 's' é pressionada
    }
}

FILE *fp;

// Função que será plotada
float funcao() {
    float a;
    if(fscanf(fp, "%f", &a) == EOF) return -1; // se alcançar final de arquivo

    return a; 
}

// Função para desenhar texto em uma posição
void desenhaTexto(const char* texto, float x, float y) {
    glRasterPos2f(x, y); // Define a posição do texto
    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *texto);
        texto++;
    }
}

// Função para desenhar os eixos X e Y com marcações e valores
void desenhaEixosComMarcacoesEValores() {
    glColor3f(0.0, 0.0, 0.0); // Cor preta para os eixos
    glBegin(GL_LINES);
    
    // Eixo X
    glVertex2f(LIM_ESQ, 0.0);
    glVertex2f(LIM_DIR, 0.0);
    
    // Eixo Y
    glVertex2f(0.0, LIM_BAIXO);
    glVertex2f(0.0, LIM_CIMA);
    
    glEnd();

    // Desenhar marcações e valores no eixo X
    for (float x = LIM_ESQ; x <= LIM_DIR; x += 1.0) {
        glBegin(GL_LINES);
        glVertex2f(x, -0.2); // Marcações no eixo X (parte abaixo do eixo)
        glVertex2f(x, 0.2);  // (parte acima do eixo)
        glEnd();
        
        // Desenha os números para as marcações
        if (x != 0 && (int)x%10 == 0) { // Só coloca o valor nos múltiplos de 10
            char texto[10];
            sprintf(texto, "%.0f", x);
            desenhaTexto(texto, x - 0.1, -2.0); // Ajusta a posição do texto
        }
    }

    // Desenhar marcações e valores no eixo Y
    for (float y = LIM_BAIXO; y <= LIM_CIMA; y += 1.0) {
        glBegin(GL_LINES);
        glVertex2f(-0.2, y); // Marcações no eixo Y (parte abaixo do eixo)
        glVertex2f(0.2, y);  // (parte acima do eixo)
        glEnd();
        
        // Desenha os números para as marcações
        if (y != 0 && (int)y%10 == 0) { // Só coloca o valor nos múltiplos de 10
            char texto[10];
            sprintf(texto, "%.0f", y);

            float offset_eixoY = -1.5;
            if(y < 0) offset_eixoY = -1.7;
            if(y >= 10) offset_eixoY -= 1.0;
            if(y >= 100) offset_eixoY -= 1.0;
            desenhaTexto(texto, offset_eixoY, y - 0.1); // Ajusta a posição do texto
        }
    }
}

// Função para desenhar o gráfico
void desenhaGrafico() {
    glColor3f(0.0, 0.0, 1.0); // Cor azul para o gráfico
    glBegin(GL_LINE_STRIP);
    
    // Plotando a função até que acabe os elementos do arquivo (y == -1)
    for (float x = 0.0; ; x += 1) {
        float y = funcao(); 
        if(y == -1) break;  
        glVertex2f(x, y);   // Plota o ponto no gráfico
    }
    
    glEnd();
}

// Função de renderização
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    desenhaEixosComMarcacoesEValores();
    desenhaGrafico();
    
    glFlush(); // Garante que todos os comandos OpenGL sejam executados
}

// Função para ajustar o sistema de coordenadas
void inicializa() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Define cor de fundo branca
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(LIM_ESQ, LIM_DIR, LIM_BAIXO, LIM_CIMA); // Define a área de visualização (janela)
}

int main(int argc, char **argv) {
    fp = fopen("valores.txt", "r");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT); // Tamanho da janela
    glutCreateWindow("Grafico com Atualizacao em OpenGL");
    
    inicializa();
    
    glutKeyboardFunc(teclado);  // Registra a função de teclado
    glutDisplayFunc(display);          // Registra a função de renderização

    glutMainLoop();
    fclose(fp);
    
    return 0;
}
