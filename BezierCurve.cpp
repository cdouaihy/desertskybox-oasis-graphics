//
//  BezierCurve.cpp
//  Project1
//
//  Created by Charbel Douaihy on 11/14/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#include "BezierCurve.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

BezierCurve::BezierCurve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
    
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    
    for(float i = 0; i <= 500; i++){
        x.push_back(getPoint(i/500.0));
    }
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * x.size(), x.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind from the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

glm::vec3 BezierCurve::getPoint(float t){
    glm::vec3 a = -points[0] + 3.0f*points[1] - 3.0f*points[2] + points[3];
    glm::vec3 b = 3.0f*points[0] - 6.0f*points[1] + 3.0f*points[2];
    glm::vec3 c = -3.0f*points[0] + 3.0f*points[1];
    glm::vec3 d = points[0];
    glm::vec3 output = a*(t*t*t) + b*(t*t) + c*(t) + d;
    return output;
}

glm::vec3 BezierCurve::getTangent(float t) {
	glm::vec3 a = -points[0] + 3.0f * points[1] - 3.0f * points[2] + points[3];
	glm::vec3 b = 3.0f * points[0] - 6.0f * points[1] + 3.0f * points[2];
	glm::vec3 c = -3.0f * points[0] + 3.0f * points[1];
	glm::vec3 d = points[0];
	glm::vec3 output = (a * (3.0f) * (t * t)) + (b * 2.0f * t) + c;
	return output;
}

double BezierCurve::getT(glm::vec3 pos){
    for(int i = 0; i <=500; i++){
        if(x[i] == pos){
            return i/500.0;
        }
    }
    return -1;
}
void BezierCurve::draw(){
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // element array buffer.
    glDrawArrays(GL_LINE_STRIP, 0, 501);
    // Unbind from the VAO.
    glBindVertexArray(0);
}


