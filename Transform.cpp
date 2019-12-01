//
//  Transform.cpp
//  Project1
//
//  Created by Charbel Douaihy on 10/29/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#include <stdio.h>
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Transform::Transform(glm::mat4 M){
    T = M;
    counter = 0;
    isCC = true;
}
Transform::~Transform(){
    delete this;
}
void Transform::addChild(Node * child){
    children.push_back(child);
}

void Transform::draw(GLuint shaderProgram, glm::mat4 C){
    for (int i = 0; i < children.size(); i++){
        children[i]->draw(shaderProgram, C * T);
    }
}

glm::vec3 Transform::getLocation(){
    return glm::vec3(T[3][0],T[3][1],T[3][2]);
}
void Transform::update(glm::mat4 C){
    T = C * T;
}
