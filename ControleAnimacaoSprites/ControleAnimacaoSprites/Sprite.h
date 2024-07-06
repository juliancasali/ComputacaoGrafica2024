#include "GL/glew.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Sprite
{
public:
    // Construtor
    Sprite();

    // Destructor
    ~Sprite();

    void init(GLuint texture, int nAnimations = 1, int nFrames = 1, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
        glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), float angulo = 0.0f, glm::vec3 cor = glm::vec3(1.0, 1.0, 0.0));

    void update();
    void Draw();

    inline void setShader(Shader* shader)
    {
        this->shader = shader;
    }

    inline void setAngulo(float angulo)
    {
        this->angulo = angulo;

    }
    inline void moveRight() { 
        this->position.x += speed.x; 
    }
    inline void moveLeft() { 
        this->position.x -= speed.x;
    }

protected:
    GLuint VAO;
    GLuint texture;

    //Variáveis 
    glm::vec3 position, size;
    float angulo;

    // Animação por sprite
    int nAnimations, nFrames, iAnimation, iFrame;
    float ds, dt;
    float FPS;
    float lastTime;
    Shader* shader;
    glm::vec2 speed;
};