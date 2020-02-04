#pragma once

#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"
#include "Renderer.h"

class DrawableModel :
	public Component
{
public:
	DrawableModel();
	void Tick(float deltaTime);
	~DrawableModel();

	void SetRenderer(Renderer r);

	void SetModel(Model m);
	void SetShader(Shader s);
	void SetMaterial(Material m);
	void SetTransform(Transform t);
	void SetScale(glm::vec3 s);

	Model GetModel();
	Shader GetShader();
	Material GetMaterial();
	Transform GetTransform();
	glm::vec3 GetScale();

	glm::mat4 CalculateModelMatrix();

private:
	Model model;
	Shader shader;
	Material material;
	Transform transform;
	glm::vec3 scale;

	Renderer renderer;
};

