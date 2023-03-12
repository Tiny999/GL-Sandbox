#include "BasicLighting.h"

#include "../Texture.h"

void BasicLighting::Load()
{
	LoadSceneLighting();
	LoadLightBulb();
}

void BasicLighting::Render(glm::mat4 view, glm::mat4 projection)
{
	// Render Scene

	glBindVertexArray(VAO);

	sceneShader.Use();

	sceneShader.SetMat4("view", view);
	sceneShader.SetMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.f);

	sceneShader.SetMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Render LightBulb

	glBindVertexArray(lightVAO);

	lightBulbShader.Use();

	lightBulbShader.SetMat4("view", view);
	lightBulbShader.SetMat4("projection", projection);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(.2f));
	

	lightBulbShader.SetMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

}

void BasicLighting::LoadLightBulb()
{
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glGenBuffers(1, &lightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


}

void BasicLighting::LoadSceneLighting()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// TexCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	sceneShader.Use();

	Texture containerTex("assets/container.jpg");

	sceneShader.Set3Float("objectColor", 1.f, .5f, .31f);
	sceneShader.Set3Float("lightColor", 1.f, 1.f, 1.f);
}
