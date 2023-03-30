#include "Instancing.h"

void Instancing::Load()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// Set offsets
	glm::vec2 translations[100];
	int index = 0;
	float offset = .1f;

	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translate;
			translate.x = (float)x / 10.f + offset;
			translate.y = (float)y / 10.f + offset;
			translations[index++] = translate;
		}
	}

	// Using uniforms to pass offsets

	/*shader.Use();

	for (unsigned int i = 0; i < 100; i++)
	{
		shader.SetVec2(("offsets[" + std::to_string(i) + "]"), translations[i]);
	}*/

	// Using Instance Array

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);

}

void Instancing::Render(Camera& camera, glm::mat4& projection, float delta)
{
	glBindVertexArray(VAO);
	shader.Use();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

	glBindVertexArray(0);

}

void Instancing::CleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
}
