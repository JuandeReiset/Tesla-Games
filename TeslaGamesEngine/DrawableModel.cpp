#include "DrawableModel.h"

DrawableModel::DrawableModel()
{
	model = Model();
	shader = Shader();
	material = Material();
	transform = Transform();
	scale = glm::vec3(1.0f);

	renderer = Renderer();
}

void DrawableModel::Tick(float deltaTime)
{
	renderer.DrawModel(model, shader, material, CalculateModelMatrix());
}

void DrawableModel::SetModel(Model m)
{
	model = m;
}

void DrawableModel::SetShader(Shader s)
{
	shader = s;
}

void DrawableModel::SetMaterial(Material m)
{
	material = m;
}

void DrawableModel::SetTransform(Transform t)
{
	transform = t;
}

void DrawableModel::SetScale(glm::vec3 s)
{
	scale = s;
}

Model DrawableModel::GetModel()
{
	return model;
}

Shader DrawableModel::GetShader()
{
	return shader;
}

Material DrawableModel::GetMaterial()
{
	return material;
}

Transform DrawableModel::GetTransform()
{
	return transform;
}

glm::vec3 DrawableModel::GetScale()
{
	return scale;
}

glm::mat4 DrawableModel::CalculateModelMatrix()
{
	// Rotation * Translation * Scale
	return glm::mat4();
}

DrawableModel::~DrawableModel()
{
}

void DrawableModel::SetRenderer(Renderer r)
{
	renderer = r;
}
