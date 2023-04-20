#include "Instancing.h"
#include <GLFW/glfw3.h>

void Instancing::Load()
{
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);


	//// Set offsets
	//glm::vec2 translations[100];
	//int index = 0;
	//float offset = .1f;

	//for (int y = -10; y < 10; y += 2)
	//{
	//	for (int x = -10; x < 10; x += 2)
	//	{
	//		glm::vec2 translate;
	//		translate.x = (float)x / 10.f + offset;
	//		translate.y = (float)y / 10.f + offset;
	//		translations[index++] = translate;
	//	}
	//}

	//// Using uniforms to pass offsets

	///*shader.Use();

	//for (unsigned int i = 0; i < 100; i++)
	//{
	//	shader.SetVec2(("offsets[" + std::to_string(i) + "]"), translations[i]);
	//}*/

	//// Using Instance Array

	//glGenBuffers(1, &instanceVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations, GL_STATIC_DRAW);

	//glVertexAttribPointer(2, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glVertexAttribDivisor(2, 1);

	
	modelMatrices = new glm::mat4[amount];
	srand(2);

	float radius = 50.f;
	float offset = 2.5f;

	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.f);

		// translate
		float angle = (float)i / (float)amount * 360.f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.f - offset;
		float y = displacement * .4f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// Scale
		float scale = (rand() % 20) / 100.f + 0.05f;
		model = glm::scale(model, glm::vec3(scale));

		// Rotate
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(.4f, .6f, .8f));

		modelMatrices[i] = model;
	}
}

void Instancing::Render(Camera& camera, glm::mat4& projection, float delta)
{
	
	modelShader.Use();


	modelShader.SetMat4("projection", projection);
	modelShader.SetMat4("view", camera.GetViewMatrix());

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
	model = glm::scale(model, glm::vec3(4.0f));
	modelShader.SetMat4("model", model);

	rock.Draw(modelShader);


	/*for (unsigned int i = 0; i < amount; i++)
	{
		modelShader.SetMat4("model", modelMatrices[i]);
		rock.Draw(modelShader);
	}*/
}

void Instancing::CleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
}
