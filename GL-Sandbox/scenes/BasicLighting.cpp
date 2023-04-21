#include "BasicLighting.h"

void BasicLighting::Load()
{
	LoadSceneLighting();
	LoadLightBulb();
}

void BasicLighting::Render(Camera& camera, glm::mat4& projection, float delta)
{
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


	// Render Scene

	glBindVertexArray(VAO);

	sceneShader.Use();

	sceneShader.SetMat4("view", camera.GetViewMatrix());
	sceneShader.SetMat4("projection", projection);
	sceneShader.Set3Float("light.direction", -0.2f, -1.0f, -0.3f);
	sceneShader.SetVec3("viewPos", camera.Position);

	// PointLight
	sceneShader.SetVec3("pointLight.position", lightPos);

	// Spotlight
	sceneShader.SetVec3("spotLight.position", camera.Position);
	sceneShader.SetVec3("spotLight.direction", camera.Front);
	sceneShader.SetFloat("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
	sceneShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));


	glm::mat4 model = glm::mat4(1.f);
	

	for (unsigned int i = 0; i < 10; i++)
	{
		model = glm::mat4(1.f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.f, .3f, .5f));
		sceneShader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	

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

void BasicLighting::CleanUp()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &lightVBO);

}

void BasicLighting::LoadLightBulb()
{
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glGenBuffers(1, &lightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// TexCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	sceneShader.Use();

	// Material
	sceneShader.Set3Float("material.ambient", 1.0f, 0.5f, 0.31f);
	sceneShader.Set3Float("material.diffuse", 1.0f, 0.5f, 0.31f);
	sceneShader.Set3Float("material.specular", 0.5f, 0.5f, 0.5f);
	sceneShader.SetFloat("material.shininess", 32.0f);

	// Light
	sceneShader.Set3Float("light.ambient", 0.2f, 0.2f, 0.2f);
	sceneShader.Set3Float("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
	sceneShader.Set3Float("light.specular", 1.0f, 1.0f, 1.0f);

	// PointLight
	sceneShader.SetFloat("pointLight.constant", 1.f);
	sceneShader.SetFloat("pointLight.linear", .09f);
	sceneShader.SetFloat("pointLight.quadratic", .032f);

	sceneShader.Set3Float("pointLight.ambient", 0.2f, 0.2f, 0.2f);
	sceneShader.Set3Float("pointLight.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
	sceneShader.Set3Float("pointLight.specular", 1.0f, 1.0f, 1.0f);

	// SpotLight
	sceneShader.Set3Float("spotLight.ambient", 0.2f, 0.2f, 0.2f);
	sceneShader.Set3Float("spotLight.diffuse", 0.5f, 0.5f, 0.5f); 
	sceneShader.Set3Float("spotLight.specular", 1.0f, 1.0f, 1.0f);

	sceneShader.SetFloat("spotLight.constant", 1.f);
	sceneShader.SetFloat("spotLight.linear", .09f);
	sceneShader.SetFloat("spotLight.quadratic", .032f);

	// Textures
	Texture containerTex("assets/container2.png");
	glActiveTexture(GL_TEXTURE0);
	containerTex.Use();

	glActiveTexture(GL_TEXTURE1);
	Texture containerSpecular("assets/container2_specular.png");
	sceneShader.SetInt("material.specular", 1);
	containerSpecular.Use();



}
