//
//  BezierBatch.hpp
//  Project1
//
//  Created by Charbel Douaihy on 11/14/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef BezierBatch_hpp
#define BezierBatch_hpp

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
#include "BezierCurve.h"

class BezierBatch : public Geometry{
private:
    std::vector<BezierCurve *> curves;
    std::vector<std::vector<glm::vec3>> x;
    GLuint vao;
    GLuint vbo;
public:
    BezierBatch(BezierCurve * c0, BezierCurve * c1, BezierCurve * c2, BezierCurve * c3);
    void getPoint(float t);
    void draw();
};



#endif /* BezierBatch_h */
