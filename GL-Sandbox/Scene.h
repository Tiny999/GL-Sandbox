#pragma once

#include <glad/glad.h>

#include "Camera.h"

class Scene
{
public:
	virtual void Load() = 0;
	virtual void Render(glm::mat4 view, glm::mat4 projection) = 0;
};

