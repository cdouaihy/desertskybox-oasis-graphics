//
//  Skybox.cpp
//  Project1
//
//  Created by Charbel Douaihy on 11/10/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "Skybox.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Skybox::Skybox(){
    // The 8 vertices of a cube.
    float skyboxVertices[] = {
        // positions
        -200.0f,  200.0f, -200.0f,
        -200.0f, -200.0f, -200.0f,
         200.0f, -200.0f, -200.0f,
         200.0f, -200.0f, -200.0f,
         200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,

        -200.0f, -200.0f,  200.0f,
        -200.0f, -200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f,  200.0f,
        -200.0f, -200.0f,  200.0f,

         200.0f, -200.0f, -200.0f,
         200.0f, -200.0f,  200.0f,
         200.0f,  200.0f,  200.0f,
         200.0f,  200.0f,  200.0f,
         200.0f,  200.0f, -200.0f,
         200.0f, -200.0f, -200.0f,

        -200.0f, -200.0f,  200.0f,
        -200.0f,  200.0f,  200.0f,
         200.0f,  200.0f,  200.0f,
         200.0f,  200.0f,  200.0f,
         200.0f, -200.0f,  200.0f,
        -200.0f, -200.0f,  200.0f,

        -200.0f,  200.0f, -200.0f,
         200.0f,  200.0f, -200.0f,
         200.0f,  200.0f,  200.0f,
         200.0f,  200.0f,  200.0f,
        -200.0f,  200.0f,  200.0f,
        -200.0f,  200.0f, -200.0f,

        -200.0f, -200.0f, -200.0f,
        -200.0f, -200.0f,  200.0f,
         200.0f, -200.0f, -200.0f,
         200.0f, -200.0f, -200.0f,
        -200.0f, -200.0f,  200.0f,
         200.0f, -200.0f,  200.0f
    };
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind from the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
	std::vector<std::string> faces
	{
		   "Right.2048x2048.png",
		   "Left.2048x2048.png",
		   "Up.2048x2048.png",
		   "Down.2048x2048.png",
		   "Front.2048x2048.png",
		   "Back.2048x2048.png"
	};

	cubemap = loadCubemap(faces);
    
}
unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    
    
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Use clamp to edge to hide skybox edges:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return id;
}

void Skybox::draw()
{
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Bind to the VAO.
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
    // Draw triangles using the indices in the second VBO, which is an
    // elemnt array buffer.
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // Unbind from the VAO.
    glBindVertexArray(0);
    //glDepthMask(GL_TRUE);
}
