//
//  Camera.c
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"



#ifndef M_PI
#define M_PI 3.1415926525
#endif

Camera::Camera()
{
	m_Type = "Camera";

	m_Rotation = vec3(0.0f, 0.0f, 0.0f);

	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);

	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_View = mat4();
	m_Projection = mat4();


	m_direction = vec3(1.0, 0.0, 1.0f);
}

Camera::~Camera()
{

}


void Camera::update()
{
	//get the position from the transform
	//vec3 position = m_Parent->getTransform()->getPosition();
	m_position = m_Parent->getTransform()->getPosition();
	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(m_position, lookvec, m_Up);

}

void Camera::lockCamera()
{
	if (camPitch > 90)
		camPitch = 90;
	if (camPitch < -90)
		camPitch = -90;
	if (camYaw < 0.0)
		camYaw += 360;
	if (camYaw > 360)
		camYaw -= 360;
}

void Camera::moveCamera(float distance, float direction){

	float radian = (camYaw + direction)* M_PI / 180.0;
	camX -= glm::sin(radian)*distance;
	camZ -= glm::cos(radian)*distance;
}

void Camera::moveCameraUp(float distance, float direction){

	float radian = (camPitch + direction)* M_PI / 180.0;
	camY += glm::sin(radian)*distance;
}

void Camera::control(SDL_Window* window, float moveVelocity, float mouseVelocity, bool mi){
	if (mi){
		int midX = 320;
		int midY = 240;

		int tmpx, tmpy;
		tmpx = m_MouseX;
		tmpy = m_MouseY;
		camYaw += mouseVelocity * (midX - tmpx);
		camPitch += mouseVelocity * (midY - tmpy);
		lockCamera();

		SDL_WarpMouseInWindow(window, midX, midY);
		movement(m_movementType, mouseVelocity, moveVelocity);
	}
}

void Camera::movement(MovementType movementType, float mouseVelocity, float moveVelocity)
{
	switch (movementType){

	case  FORWARD:
		if (camPitch != 90 && camPitch != -90)
			moveCamera(moveVelocity, 0.0);
		moveCameraUp(moveVelocity, 0.0);
		break;
	case BACKWARD:
		if (camPitch != 90 && camPitch != -90)
			moveCamera(moveVelocity, 180.0);
		moveCameraUp(moveVelocity, 180.0);
		break;
	case STRAFE_LEFT:
		moveCamera(moveVelocity, 90.0);
		break;
	case STRAFE_RIGHT:
		moveCamera(moveVelocity, 270.0);
		break;
	case RESET:
		m_position = vec3(0.0, 0.0, -10.0f);
		break;
	}

	int lookz = m_position.x + (int)(30 * glm::cos(camYaw));
	int lookx = m_position.x + (int)(30 * glm::sin(camYaw));
	int looky = m_position.y + (int)(30 * glm::tan(camPitch));
	lookvec = vec3(lookx, looky, lookz);


	//m_Rotation.x = (-camPitch, 1.0, 0.0, 0.0);
	//m_Rotation.y = (-camYaw, 0.0, 1.0, 0.0);

	//glRotatef(-camPitch, 1.0, 0.0, 0.0);
	//glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void Camera::updateCamera(){
	//glTranslatef(-camX, -camY, -camZ);
	m_Parent->getTransform()->setRotation(-camX, -camY, -camZ);
	//camPos = vec3(-camX, -camY, -camZ);
}

MovementType Camera::setMovementType(MovementType type){
	return m_movementType = type;
}





//use later for frame rate
void Camera::setTime(float deltatime)
{
	m_deltatime = deltatime;
}

void Camera::setMousePosition(int mouseX, int mouseY)
{
	//Center the mouses position
	m_MouseX = mouseX;
	m_MouseY = mouseY;
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