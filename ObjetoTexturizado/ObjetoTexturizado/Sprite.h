#include "GL/glew.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class Sprite
{
public:
    // Construtor
    Sprite();

    // Destructor
    ~Sprite();

    void initRenderData(GLuint texture, int nAnimations = 1, int nFrames = 1, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
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

protected:
    GLuint VAO;
    GLuint texture;

    //Vari�veis 
    glm::vec3 position, size;
    float angulo;

    // Anima��o por sprite
    int nAnimations, nFrames, iAnimation;
    glm::vec2 offsetTex; 

    Shader* shader;
};