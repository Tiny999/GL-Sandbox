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

	// Plane
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

	glBindVertexArray(0);


}
