#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <map>

#include <btBulletDynamicsCommon.h>
#include "tiny_obj_loader.h"

//Using btTransform for Transform Component

struct Mesh
{
    struct Texture {
        GLuint id;              // OpenGL texture ID
        std::string type;       // Type of texture ("diffuse", "specular", etc.)
        std::string path;       // Path to the texture file
    };

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes; 
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    btVector3 dimensions;
};

//Using Rigidbody component for 
