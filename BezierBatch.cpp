//
//  BezierBatch.cpp
//  Project1
//
//  Created by Charbel Douaihy on 11/14/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#include "BezierBatch.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

BezierBatch::BezierBatch(BezierCurve * c0, BezierCurve * c1, BezierCurve * c2, BezierCurve * c3){
    
    curves.push_back(c0);
    curves.push_back(c1);
    curves.push_back(c2);
    curves.push_back(c3);
	BezierCurve* d0 = new BezierCurve(c0->points[0], c1->points[0], c2->points[0], c3->points[0]);
	BezierCurve* d1 = new BezierCurve(c0->points[1], c1->points[1], c2->points[1], c3->points[1]);
	BezierCurve* d2 = new BezierCurve(c0->points[2], c1->points[2], c2->points[2], c3->points[2]);
	BezierCurve* d3 = new BezierCurve(c0->points[3], c1->points[3], c2->points[3], c3->points[3]);
	otherAxis.push_back(d0);
	otherAxis.push_back(d1);
	otherAxis.push_back(d2);
	otherAxis.push_back(d3);
    for(float u = 0; u <= 300; u++){
        getPoint(u/300.0);
    }
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).

	// GENERATE INDICES
	int count = 0;
	for (int x = 0; x < 300; x++) {
		int index1 = (x * 301) + 1; //based on height
		for (int y = 0; y < 300; y++) {
			int index2 = index1 + y;
			indices.push_back(index2);
			indices.push_back(index2 + 301);
			indices.push_back(index2 + 1);
			indices.push_back(index2 + 301 + 1);
			if (y == 299 && x < 299) {
				indices.push_back(index2 + 1);
				indices.push_back(index2 + 2);
			}
		}
	}
	
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
	glGenBuffers(1, &vboNormal);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * x.size(), x.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);


    // Unbind from the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void BezierBatch::getPoint(float t){
    glm::vec3 q0 = curves[0]->getPoint(t);
    glm::vec3 q1 = curves[1]->getPoint(t);
    glm::vec3 q2 = curves[2]->getPoint(t);
    glm::vec3 q3 = curves[3]->getPoint(t);
	glm::vec3 r0 = otherAxis[0]->getPoint(t);
	glm::vec3 r1 = otherAxis[1]->getPoint(t);
	glm::vec3 r2 = otherAxis[2]->getPoint(t);
	glm::vec3 r3 = otherAxis[3]->getPoint(t);
	BezierCurve* c = new BezierCurve(q0, q1, q2, q3);
	BezierCurve* d = new BezierCurve(r0, r1, r2, r3);
    for(float v = 0.0; v <= 300.0; v++){
       
        x.push_back(c->getPoint(v/300.0));
		glm::vec3 yTangent = c->getTangent(v / 300.0);
		glm::vec3 xTangent = d->getTangent(v / 300.0);
		normals.push_back(glm::cross(xTangent,yTangent));
    }
}

void BezierBatch::draw(){
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // element array buffer.
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}


