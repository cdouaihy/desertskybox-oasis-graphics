//
//  BezierCurve.hpp
//  Project1
//
//  Created by Charbel Douaihy on 11/14/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef BezierCurve_hpp
#define BezierCurve_hpp

#include <stdio.h>
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
#include "Geometry.h"

class BezierCurve : public Geometry{
private:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> x;
    GLuint vao;
    GLuint vbo;
public:
    BezierCurve(glm::vec3 p0,glm::vec3 p1,glm::vec3 p2,glm::vec3 p3);
    glm::vec3 getPoint(float t);
    double getT(glm::vec3 pos);
    void draw();
};



#endif /* BezierCurve_h */
