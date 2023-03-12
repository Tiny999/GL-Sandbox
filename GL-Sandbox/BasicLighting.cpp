#include "BasicLighting.h"

void BasicLighting::Load()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void BasicLighting::Render(glm::mat4 view, glm::mat4 projection)
{
	sceneShader.Use();

	sceneShader.SetMat4("view", view);
	sceneShader.SetMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));

	sceneShader.SetMat4("model", model);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}
