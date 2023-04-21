#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"

class ShadowMapping :
    public Scene
{
public:
	void Load();
	void Render(Camera& camera, glm::mat4& projection, float delta);
	void CleanUp();

private:
	unsigned int depthMapFBO, depthMap, planeVAO, planeVBO;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	float planeVertices[48] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};

	Shader simpleDepthShader = Shader("shaders/simpleDepthShader.vertex.glsl", "shaders/simpleDepthShader.frag.glsl");
	Shader debugQuadShader = Shader("shaders/debugQuad.vertex.glsl", "shaders/debugQuad.frag.glsl");
	Shader shader = Shader("shaders/shadowMapping.vertex.glsl", "shaders/shadowMapping.frag.glsl");

	Texture woodTexture = Texture("assets/wood.png");

	glm::vec3 lightPos = glm::vec3(- 2.0f, 4.0f, -1.0f);

	void RenderScene(Shader& shader);
	void RenderQuad();
	void RenderCube();
};