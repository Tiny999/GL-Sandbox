#pragma once
#include "../Scene.h"

#include "../Shader.h"
#include "../Model.h"

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
    unsigned int amount = 1000;
    glm::mat4* modelMatrices;

    Shader shader = Shader("shaders/instancing.vertex.glsl", "shaders/instancing.frag.glsl");
    Shader modelShader = Shader("shaders/basicModel.vertex.glsl", "shaders/basicModel.frag.glsl");

    Model planet = Model("assets/models/planet/planet.obj");
    Model rock = Model("assets/models/rock/rock.obj");
};

