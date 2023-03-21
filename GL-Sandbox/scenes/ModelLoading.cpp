#include "ModelLoading.h"

ModelLoading::ModelLoading(std::string vs_path, std::string frag_path, std::string model_path)
	:
	vs_path(vs_path),
	fs_path(frag_path),
	model_path(model_path),
	shader(vs_path, frag_path),
	model(model_path.c_str())
{
	
}

void ModelLoading::Load()
{
}

void ModelLoading::Render(Camera& camera, glm::mat4& projection, float delta)
{
	shader.Use();
	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", projection);

	glm::mat4 modelMat = glm::mat4(1.f);
	modelMat = glm::translate(modelMat, glm::vec3(0.f));
	modelMat = glm::scale(modelMat, glm::vec3(.4f));

	shader.SetMat4("model", modelMat);

	model.Draw(shader);
}
