//
//  Skybox.hpp
//  Project1
//
//  Created by Charbel Douaihy on 11/10/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>
#include <stdio.h>

class Skybox{
private:
    unsigned int id;
    GLuint vao;
    GLuint vbo;
public:
    Skybox();
    void draw();
    unsigned int loadCubemap(std::vector<std::string> faces);
};
#endif /* Skybox_hpp */
