//
//  Node.h
//  Project1
//
//  Created by Charbel Douaihy on 10/29/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef Node_h
#define Node_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Node{
public:
    virtual void draw(GLuint shaderProgram, glm::mat4 C) = 0;
    virtual void update(glm::mat4 C) = 0;
};
#endif /* Node_h */
