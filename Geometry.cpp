//
//  Geometry.cpp
//  Project1
//
//  Created by Charbel Douaihy on 10/29/19.
//  Copyright © 2019 Charbel Douaihy. All rights reserved.
//

#include <stdio.h>
#include "Geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Geometry::Geometry(){
    
}
Geometry::Geometry(std::string objFilename)
{
    /*
     * Section 2: Currently, all the points are hard coded below.
     * Modify this to read points from an obj file.
     */
    double max_x = -1000;
    double min_x = 1000;
    double max_y = -1000;
    double min_y = 1000;
    double max_z = -1000;
    double min_z = 1000;
    
    if(objFilename != "foo"){
        std::ifstream objFile(objFilename); // The obj file we are reading.
        
        // Check whether the file can be opened.
        if (objFile.is_open())
        {
            
            std::string line; // A line in the file.

            // Read lines from the file.
            while (std::getline(objFile, line))
            {
                // Turn the line into a string stream for processing.
                std::stringstream ss;
                ss << line;
                
                // Read the first word of the line.
                std::string label;
                ss >> label;

                // If the line is about vertex (starting with a "v").
                if (label == "v")
                {
                    // Read the later three float numbers and use them as the
                    // coordinates.
                    glm::vec3 point;
                    
                    ss >> point.x >> point.y >> point.z;

                    //std::cout << point.x << std::endl;
                    if(point.x > max_x){
                        max_x = point.x;
                    }
                    if(point.x < min_x){
                        min_x = point.x;
                    }
                    if(point.y > max_y){
                        max_y = point.y;
                    }
                    if(point.y < min_y){
                        min_y = point.y;
                    }
                    if(point.z > max_z){
                        max_z = point.z;
                    }
                    if(point.z < min_z){
                        min_z = point.z;
                    }
                    // Process the point. For example, you can save it to a.
                    input_points.push_back(point);
                }
                else if (label == "vn"){
                    glm::vec3 normal;
                    
                    ss >> normal.x >> normal.y >> normal.z;

                    
                    input_normals.push_back(normal);
                }
                else if (label == "f"){
                    glm::ivec3 vert_ind;
                    glm::ivec3 norm_ind;
                    std::string num;
                    std::string num2;
                    std::string num3;
                    
                    ss >> num;
                    int pos = num.find('/');
                    num = (num.substr(0,pos));
                    vert_ind[0] = stoi(num);
                    pos = num.find('/');
                    num = (num.substr(0,pos));
                    pos = num.find('/');
                    num = (num.substr(0,pos));
                    norm_ind[0] = stoi(num);
                    
                    ss >> num2;
                    int pos2 = num2.find('/');
                    num2 = num2.substr(0,pos2);
                    vert_ind[1] = stoi(num2);
                    pos2 = num2.find('/');
                    num2 = num2.substr(0,pos2);
                    pos2 = num2.find('/');
                    num2 = num2.substr(0,pos2);
                    norm_ind[1] = stoi(num2);
                    
                    ss >> num3;
                    int pos3 = num3.find('/');
                    num3 = num3.substr(0,pos3);
                    vert_ind[2] = stoi(num3);
                    pos3 = num3.find('/');
                    num3 = num3.substr(0,pos3);
                    pos3 = num3.find('/');
                    num3 = num3.substr(0,pos3);
                    norm_ind[2] = stoi(num3);
                    
                    vertex_indices.push_back(vert_ind[0] - 1);
                    vertex_indices.push_back(vert_ind[1] - 1);
                    vertex_indices.push_back(vert_ind[2] - 1);
                    normal_indices.push_back(norm_ind[0] - 1);
                    normal_indices.push_back(norm_ind[1] - 1);
                    normal_indices.push_back(norm_ind[2] - 1);

                }
            }
        }
        else
        {
            std::cerr << "Can't open the file " << objFilename << std::endl;
        }

        objFile.close();
    }
    else {
        points =
        {
            glm::vec3(-2.5, 2.5, 2.5),
            glm::vec3(-2.5, -2.5, 2.5),
            glm::vec3(2.5, -2.5, 2.5),
            glm::vec3(2.5, 2.5, 2.5),
            glm::vec3(-2.5, 2.5, -2.5),
            glm::vec3(-2.5, -2.5, -2.5),
            glm::vec3(2.5, -2.5, -2.5),
            glm::vec3(2.5, 2.5, -2.5)
        };
    }
    /*points = input_points;
    normals = input_normals;
    indices = vertex_indices;*/
    
    for (unsigned int i = 0; i < vertex_indices.size(); i++) {
      points.push_back(input_points[vertex_indices[i]]);
      normals.push_back(input_normals[normal_indices[i]]);
      indices.push_back(i);
    }
    /*
     * TODO: Section 4, you will need to normalize the object to fit in the
     * screen.
     */
    double center_x = (max_x + min_x)/ 2;
    double center_y = (max_y + min_y)/ 2;
    double center_z = (max_z + min_z)/ 2;
    double max_dist = 0; //maximum distance from a point to the center
    center = glm::vec3(center_x, center_y, center_z);
    for (int i = 0; i < points.size(); i++){
        points[i] = points[i] - center;
        
        double v_x = points[i].x - center.x;
        double v_y = points[i].y - center.y;
        double v_z = points[i].z - center.z;
        double dist = sqrt(v_x*v_x + v_y*v_y + v_z*v_z);
        if(dist > max_dist){
            max_dist = dist;
        }
    }
    
    
    double scale_factor = (12)/max_dist;
    
    for (int i = 0; i < points.size(); i++){
        points[i] *= scale_factor;
    }
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    // Set the color.
    //color = glm::vec3(1, 0, 0);

    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);

    // Bind to the VAO.
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
        points.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access vertices through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Bind to the second VBO. We will use it to store the indices.
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::ivec3) * normals.size(),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);


    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Pass in the data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(),
        indices.data(), GL_STATIC_DRAW);

    // Unbind from the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

Geometry::~Geometry()
{
    // Delete the VBO and the VAO.
    glDeleteBuffers(2, vbos);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Geometry::draw(GLuint shaderProgram, glm::mat4 C){
    model = C;
    
    auto modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // elemnt array buffer.
    glDrawElements(GL_TRIANGLES, 3*(indices.size()), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void Geometry::update(glm::mat4 C){
    //model = C * model;
}

glm::mat4 Geometry::getModel(){
    return model;
}
