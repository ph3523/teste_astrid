#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <set>
#include <random>

// Definição dos vértices da estrela
float v1[3] = {-35.0f, 22.5f, 0.0f};
float v2[3] = {-35.0f, -22.5f, 0.0f};
float v3[3] = {0.0f, 42.5f, 0.0f};
float v4[3] = {0.0f, -42.5f, 0.0f};
float v5[3] = {35.0f, 22.5f, 0.0f};
float v6[3] = {35.0f, -22.5f, 0.0f};

// Variáveis para o centro da estrela e rotação
float px = {250}, py = {100}; // Coordenadas do ponto de destino
float center_s[3] = {0.0f, 0.0f, 0.0f};
float center_d[3] = {px, py, 0.0f};
static GLfloat spin = 0.0; // Ângulo de rotação

// Variáveis para cor e modo
float x = -10.0f, y = 500.0f;         // Coordenadas da estrela
float color1[3] = {1.0f, 1.0f, 1.0f}; // Cor do primeiro triângulo
float color2[3] = {1.0f, 1.0f, 1.0f}; // Cor do segundo triângulo
int mode = 1;                         // Modo para alterar cores
int rotate = 1;                       // Modo para rotação

// Variáveis para tempo e velocidade
int timeLastFrame = 0; // Registro do tempo da última moldura
float speed = 100.0f; // Velocidade de movimento

// Função e protótipos
void init(void);
void triangle_1(void);
void triangle_2(void);
void lines(void);
void display(void);
void spinDisplay_1(void);
void spinDisplay_2(void);
void reshape(int, int);
void changeColor(int);
void mouse(int, int, int, int);
void closeWindow(unsigned char key, int x, int y);
void calculoDir(void);

// Função para fechar a janela quando a tecla "Esc" é pressionada
void closeWindow(unsigned char key, int x, int y)
{
    if (key == 27)
    {            // 27 é o código ASCII para a tecla "Esc"
        exit(0); // Fecha o programa
    }
}

// Função principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(341, 0);
    glutCreateWindow("6-Point Star");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(closeWindow); // Registra a função para lidar com pressionamento de teclas
    //glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

// Inicializa o ambiente OpenGL
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo
    glShadeModel(GL_FLAT);            // Define o modelo de sombreamento
}

// Função para desenhar o primeiro triângulo da estrela
void triangle_1(void)
{
    glColor3fv(color1); // Define a cor do primeiro triângulo

    glBegin(GL_TRIANGLE_FAN); // Começa a definir um triângulo
    glVertex3fv(v1);
    glVertex3fv(v4);
    glVertex3fv(v5);
    glEnd();
}

// Função para desenhar o segundo triângulo da estrela
void triangle_2(void)
{
    glColor3fv(color2); // Define a cor do segundo triângulo

    glBegin(GL_TRIANGLE_FAN); // Começa a definir um triângulo
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v6);
    glEnd();
}

// Função para desenhar as linhas conectando os triângulos e um ponto
void lines(void)
{
    glColor3f(1.0, 0.0, 0.0); // Define a cor vermelha

    glPointSize(5);     // Define o tamanho do ponto
    glBegin(GL_POINTS); // Começa a definir um ponto
    glVertex2f(px, py); // Desenha o ponto
    glEnd();

    glLineWidth(1);     // Define a largura da linha
    glBegin(GL_LINES);  // Começa a definir uma linha
    glVertex2f(x, y);   // Ponto de partida da linha
    glVertex2f(px, py); // Ponto de destino da linha
    glEnd();
}

void calculoDir(float length)
{
    if (length < 1.0f)
    {
        srand(time(NULL)); // Semente para o gerador de números aleatórios
        int max = 600;
        int min = -100;
        x = rand() % (max - min + 1) + min; // Gera um novo valor de x
        y = 620;

        // y = rand() % 500;
        // x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 500.0f;
        // y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 500.0f;

        std::cout << "x: " << x << " "
                  << "y: " << y << std::endl;
    }
}

