#include "primitiveType.h"


const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";

Vertex triangleData[] =
{
		{ vec3(-0.5f, 0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 0.0f) },// Top Left
		{ vec3(-0.5f, -0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 1.0f) },// Bottom Left
		{ vec3(0.5f, -0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 0.0f) },// Top Right


		//back
		{ vec3(-0.5f, 0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 0.0f) },// Top Left
		{ vec3(-0.5f, -0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 1.0f) },// Bottom Left
		{ vec3(0.5f, -0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 0.0f), }// Top Right
};

GLuint triangleIndices[];
GLuint indices[];

GLuint cubeIndices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};

primitiveType::primitiveType()
{

}

primitiveType::primitiveType(primitiveShape shapes)
{
	shape = shapes;
}

primitiveType::~primitiveType(){

}


void primitiveType::render()
{


}
void primitiveType::update(){

}


//I think its moaning at this
void primitiveType::CheckShape(primitiveShape shape)
{
	 if (shape == cube){
		 indices == cubeIndices;
	 }	 
	else
		if (shape == triangle)
		{
		 indices == triangleIndices;
		}
}

//Allow's you to create a shape at a given position
 void primitiveType::setUpPrimitive(std::string name, vec3 pos, GameObject* objectShape, Transform* transform, Material* material, Mesh* mesh) 
 {

	 //this method should setup any primitive we want

	 CheckShape(shape);

	 float x, y, z;
	 x = pos.x;
	 y = pos.y;
	 z = pos.z;

	// objectShape = new GameObject();
	// transform = new Transform();
	// material = new Material();
	// mesh = new Mesh();

	 objectShape->setName(name);
	 transform->setPosition(x, y, z);
	 objectShape->setTransform(transform);

	 std::string vsPath = ASSET_PATH + SHADER_PATH + "/specularVS.glsl";
	 std::string fsPath = ASSET_PATH + SHADER_PATH + "/specularFS.glsl";
	 material->loadShader(vsPath, fsPath);
	 objectShape->setMesh(mesh);
	 objectShape->setMaterial(material);
	 displayList.push_back(objectShape);
	 

	 for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	 {
		 (*iter)->init();
	 }

	 mesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	 mesh->copyIndexData(36, sizeof(int), (void**)indices);
 }


