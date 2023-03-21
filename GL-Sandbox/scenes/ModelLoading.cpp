#include "ModelLoading.h"

void ModelLoading::Load()
{

}

void ModelLoading::Render(Camera& camera, glm::mat4& projection, float delta)
{
	shader.Use();
	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(0.f));
	model = glm::scale(model, glm::vec3(.4f));

	shader.SetMat4("model", model);

	backpackModel.Draw(shader);
}