// Função de exibição
void display(void)
{
    // Calcula o tempo desde a última moldura
    int timeNow = glutGet(GLUT_ELAPSED_TIME);
    float delta = (float)(timeNow - timeLastFrame) / 1000.0f;
    timeLastFrame = timeNow;

    // Calcula a direção e a distância até o ponto de destino
    float dx = px - x;
    float dy = py - y;

    // Calcula o comprimento do vetor direção
    float length = sqrt(dx * dx + dy * dy);

    // Normaliza o vetor direção
    dx /= length;
    dy /= length;

    // Move a estrela em direção ao ponto de destino com base na velocidade
    if (length > 1.0f)
    {
        x += dx * speed * delta;
        y += dy * speed * delta;
    }
    // Gera uma nova posição aleatória se a estrela estiver próxima o suficiente do ponto de destino
    if (length < 1.0f)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        // srand(time(NULL)); // Semente para o gerador de números aleatórios
        int max = glutGet(GLUT_WINDOW_WIDTH) + 100;
        int min = glutGet(GLUT_WINDOW_WIDTH) - (glutGet(GLUT_WINDOW_WIDTH) + 100);
        std::cout << "max: " << max << " "
                  << "min: " << min << std::endl;
        // x = rand() % (max - min + 1) + min; // Gera um novo valor de x
        std::uniform_int_distribution<int> dis(min, max);
        x = dis(gen);
        y = 550;

        if (x < 0)
        {
            int max = glutGet(GLUT_WINDOW_WIDTH) + 10;
            int min = glutGet(GLUT_WINDOW_WIDTH) /2;
            // y = rand() % (max - min + 1) + min;
            std::uniform_int_distribution<int> dis(min, max);
            y = dis(gen);
        }

        // y = rand() % 500;
        // x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 500.0f;
        // y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 500.0f;

        std::cout << "x: " << x << " "
                  << "y: " << y << std::endl;
    }

    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de tela

    glPushMatrix();
    glTranslatef(x, y, 0.0f);       // Translada a estrela para a posição (x, y)
    glRotatef(spin, 0.0, 0.0, 1.0); // Aplica a rotação
    triangle_1();                   // Desenha o primeiro triângulo
    triangle_2();                   // Desenha o segundo triângulo
    glPopMatrix();

    lines(); // Desenha as linhas

    glutSwapBuffers(); // Troca os buffers de tela para exibir o desenho

    glutPostRedisplay(); // Solicita a próxima atualização da tela
}

// Função de rotação no sentido horário
void spinDisplay_1(void)
{
    spin = spin + 2.0;

    if (spin > 360.0)
    {
        spin = spin - 360.0;
    }

    glutPostRedisplay(); // Solicita a próxima atualização da tela
}

// Função de rotação no sentido anti-horário
void spinDisplay_2(void)
{
    spin = spin - 2.0;

    if (spin < 360.0)
    {
        spin = spin + 360.0;
    }

    glutPostRedisplay(); // Solicita a próxima atualização da tela
}

// Função de remodelar a janela
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Define a área de visualização
    glMatrixMode(GL_PROJECTION);              // Define o modo da matriz como projeção
    glLoadIdentity();                         // Carrega uma matriz de identidade
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);       // Define a projeção ortogonal
    glMatrixMode(GL_MODELVIEW);               // Retorna ao modo de matriz de modelo
    glLoadIdentity();                         // Carrega uma matriz de identidade
}

// Função para mudar a cor dos triângulos da estrela
void changeColor(int n)
{
    if (n == 1)
    {
        color1[0] = 0.0f, color1[1] = 0.0f, color1[2] = 1.0f; // Altera a cor do primeiro triângulo
        color2[0] = 0.0f, color2[1] = 1.0f, color2[2] = 0.0f; // Altera a cor do segundo triângulo
    }
    else if (n == 2)
    {
        color1[0] = 1.0f, color1[1] = 1.0f, color1[2] = 1.0f; // Restaura a cor do primeiro triângulo
        color2[0] = 1.0f, color2[1] = 1.0f, color2[2] = 1.0f; // Restaura a cor do segundo triângulo
    }
}

// Função para eventos de mouse
void mouse(int button, int state, int mx, int my)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON: // Botão esquerdo do mouse
        if (state == GLUT_DOWN)
        {
            px = mx;
            py = glutGet(GLUT_WINDOW_HEIGHT) - my;
        }
        glutPostRedisplay();
        std::cout << "px: " << px << " "
                  << "py: " << py << std::endl;

        break;
    case GLUT_MIDDLE_BUTTON: // Botão do meio do mouse
        if (state == GLUT_DOWN)
        {
            if (mode == 1)
            {
                changeColor(mode);
                mode = 2;
            }
            else if (mode == 2)
            {
                changeColor(mode);
                mode = 1;
            }
        }
        glutPostRedisplay();
        break;
    case GLUT_RIGHT_BUTTON: // Botão direito do mouse
        if (state == GLUT_DOWN)
            if (rotate == 1)
            {
                glutIdleFunc(spinDisplay_1); // Inicia a rotação no sentido horário
                rotate = 2;
            }
            else if (rotate == 2)
            {
                glutIdleFunc(spinDisplay_2); // Inicia a rotação no sentido anti-horário
                rotate = 1;
            }
        break;
    default:
        break;
    }
}
