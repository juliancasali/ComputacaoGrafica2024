/*
Tarefa | Controle e Animação de Sprites
*/


#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "Shader.h"
#include "Sprite.h"


using namespace std;

// Dimensão da janela
const GLint WIDTH = 800, HEIGHT = 600;

Sprite sprite, sprite2, sprite3, sprite4, sprite5, sprite6;

glm::mat4 matrix = glm::mat4(1);

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLuint loadTexture(string fileTexture, int &imageWidth, int &imageHeight);


int main() {

    // Inicialização da GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria a janela Glfw
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Textura", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed no init GLEW." << std::endl;
        return EXIT_FAILURE;
    }

    // Obtendo as informações de versão
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported " << version << endl;

    //Habilitar teste de profundidade
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    //Habilitar o modo de transparância (blend - mistura de cores)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Compilando e buildando o programa de shader   
    Shader shader("VertexShader.vs", "FragmentShader.fs");
    shader.use();

    int imageWidth, imageHeight;
    

    GLuint textura1 = loadTexture("walk.PNG", imageWidth, imageHeight);
    GLuint textura2 = loadTexture("Battleground1.PNG", imageWidth, imageHeight);
    //GLuint textura3 = loadTexture("BG3.PNG");
    //GLuint textura4 = loadTexture("Arvore.PNG");


    //Criação de uma sprite
    sprite.init(textura1, 1, 6, glm::vec3(400, 300, 0.0), glm::vec3(imageWidth/ 3, imageHeight /3, 1.0), 0.0, glm::vec3(1.0, 0.0, 1.0));
    sprite.setShader(&shader);


    sprite2.init(textura2, 1, 1, glm::vec3(400, 300, 0.0), glm::vec3(imageWidth/2, imageHeight/2, 1.0), 0.0, glm::vec3(0.0, 1.0, 1.0));
    sprite2.setShader(&shader);

    //Ativando o buffer de textura 
    glActiveTexture(GL_TEXTURE0);

    //Matriz de projeção
    glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);

    //Enviando para o shader a matriz como uma var uniform
    shader.setMat4("projection", projection);

    //Matriz de transformação do objeto (matriz de modelo)
    shader.setInt("texBuffer", 0);


    // Loop da aplicação
    while (!glfwWindowShouldClose(window)) {

        // Checa se houveram eventos de input
        glfwPollEvents();


        // Definindo as dimensões da viewport 
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Limpa o buffer de cor
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //cor de fundo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sprite.setShader(&shader);
        sprite2.Draw();
        sprite.Draw();
        
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        sprite.moveLeft();

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        sprite.moveRight();
}


GLuint loadTexture(string fileTexture, int &imageWidth, int &imageHeight)
{
    std::cout << "Carregando textura..." << std::endl;
    stbi_set_flip_vertically_on_load(true);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileTexture.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        imageWidth = width;
        imageHeight = height;

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Erro ao carregar a textura" << std::endl;
        stbi_image_free(data);
    }

    cout << "Textura ok" << endl;

    return texture;
}
