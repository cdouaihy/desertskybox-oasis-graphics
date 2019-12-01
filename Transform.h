//
//  Transform.h
//  Project1
//
//  Created by Charbel Douaihy on 10/29/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Node.h"

class Transform : public Node{
private:
    glm::mat4 T; //transform matrix to place object relative to parent
    std::vector<Node *> children; //list of children
    int counter;
    bool isCC;
public:
    Transform(glm::mat4 M);
    ~Transform();
    void draw(GLuint shaderProgram, glm::mat4 C);
    void update(glm::mat4 C);
    glm::vec3 getLocation();
    void addChild(Node * child);
};

#endif /* Transform_h */
