#include "BasicLighting.h"

void BasicLighting::Load()
{
	LoadSceneLighting();
	LoadLightBulb();
}

void BasicLighting::Render(Camera& camera, glm::mat4& projection)
{
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


	// Render Scene

	glBindVertexArray(VAO);

	sceneShader.Use();

	sceneShader.SetMat4("view", camera.GetViewMatrix());
	sceneShader.SetMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.f);

	sceneShader.SetMat4("model", model);
	sceneShader.SetVec3("lightPos", lightPos);
	sceneShader.SetVec3("viewPos", camera.Position);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Render LightBulb

	glBindVertexArray(lightVAO);

	lightBulbShader.Use();

	lightBulbShader.SetMat4("view", camera.GetViewMatrix());
	lightBulbShader.SetMat4("projection", projection);


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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	sceneShader.Use();

	sceneShader.Set3Float("objectColor", 1.f, .5f, .31f);
	sceneShader.Set3Float("lightColor", 1.f, 1.f, 1.f);
}
