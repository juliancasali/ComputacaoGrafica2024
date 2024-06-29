#include "Sprite.h"
#include <GLFW/glfw3.h>

enum movement { LEFT, RIGHT };


Sprite::Sprite() { }

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &VAO);
}

void Sprite::init(GLuint texture, int nAnimations, int nFrames, glm::vec3 position, glm::vec3 size, float angulo, glm::vec3 cor)
{
    this->texture = texture;
    this->position = position;
    this->size.x = size.x / (float)nFrames;
    this->size.y = size.y / (float)nAnimations;
    this->angulo = angulo;
    this->nAnimations = nAnimations;
    this->nFrames = nFrames;

    speed.x = 10.0;
    speed.y = 10.0;

    ds = 1.0 / (float)nFrames;
    dt = 1.0 / (float)nAnimations;

    //iFrame = ds + 1;

    GLfloat vertices[] = {

        //Triangulo 1
        // positions             cor           textura
        // x    y   z       r    g      b       s   t
        -0.5 , 0.5, 0.0, cor.r, cor.g, cor.b, 0.0, dt,
        -0.5 ,-0.5, 0.0, cor.r, cor.g, cor.b, 0.0, 0.0,
         0.5 , 0.5, 0.0, cor.r, cor.g, cor.b, ds, dt,

         //Triangulo 2
         // positions             cor           textura
         // x    y   z       r    g      b       s   t	
         -0.5 ,-0.5, 0.0, cor.r, cor.g, cor.b, 0.0, 0.0,
          0.5 ,-0.5, 0.0, cor.r, cor.g, cor.b, ds, 0.0,
          0.5 , 0.5, 0.0, cor.r, cor.g, cor.b, ds, dt
    };

    // configure VAO/VBO
    GLuint VBO;

    //Geração do identificador do VBO
    glGenBuffers(1, &VBO);

    //Faz a conexão (vincula) do buffer como um buffer de array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Envia os dados do array de floats para o buffer da OpenGl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Geração do identificador do VAO (Vertex Array Object)
    glGenVertexArrays(1, &this->VAO);

    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
    // e os ponteiros para os atributos 
    glBindVertexArray(this->VAO);

    //Atributo 0 - posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Atributo 1 - cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Atributo 2 - coordenadas de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desvincula o VAO
    glBindVertexArray(0);

}

void Sprite::update()
{
    
    iFrame = (iFrame + 1) % nFrames;

    float offsetS = iFrame + ds;
    float offsetT = iAnimation + dt;
    this->shader->setVec2("offsetTex", offsetS, offsetT);

    

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
   // if (isMirroded)
    //    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, size);

    this->shader->setMat4("model", model);
}

void Sprite::Draw()
{
    update();

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Sprite::morroIt()
{
}
