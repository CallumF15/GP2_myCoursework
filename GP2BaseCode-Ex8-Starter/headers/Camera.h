//
//  Camera.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <SDL.h>
#include <gl\glew.h>

#include <gl\glew.h>
#include <glm\gtc\quaternion.hpp>
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

enum MovementType { FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT, RESET };

class Camera:public Component
{
public:
    Camera();
    ~Camera();
    
	void update();
    
	void setLook(float x, float y, float z);
    
	void setUp(float x, float y, float z);
    
    void setNearClip(float near);
    void setFarClip(float far);
	void setFOV(float FOV);
    
	void setAspectRatio(float ratio);
    
	mat4& getView();
	mat4& getProjection();

	void translate(glm::vec3& direction);
	void applyMovement(MovementType movement);
	void setMousePosition(int X, int Y);

	void calculateMovement();
	void setTime(float deltatime);

	void lockCamera();
	void moveCamera(float distance, float direction);
	void moveCameraUp(float distance, float direction);
	void control(SDL_Window* window, float moveVelocity, float mouseVelocity, bool mi);
	void movement(MovementType movementType, float mouseVelocity, float moveVelocity);
	void updateCamera();

	MovementType setMovementType(MovementType type);

protected:
private:
	// Creates an identity quaternion (no rotation)
	glm::quat MyQuaternion;

	// Conversion from Euler angles (in radians) to Quaternion
	vec3 EulerAngles;



	//my variables
	MovementType  m_movementType;
	int m_MouseX, m_MouseY;
	float mouseSpeed = 0.005f; 
	float speed = 3.0f;

	float m_deltatime;

	vec3 direction;
	vec3 right;

	// position
	//vec3 position = vec3(0, 0, 5);

	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;


	//yaw/pitch...
	
	vec3 lookvec, camPos;
	vec3 m_Rotation;
	float camPitch = 0.0f;
	float camYaw = 0.0f;
	float camX = 0.0f, camY = 0.0f, camZ = 0.0f;
	bool mouseIn = false;

	//end myVariables



	glm::vec3 m_position;
	glm::vec3 m_direction;

	vec3 m_LookAt;
	vec3 m_Up;
    
	mat4 m_View;
	mat4 m_Projection;
    
	float m_NearClip;
	float m_FarClip;
	float m_FOV;
	float m_AspectRatio;
};

#endif
