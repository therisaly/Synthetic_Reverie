#include <LinearMath/btIDebugDraw.h>
#include <GL/glew.h> // For OpenGL functions 

class BulletDebugDrawer : public btIDebugDraw {
public:
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override {
        glBegin(GL_LINES);
        glColor3f(color.x(), color.y(), color.z());
        glVertex3f(from.x(), from.y(), from.z());
        glVertex3f(to.x(), to.y(), to.z());
        glEnd();
    }

    void setDebugMode(int mode) override { debugMode = mode; }
    int getDebugMode() const override { return debugMode; }

    // Optional overrides (stubs for unused methods)
    void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override {}
    void reportErrorWarning(const char*) override {}
    void draw3dText(const btVector3&, const char*) override {}

private:
    int debugMode = DBG_DrawWireframe; // Default mode
};