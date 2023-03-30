#pragma once
#include "../Scene.h"

#include "../Shader.h"

class Instancing :
    public Scene
{
public:
    Instancing() = default;
    virtual void Load() override;
    virtual void Render(Camera& camera, glm::mat4& projection, float delta) override;
    virtual void CleanUp() override;
private:
    float quadVertices[30] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    unsigned int VAO, VBO, instanceVBO;


    Shader shader = Shader("shaders/instancing.vertex.glsl", "shaders/instancing.frag.glsl");
};

