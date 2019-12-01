#include "PointCloud.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

PointCloud::PointCloud(std::string objFilename, GLfloat pointSize) 
	: pointSize(pointSize)
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
                    points.push_back(point);
                }
                else if (label == "vn"){
                    glm::vec3 normal;
                    
                    ss >> normal.x >> normal.y >> normal.z;

                    
                    normals.push_back(normal);
                }
                else if (label == "f"){
                    glm::ivec3 face;
                    std::string num;
                    std::string num2;
                    std::string num3;
                    
                    ss >> num;
                    int pos = num.find('/');
                    num = (num.substr(0,pos));
                    
                    ss >> num2;
                    int pos2 = num2.find('/');
                    num2 = num2.substr(0,pos2);
                    
                    ss >> num3;
                    int pos3 = num3.find('/');
                    num3 = num3.substr(0,pos3);
                    
                    face.x = std::stoi(num) - 1;
                    face.y = std::stoi(num2) - 1;
                    face.z = std::stoi(num3) - 1;
                    indices.push_back(face);
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
	color = glm::vec3(1, 0, 0);

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

PointCloud::~PointCloud() 
{
	// Delete the VBO and the VAO.
	glDeleteBuffers(2, vbos);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void PointCloud::draw()
{
	// Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // elemnt array buffer.
    glDrawElements(GL_TRIANGLES, 3*(indices.size()), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void PointCloud::update()
{
	// Spin the cube by 1 degree.
	//spin(0.1f);
    
}

void PointCloud::updatePointSize(GLfloat size) 
{
	/*
	 * Section 3: Implement this function to adjust the point size.
	 */
    pointSize = size;
    draw();
}

void PointCloud::scaleModelUp()
{
    model = glm::scale(glm::vec3(1.25f, 1.25f, 1.25f)) * model;
}

void PointCloud::scaleModelDown()
{
    model = glm::scale(glm::vec3(0.75f, 0.75f, 0.75f)) * model;
}

void PointCloud::scaleSphere()
{
    model = glm::translate(glm::mat4(1), glm::vec3(5.0f, 5.0f, 5.0f));
    model = glm::scale(model,glm::vec3(0.08f, 0.08f, 0.08f));
    model = glm::translate(model, glm::vec3(5.0f, 5.0f, 5.0f));
}

glm::vec3 PointCloud::rotateSphere(glm::vec3 pivot, glm::vec3 lightPos, glm::vec3 axis)
{
    glm::mat4 transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(-pivot.x, -pivot.y, -pivot.z));
    transform = glm::rotate(transform, 0.1f, axis);
    transform = glm::translate(transform, glm::vec3(pivot.x, pivot.y, pivot.z));
    model = transform * model;
    glm::vec4 newPos = glm::vec4(lightPos, 1);
    glm::vec4 finalPos = model * newPos;
    return finalPos;
}

void PointCloud::translateSphereTo(glm::vec3 pivot)
{
    glm::mat4 transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(pivot.x, pivot.y, pivot.z));
    model = transform * model;
}

void PointCloud::translateSphereFrom(glm::vec3 pivot)
{
    glm::mat4 transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(-pivot.x, -pivot.y, -pivot.z));
    model = transform * model;
}
void PointCloud::rotate(float angle, glm::vec3 axis){
    model = glm::rotate(angle,axis) * model;
}
glm::vec3 PointCloud::getCenter(){
    return center;
}
void PointCloud::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	model = glm::rotate(model, glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

