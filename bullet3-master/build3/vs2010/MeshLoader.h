#pragma once
#pragma warning(disable : 4996)
#include "stb_image.h"
#include "Components.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <tuple>

#include <functional>

// Custom hash function for std::tuple
struct TupleHash {
    template <typename T>
    std::size_t operator()(const T& tuple) const {
        std::size_t hash = 0;
        std::apply([&hash](auto&&... args) {
            ((hash ^= std::hash<std::decay_t<decltype(args)>>{}(args)+0x9e3779b9 + (hash << 6) + (hash >> 2)), ...);
            }, tuple);
        return hash;
    }
};

class MeshLoader {
public:
    // Function to load the model from an OBJ file
    static bool LoadModel(const char* path, Mesh& mesh) {
        if (!tinyobj::LoadObj(&mesh.attrib, &mesh.shapes, &mesh.materials, &mesh.warn, &mesh.err, path)) {
            std::cerr << "TinyObjLoader error: " << mesh.warn << mesh.err << std::endl;
            return false;
        }

        mesh.vertices.clear();
        mesh.normals.clear();
        mesh.texCoords.clear();
        mesh.indices.clear();
        mesh.textures.clear(); // Clear any previously loaded textures

        std::unordered_map<std::tuple<int, int, int>, unsigned int, TupleHash> uniqueVertices;
        unsigned int nextIndex = 0;

        for (const auto& shape : mesh.shapes) {
            for (const auto& index : shape.mesh.indices) {
                // Create a unique key for the triplet (vertex, normal, texcoord)
                std::tuple<int, int, int> key = {
                    index.vertex_index,
                    index.normal_index,
                    index.texcoord_index
                };

                // Check if this triplet is already added
                if (uniqueVertices.find(key) == uniqueVertices.end()) {
                    // Add new vertex
                    uniqueVertices[key] = nextIndex++;

                    // Add vertex position
                    mesh.vertices.push_back(mesh.attrib.vertices[3 * index.vertex_index + 0]);
                    mesh.vertices.push_back(mesh.attrib.vertices[3 * index.vertex_index + 1]);
                    mesh.vertices.push_back(mesh.attrib.vertices[3 * index.vertex_index + 2]);

                    // Add normal
                    if (!mesh.attrib.normals.empty()) {
                        mesh.normals.push_back(mesh.attrib.normals[3 * index.normal_index + 0]);
                        mesh.normals.push_back(mesh.attrib.normals[3 * index.normal_index + 1]);
                        mesh.normals.push_back(mesh.attrib.normals[3 * index.normal_index + 2]);
                    }

                    // Add texture coordinates
                    if (!mesh.attrib.texcoords.empty()) {
                        mesh.texCoords.push_back(mesh.attrib.texcoords[2 * index.texcoord_index + 0]);
                        mesh.texCoords.push_back(mesh.attrib.texcoords[2 * index.texcoord_index + 1]);
                    }
                }

                // Add the index for the triplet
                mesh.indices.push_back(uniqueVertices[key]);
            }
        }

        // Load textures from materials
        std::unordered_map<std::string, GLuint> loadedTextures; // Prevent duplicate texture loading
        for (const auto& material : mesh.materials) {
            if (!material.diffuse_texname.empty()) {
                const std::string& texturePath = material.diffuse_texname;

                if (loadedTextures.find(texturePath) == loadedTextures.end()) {
                    GLuint textureID = LoadTexture(texturePath.c_str());
                    if (textureID != 0) {
                        loadedTextures[texturePath] = textureID;
                        mesh.textures.push_back({ textureID, "diffuse", texturePath });
                    }
                }
            }
            // Handle other texture types (e.g., specular, normal) similarly
        }

        // Compute bounding box (unchanged)
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float minZ = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float maxY = std::numeric_limits<float>::lowest();
        float maxZ = std::numeric_limits<float>::lowest();

        for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
            float x = mesh.vertices[i];
            float y = mesh.vertices[i + 1];
            float z = mesh.vertices[i + 2];

            minX = std::min(minX, x);
            minY = std::min(minY, y);
            minZ = std::min(minZ, z);

            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
            maxZ = std::max(maxZ, z);
        }

        mesh.dimensions = btVector3(maxX - minX, maxY - minY, maxZ - minZ);


        return true;
    }

private:
    static GLuint LoadTexture(const char* texturePath) {
        int width, height, channels;
        unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);
        if (!data) {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
            return 0;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        if (channels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(data);
        return textureID;
    }
};