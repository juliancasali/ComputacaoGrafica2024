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

    void DrawSprite(GLuint texture, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
        glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), float rotate = 0.0f);

    inline void setShader(Shader* shader)
    {
        this->shader = shader;
    }

    void initRenderData();

protected:
    GLuint VAO;
    GLuint texture;

    //Variáveis 
    glm::vec2 position, size;
    float rotate;

    Shader* shader;
};