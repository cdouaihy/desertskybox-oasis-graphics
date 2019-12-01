//
//  Geometry.h
//  Project1
//
//  Created by Charbel Douaihy on 10/29/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Node.h"

class Geometry : public Node{
private:
    glm::mat4 model; // model matrix
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> input_points;
    std::vector<glm::vec3> input_normals;
    std::vector<int> indices;
    std::vector<int> vertex_indices;
    std::vector<int> normal_indices;
    glm::vec3 center;
    GLuint vao;
    GLuint vbos[2];
    GLuint ebo;
public:
    Geometry();
    Geometry(std::string objFilename);
    ~Geometry();
    void draw(GLuint shaderProgram, glm::mat4 C);
    void update(glm::mat4 C);
    glm::mat4 getModel();
};


#endif /* Geometry_h */
