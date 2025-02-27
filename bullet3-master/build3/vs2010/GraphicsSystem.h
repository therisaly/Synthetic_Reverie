#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

class GraphicsSystem
{
public:
	static GraphicsSystem& GetInstance()
	{
		static GraphicsSystem gfx;
		return gfx;
	}
	static void InitLight()
	{
		glClearColor(0.68f, 0.85f, 0.9f, 1.0f);  // Set the background color

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);  // Enable light source 0
		glEnable(GL_DEPTH_TEST);  // Enable depth testing
		glEnable(GL_TEXTURE_2D);  // Enable 2D textures
		glEnable(GL_COLOR_MATERIAL);  // Enable material color tracking

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor4f(0.7f, 0.7f, 0.7f, 1.0f);  // Desaturated grayish tone

		// Light properties
		GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };  // Directional light (w=0 for directional)
		GLfloat lightAmbient[] = { 0.6f, 0.6f, 0.6f, 1.0f };  // Dim ambient light
		GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // White diffuse light
		GLfloat lightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.0f };  // White specular light

		glEnable(GL_FOG);
		GLfloat fogColor[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // Light gray fog
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_EXP);  // Linear fog gives a gradual fade
		glFogf(GL_FOG_START, 5.0f);
		glFogf(GL_FOG_END, 25.0f);
		glFogf(GL_FOG_DENSITY, 0.02f);  // Very subtle fog effect


		// Set the light source properties
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	}
	void RenderMesh(btScalar* matrix, Mesh& mesh)
	{
		GLfloat glTransform[16]; 
		for (int i = 0; i < 16; ++i) 
		{
			glTransform[i] = static_cast<GLfloat>(matrix[i]);
		}

		glPushMatrix(); 
		glMultMatrixf(glTransform); 

		for (const auto& texture : mesh.textures) { 
			if (texture.type == "diffuse") { 
				glBindTexture(GL_TEXTURE_2D, texture.id); 
				glEnable(GL_TEXTURE_2D); 
				break; // Assuming only one diffuse texture for now
			}
		}

		glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < mesh.indices.size(); ++i) {
			unsigned int vertexIndex = mesh.indices[i];

			// Apply normals if available
			if (!mesh.normals.empty()) {
				glNormal3f(
					mesh.normals[3 * vertexIndex + 0],
					mesh.normals[3 * vertexIndex + 1],
					mesh.normals[3 * vertexIndex + 2]
				);
			}

			// Apply texture coordinates if available
			if (!mesh.texCoords.empty()) {
				glTexCoord2f(
					mesh.texCoords[2 * vertexIndex + 0],
					- mesh.texCoords[2 * vertexIndex + 1]
				);
			}

			// Set the vertex position
			glVertex3f(
				mesh.vertices[3 * vertexIndex + 0],
				mesh.vertices[3 * vertexIndex + 1],
				mesh.vertices[3 * vertexIndex + 2]
			);
		}
		glEnd();

		// Disable texture after rendering
		glDisable(GL_TEXTURE_2D);

		glPopMatrix(); 
	}
private:
	GraphicsSystem()
	{
	}
	~GraphicsSystem()
	{

	}
	
};