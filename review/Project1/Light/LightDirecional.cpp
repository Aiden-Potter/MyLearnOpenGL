#include "LightDirecional.h"



LightDirecional::LightDirecional(glm::vec3 _position,
	glm::vec3 _angles,
	glm::vec3 _color):
	position(_position),
	color(_color),
	angles(_angles)

{
	UpdateDireciton();
}

LightDirecional::~LightDirecional()
{
}
