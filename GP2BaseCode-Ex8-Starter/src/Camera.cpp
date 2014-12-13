

///This class was implemented by Callum Flannagan ///

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"



#ifndef M_PI
#define M_PI 3.1415926525
#endif


Camera::Camera()
{
	m_position = vec3(0, 0, 10);
	m_Type = "Camera";

	m_direction = vec3(0.0, 0.0, -1.0f);
	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);

	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_View = mat4();
	m_Projection = mat4();
}

Camera::~Camera()
{

}


void Camera::update()
{
	//m_position = m_Parent->getTransform()->getPosition();
	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(m_position, m_position + m_direction, m_Up);

}

void Camera::mouseUpdate(const glm::vec2& newMousePos)
{
	glm::vec2 mouseDelta = newMousePos - oldMousePos;

	if (glm::length(mouseDelta) > 50.0f){
		oldMousePos = newMousePos;
		return;
	}
	
	const float ROTATIONAL_SPEED = 0.5f;

	    strafedirection = glm::cross(m_direction, m_Up);
	    glm::mat4 rotator = glm::rotate(mat4(1.0f), -mouseDelta.x * ROTATIONAL_SPEED, m_Up) *
		glm::rotate(mat4(1.0f), -mouseDelta.y * ROTATIONAL_SPEED, strafedirection);

	m_direction = glm::mat3(rotator) * m_direction;

	oldMousePos = newMousePos; 
}

void Camera::movement(MovementType movementType)
{
	switch (movementType){

	case  FORWARD:
		m_position += movementSpeed * m_direction;
		break;
	case BACKWARD:
		m_position += -movementSpeed * m_direction;
		break;
	case STRAFE_LEFT:
		strafeLeft();
		break;
	case STRAFE_RIGHT:
		strafeRight();
		break;
	case UP:
		m_position += movementSpeed * m_Up;
		break;
	case DOWN:
		m_position -= movementSpeed * m_Up;
		break;
	case RESET:
		m_position = vec3(0, 0, 0);
		m_direction = vec3(0.0, 0.0, -1.0f);
		break;
	}
}

void Camera::strafeLeft(){
	m_position -= movementSpeed * strafedirection;
}

void Camera::strafeRight()
{
	m_position += movementSpeed * strafedirection;
}

MovementType Camera::setMovementType(MovementType type){
	return m_movementType = type;
}

//End Methods










void Camera::setLook(float x, float y, float z)
{
	m_LookAt = vec3(x, y, z);
}

void Camera::setUp(float x, float y, float z)
{
	m_Up = vec3(x, y, z);
}


void Camera::setNearClip(float near)
{
	m_NearClip = near;
}

void Camera::setFarClip(float far)
{
	m_FarClip = far;
}

void Camera::setFOV(float FOV)
{
	m_FOV = FOV;
}

void Camera::setAspectRatio(float ratio)
{
	m_AspectRatio = ratio;
}

mat4& Camera::getView()
{
	return m_View;
}

mat4& Camera::getProjection()
{
	return m_Projection;
}