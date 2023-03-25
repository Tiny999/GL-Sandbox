#include "DepthTest.h"

void DepthTest::Load()
{
	// Cube
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glGenBuffers(1, &cubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Plane (Floor)
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);

	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Transparent Quad
	glGenVertexArrays(1, &transparentVAO);
	glBindVertexArray(transparentVAO);

	glGenBuffers(1, &transparentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	shader.Use();
	shader.SetInt("texture1", 0);
	

}

void DepthTest::Render(Camera& camera, glm::mat4& projection, float delta)
{
	shader.Use();

	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.f);

	// Draw Cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	cubeTexture.Use();

	model = glm::translate(model, glm::vec3(-1.f, 0.f, -1.f));
	shader.SetMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(2.f, 0.f, 0.f));
	shader.SetMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// floor
	glBindVertexArray(planeVAO);
	model = glm::mat4(1.f);
	planeTexture.Use();
	shader.SetMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// Draw Windows
	glBindVertexArray(transparentVAO);
	windowTexture.Use();

	// Change wrapping for alpha texture types
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Sort windows by distance from lookat point
	std::map<float, glm::vec3> sorted;

	for (unsigned int i = 0; i < 5; i++)
	{
		float distance = glm::length(camera.Position - vegetation[i]);
		sorted[distance] = vegetation[i];
	}

	/*for (unsigned int i = 0; i < 5; i++)
	{
		
	}*/

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = glm::mat4(1.f);
		model = glm::translate(model, it->second);
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);


}
