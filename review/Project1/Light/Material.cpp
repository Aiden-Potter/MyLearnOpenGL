#include "Material.h"



Material::Material(Shader * _shader,
	glm::vec3 _ambient,
	unsigned int _diffuse,
	unsigned int _specular,
	unsigned int _emission,
	float _shiness):
	shader(_shader),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular),
	emission(_emission),
	shiness(_shiness)
{
	

}

Material::~Material()
{
}
