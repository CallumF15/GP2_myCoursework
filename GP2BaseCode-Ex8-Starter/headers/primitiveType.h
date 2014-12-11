#ifndef primitiveType_h
#define primitiveType_h


//#include <GL/glew.h>

#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"


#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>
using glm::vec3;


#include <string>

#include "Component.h"


enum primitiveShape 
{ 
	cube, 
	triangle
};

static class primitiveType : public Component{

public:
	primitiveType();
	primitiveType(primitiveShape shapes);
	~primitiveType();

	void render(); //needed to render primitive to screen.
	void update();
	void setUpPrimitive(std::string name, vec3 pos, GameObject* objectShape, Transform* transform, Material* material, Mesh* mesh);

	std::vector<GameObject*> displayList;

private:
	 void CheckShape(primitiveShape shape);

	 primitiveShape shape;

};



#endif