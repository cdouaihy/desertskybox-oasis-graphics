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
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * x.size(), x.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
    std::vector<glm::vec3> row;
    for(float v = 0.0; v <= 300.0; v++){
        BezierCurve * c = new BezierCurve(q0,q1,q2,q3);
        x.push_back(c->getPoint(v/300.0));
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


