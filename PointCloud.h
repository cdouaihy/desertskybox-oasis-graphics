#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Object.h"

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> indices;
    glm::vec3 center;
	GLuint vao;
    GLuint vbos[2];
    GLuint ebo;
	GLfloat pointSize;
public:
	PointCloud(std::string objFilename, GLfloat pointSize);
	~PointCloud();

	void draw();
	void update();

	void updatePointSize(GLfloat size);
    void scaleModelUp();
    void scaleModelDown();
    void scaleSphere();
    glm::vec3 rotateSphere(glm::vec3 pivot, glm::vec3 lightPos, glm::vec3 axis);
    void translateSphereTo(glm::vec3 pivot);
    void translateSphereFrom(glm::vec3 pivot);
    void rotate(float angle, glm::vec3 axis);
	void spin(float deg);
    glm::vec3 getCenter();
};

#endif

