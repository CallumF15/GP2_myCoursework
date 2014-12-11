//
//  Material.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include <GL/glew.h>

#include <glm/glm.hpp>
using glm::vec4;

#include <string>

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#include "Component.h"

class Material:public Component{
public:
    Material();
    ~Material();
    
    void destroy();
    
    void bind();
    
    bool loadShader(const std::string& vsFilename,const std::string& fsFilename);
    GLint getUniformLocation(const std::string& name);
	
	vec4& getAmbientColour();
	void setAmbientColour(float r, float g, float b, float a);

	vec4& getDiffuseColour();
	void setDiffuseColour(float r, float g, float b, float a);

	vec4& getSpecularColour();
	void setSpecularColour(float r, float g, float b, float a);

	float getSpecularPower();
	void setSpecularPower(float power);

	void loadDiffuseMap(const std::string& filename);
	GLuint getDiffuseMap();


protected:
private:
    GLuint m_ShaderProgram;
	GLuint m_DiffuseMap;
	vec4 m_AmbientColour;
	vec4 m_DiffuseColour;
	vec4 m_SpecularColour;
	float m_SpecularPower;
};

#endif
