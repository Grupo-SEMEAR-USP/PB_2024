#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

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
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    
    // Eixo Y
    glVertex2f(0.0, -10.0);
    glVertex2f(0.0, 10.0);
    
    glEnd();

    // Desenhar marcações e valores no eixo X
    for (float x = -10.0; x <= 10.0; x += 1.0) {
        glBegin(GL_LINES);
        glVertex2f(x, -0.2); // Marcações no eixo X (parte abaixo do eixo)
        glVertex2f(x, 0.2);  // (parte acima do eixo)
        glEnd();
        
        // Desenha os números para as marcações
        if (x != 0) { // Não desenha o zero no centro
            char texto[10];
            sprintf(texto, "%.0f", x);
            desenhaTexto(texto, x - 0.1, -0.5); // Ajusta a posição do texto
        }
    }

    // Desenhar marcações e valores no eixo Y
    for (float y = -10.0; y <= 10.0; y += 1.0) {
        glBegin(GL_LINES);
        glVertex2f(-0.2, y); // Marcações no eixo Y (parte abaixo do eixo)
        glVertex2f(0.2, y);  // (parte acima do eixo)
        glEnd();
        
        // Desenha os números para as marcações
        if (y != 0) { // Não desenha o zero no centro
            char texto[10];
            sprintf(texto, "%.0f", y);

            float offset_eixoY = -0.5;
            if(y < 0) offset_eixoY = -0.7;
            desenhaTexto(texto, offset_eixoY, y - 0.1); // Ajusta a posição do texto
        }
    }
}

// Função para desenhar o gráfico
void desenhaGrafico() {
    glColor3f(0.0, 0.0, 1.0); // Cor azul para o gráfico
    glBegin(GL_LINE_STRIP);
    
    // Plotando a função seno no intervalo [-10, 10]
    for (float x = -10.0; x <= 10.0; x += 1) {
        glVertex2f(x, funcao());
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
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Define a área de visualização (janela)
}

int main(int argc, char **argv) {
    fp = fopen("valores.txt", "r");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600); // Tamanho da janela
    glutCreateWindow("Grafico com Atualizacao em OpenGL");
    
    inicializa();
    
    glutDisplayFunc(display);          // Registra a função de renderização

    glutMainLoop();
    fclose(fp);
    
    return 0;
}
