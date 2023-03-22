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
	shader.Use();

	

	shader.SetFloat("light.constant", 1.f);
	shader.SetFloat("light.linear", .09f);
	shader.SetFloat("light.quadratic", .032f);

	shader.Set3Float("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.Set3Float("light.diffuse", .7f, .7f, .7f);
	shader.Set3Float("light.specular", 1.0f, 1.0f, 1.0f);

	shader.SetFloat("shininess", 32.f);

	
}

void ModelLoading::Render(Camera& camera, glm::mat4& projection, float delta)
{
	shader.Use();

	glm::vec3 lightPos(1.2, 1.f, 1.f);

	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", projection);

	shader.SetVec3("viewPos", camera.Position);
	shader.SetVec3("light.position", lightPos);


	glm::mat4 modelMat = glm::mat4(1.f);
	modelMat = glm::translate(modelMat, glm::vec3(0.f));
	modelMat = glm::scale(modelMat, glm::vec3(.4f));

	shader.SetMat4("model", modelMat);

	model.Draw(shader);
}
