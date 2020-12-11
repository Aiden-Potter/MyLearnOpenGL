#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightDirecional
{

public:
	LightDirecional(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color= glm::vec3(1.0f,1.0f,1.0f));
	~LightDirecional();

	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0,0,1.0f);
	glm::vec3 color;

	void UpdateDireciton()
	{
		direction = glm::vec3(0, 0, 1.0f);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
		direction *= -1;
	}
};

