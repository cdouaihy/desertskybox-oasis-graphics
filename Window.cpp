#include "Window.h"
#include <cmath>

using namespace irrklang;

int Window::width;
int Window::height;

const char* Window::windowTitle = "GLFW Starter Project";

// Objects to display.
Cube * Window::cube;
PointCloud * Window::cubePoints;
PointCloud * Window::bunny;
PointCloud * Window::bear;
PointCloud * Window::dragon;

Geometry * Window::robot;
Transform * Window::robotroot;
Transform * Window::head;
Transform * Window::body;
Transform * Window::larm;
Transform * Window::rarm;
Transform * Window::lleg;
Transform * Window::rleg;
Transform * Window::leye;
Transform * Window::reye;

Transform * Window::sphereT;

Transform * Window::sphereAnch;
Transform * Window::sphereT1;
Transform * Window::sphereT2;
Transform * Window::sphereT3;
Transform * Window::sphereT4;
Transform * Window::sphereT5;
Transform * Window::sphereT6;
Transform * Window::sphereT7;
Transform * Window::sphereT8;

Transform * Window::spherePull;
Transform * Window::pullT1;
Transform * Window::pullT2;
Transform * Window::pullT3;
Transform * Window::pullT4;
Transform * Window::pullT5;
Transform * Window::pullT6;
Transform * Window::pullT7;
Transform * Window::pullT8;
Transform * Window::pullT9;
Transform * Window::pullT10;
Transform * Window::pullT11;
Transform * Window::pullT12;
Transform * Window::pullT13;
Transform * Window::pullT14;
Transform * Window::pullT15;
Transform * Window::pullT16;
   
int Window::curr = 0;

float Window::waveDegree = 0;

Geometry * Window::bodyGeo;
Geometry * Window::headGeo;
Geometry * Window::limbGeo;
Geometry * Window::eyeGeo;
Geometry * Window::sphereGeo;

Skybox * Window::skybox;

BezierCurve * Window::curve1;
BezierCurve * Window::curve2;
BezierCurve * Window::curve3;
BezierCurve * Window::curve4;
BezierCurve * Window::curve5;
BezierCurve * Window::curve6;
BezierCurve * Window::curve7;
BezierCurve * Window::curve8;

BezierCurve * Window::curve9;
BezierCurve * Window::curve10;
BezierCurve * Window::curve11;
BezierCurve * Window::curve12;
BezierCurve * Window::curve13;
BezierCurve * Window::curve14;
BezierCurve * Window::curve15;
BezierCurve * Window::curve16;

BezierCurve* Window::terrain[4];


BezierBatch* Window::b1;
BezierBatch* Window::b2;
BezierBatch* Window::b3;
BezierBatch* Window::b4;
BezierBatch* Window::ground;

std::vector<BezierCurve *> Window::curves;

float Window::lastTime;
float Window::currentTime;
// The object currently displaying.
Object * Window::currentObj;
Geometry * Window::currentNode;

PointCloud * Window::sphere;
glm::vec3 Window::lightPos(5.0f,5.0f,5.0f);
glm::mat4 Window::projection; // Projection matrix.

glm::vec3 Window::eye(0, 4, 70); // Camera position.
glm::vec3 Window::center(0, 0, 0); // The point we are looking at.
glm::vec3 Window::up(0, 1, 0); // The up direction of the camera.
glm::vec3 Window::start(0,0,0);
glm::vec2 Window::point(0,0);
glm::vec3 Window::direction = glm::normalize(center - eye);

float Window::deltaTime = 0.0f;
float Window::lastFrame = 0.0f;

float Window::lastX = width/2;
float Window::lastY = height/2;

float Window::yaw = -90.0f;
float Window::pitch = 0.0f;

bool Window::isRotate = false;
bool Window::modeOne = true;
bool Window::modeTwo = false;
bool Window::modeThree = false;
bool Window::isScaled = false;
bool Window::isWaterSound = true;
bool Window::firstMouse = true;
int Window::isNorm = false;
bool Window::isWave = true;

int Window:: delay = 0;

float Window::fov = 60;

ISoundSource * Window::waterSound;
std::vector<glm::vec3> Window::anchorPoints;

std::vector<glm::vec3> Window::pullPoints;

ISoundEngine * Window::SoundEngine = createIrrKlangDevice();

// View matrix, defined by eye, center and up.
glm::mat4 Window::view = glm::lookAt(Window::eye, Window::eye + Window::direction, Window::up);

GLuint Window::starterProgram;
GLuint Window::program; // The shader program id.
GLuint Window::skyboxProgram;
GLuint Window::anchProgram;
GLuint Window::pullProgram;

GLuint Window::projectionLoc; // Location of projection in shader.
GLuint Window::viewLoc;
GLuint Window::projectionSkyLoc; // Location of projection in shader.
GLuint Window::viewSkyLoc;// Location of view in shader.
GLuint Window::modelLoc;
GLuint Window::projectionAnchLoc; // Location of projection in shader.
GLuint Window::viewAnchLoc;// Location of view in shader.
GLuint Window::modelAnchLoc;
GLuint Window::projectionPullLoc; // Location of projection in shader.
GLuint Window::viewPullLoc;// Location of view in shader.
GLuint Window::modelPullLoc;
GLuint Window::modelSkyLoc;
GLuint Window::viewCurveLoc;// Location of view in shader.
GLuint Window::modelCurveLoc;
GLuint Window::projectionCurveLoc;// Location of model in shader.
GLuint Window::colorLoc; // Location of color in shader.
GLuint Window::lightPosLoc; // Location of light position in shader.
GLuint Window::lightColorLoc; // Location of light color in shader.
GLuint Window::viewPosLoc;
GLuint Window::ambientLoc;
GLuint Window::diffuseLoc;
GLuint Window::specularLoc;
GLuint Window::shinyLoc;
GLuint Window::condLoc;


bool Window::initializeProgram() {
    // Create a shader program with a vertex shader and a fragment shader.
    anchProgram = LoadShaders("shaders/anchshader.vert", "shaders/anchshader.frag");
    pullProgram = LoadShaders("shaders/pullshader.vert", "shaders/pullshader.frag");
    starterProgram = LoadShaders("shaders/startershader.vert", "shaders/startershader.frag");
    program = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    skyboxProgram = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");

    // Check the shader program.
    if (!program)
    {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }

    // Activate the shader program.
    glUseProgram(program);

    // Get the locations of uniform variables.
	projectionLoc = glGetUniformLocation(program, "projection");
	viewLoc = glGetUniformLocation(program, "view");
	modelLoc = glGetUniformLocation(program, "model");
	lightColorLoc = glGetUniformLocation(starterProgram, "lightAttr1");
	lightPosLoc = glGetUniformLocation(starterProgram, "lightAttr2");
	viewPosLoc = glGetUniformLocation(starterProgram, "viewPos");
	ambientLoc = glGetUniformLocation(starterProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(starterProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(starterProgram, "material.specular");
	shinyLoc = glGetUniformLocation(starterProgram, "material.shininess");
	condLoc = glGetUniformLocation(program, "isNormalCol");
    
    glUseProgram(starterProgram);
    projectionCurveLoc = glGetUniformLocation(starterProgram, "projection");
    viewCurveLoc = glGetUniformLocation(starterProgram, "view");
    modelCurveLoc = glGetUniformLocation(starterProgram, "model");
    colorLoc = glGetUniformLocation(starterProgram, "color");
    
    glUseProgram(anchProgram);
    projectionAnchLoc = glGetUniformLocation(anchProgram, "projection");
    viewAnchLoc = glGetUniformLocation(anchProgram, "view");
    modelAnchLoc = glGetUniformLocation(anchProgram, "model");
    
    glUseProgram(pullProgram);
    projectionPullLoc = glGetUniformLocation(pullProgram, "projection");
    viewPullLoc = glGetUniformLocation(pullProgram, "view");
    modelPullLoc = glGetUniformLocation(pullProgram, "model");
    
    glUseProgram(skyboxProgram);
    projectionSkyLoc = glGetUniformLocation(skyboxProgram, "projection");
    viewSkyLoc = glGetUniformLocation(skyboxProgram, "view");
    modelSkyLoc = glGetUniformLocation(skyboxProgram, "model");
    
    
    skybox = new Skybox();
    skybox->draw();

    return true;
}

bool Window::initializeObjects()
{
    
    glm::mat4 model = glm::scale(glm::mat4(1),glm::vec3(0.08f, 0.08f, 0.08f));
    sphereT = new Transform(model);
    sphereGeo = new Geometry("sphere.obj");
    sphereT->addChild(sphereGeo);
	bear = new PointCloud("bear.obj",10.0f);

    anchorPoints.push_back(glm::vec3(0,0,0));
    anchorPoints.push_back(glm::vec3(15,0,0));
    anchorPoints.push_back(glm::vec3(10,0,10));
    anchorPoints.push_back(glm::vec3(-10,0,20));
    anchorPoints.push_back(glm::vec3(-30,0,15));
    anchorPoints.push_back(glm::vec3(-25,0,5));
    anchorPoints.push_back(glm::vec3(-10,0,0));
    anchorPoints.push_back(glm::vec3(0,0,10));
    
    pullPoints.push_back(glm::vec3(12,0,0));
    pullPoints.push_back(glm::vec3(30,0,-16));
    pullPoints.push_back(glm::vec3(10,0,-5));
    pullPoints.push_back(glm::vec3(25,0,-18));
    pullPoints.push_back(glm::vec3(8,0,-10));
    pullPoints.push_back(glm::vec3(20,0,-20));
    pullPoints.push_back(glm::vec3(6,0,-15));
    pullPoints.push_back(glm::vec3(15,0,-22));
    
    pullPoints.push_back(glm::vec3(30,0,-44));
    pullPoints.push_back(glm::vec3(12,0,-60));
    pullPoints.push_back(glm::vec3(25,0,-42));
    pullPoints.push_back(glm::vec3(10,0,-55));
    pullPoints.push_back(glm::vec3(20,0,-40));
    pullPoints.push_back(glm::vec3(8,0,-50));
    pullPoints.push_back(glm::vec3(15,0,-38));
    pullPoints.push_back(glm::vec3(6,0,-45));
    
    pullPoints.push_back(glm::vec3(-12,0,-60));
    pullPoints.push_back(glm::vec3(-30,0,-44));
    pullPoints.push_back(glm::vec3(-10,0,-55));
    pullPoints.push_back(glm::vec3(-25,0,-42));
    pullPoints.push_back(glm::vec3(-8,0,-50));
    pullPoints.push_back(glm::vec3(-20,0,-40));
    pullPoints.push_back(glm::vec3(-6,0,-45));
    pullPoints.push_back(glm::vec3(-15,0,-38));
    
    pullPoints.push_back(glm::vec3(-30,0,-16));
    pullPoints.push_back(glm::vec3(-12,0,0));
    pullPoints.push_back(glm::vec3(-25,0,-18));
    pullPoints.push_back(glm::vec3(-10,0,-5));
    pullPoints.push_back(glm::vec3(-20,0,-20));
    pullPoints.push_back(glm::vec3(-8,0,-10));
    pullPoints.push_back(glm::vec3(-15,0,-22));
    pullPoints.push_back(glm::vec3(-6,0,-15));
    

    
    curve1 = new BezierCurve(glm::vec3(0,0,0),pullPoints[0],pullPoints[1],glm::vec3(30,0,-30));
    curve2 = new BezierCurve(glm::vec3(0,0,-5),pullPoints[2],pullPoints[3],glm::vec3(25,0,-30));
    curve3 = new BezierCurve(glm::vec3(0,0,-10),pullPoints[4],pullPoints[5],glm::vec3(20,0,-30));
    curve4 = new BezierCurve(glm::vec3(0,0,-15),pullPoints[6],pullPoints[7],glm::vec3(15,0,-30));
    
    curve5 = new BezierCurve(glm::vec3(30,0,-30),pullPoints[8],pullPoints[9],glm::vec3(0,0,-60));
    curve6 = new BezierCurve(glm::vec3(25,0,-30),pullPoints[10],pullPoints[11],glm::vec3(0,0,-55));
    curve7 = new BezierCurve(glm::vec3(20,0,-30),pullPoints[12],pullPoints[13],glm::vec3(0,0,-50));
    curve8 = new BezierCurve(glm::vec3(15,0,-30),pullPoints[14],pullPoints[15],glm::vec3(0,0,-45));
    
    curve9 = new BezierCurve(glm::vec3(0,0,-60),pullPoints[16],pullPoints[17],glm::vec3(-30,0,-30));
    curve10 = new BezierCurve(glm::vec3(0,0,-55),pullPoints[18],pullPoints[19],glm::vec3(-25,0,-30));
    curve11 = new BezierCurve(glm::vec3(0,0,-50),pullPoints[20],pullPoints[21],glm::vec3(-20,0,-30));
    curve12 = new BezierCurve(glm::vec3(0,0,-45),pullPoints[22],pullPoints[23],glm::vec3(-15,0,-30));
    
    curve13 = new BezierCurve(glm::vec3(-30,0,-30),pullPoints[24],pullPoints[25],glm::vec3(0,0,0));
    curve14 = new BezierCurve(glm::vec3(-25,0,-30),pullPoints[26],pullPoints[27],glm::vec3(0,0,-5));
    curve15 = new BezierCurve(glm::vec3(-20,0,-30),pullPoints[28],pullPoints[29],glm::vec3(0,0,-10));
    curve16 = new BezierCurve(glm::vec3(-15,0,-30),pullPoints[30],pullPoints[31],glm::vec3(0,0,-15));
    
    b1 = new BezierBatch(curve1, curve2, curve3, curve4);
    b2 = new BezierBatch(curve5, curve6, curve7, curve8);
    b3 = new BezierBatch(curve9, curve10, curve11, curve12);
    b4 = new BezierBatch(curve13, curve14, curve15, curve16);
	std::vector<glm::vec3> pullPoints2;
	pullPoints2.push_back(glm::vec3(-40, 0, -120));
	pullPoints2.push_back(glm::vec3(40, 0, -120));
	pullPoints2.push_back(glm::vec3(-40, 0, -40));
	pullPoints2.push_back(glm::vec3(40, 0, -40));
	pullPoints2.push_back(glm::vec3(-40, 0, 40));
	pullPoints2.push_back(glm::vec3(40, 0, 40));
	pullPoints2.push_back(glm::vec3(-40, 0, 120));
	pullPoints2.push_back(glm::vec3(40, 0, 120));
	terrain[0] = new BezierCurve(glm::vec3(-120, -1, -120), pullPoints2[0], pullPoints2[1], glm::vec3(120, 0, -120));
	terrain[1] = new BezierCurve(glm::vec3(-120, -1, -40), pullPoints2[2], pullPoints2[3], glm::vec3(120, 0, -40));
	terrain[2] = new BezierCurve(glm::vec3(-120, -1, 40), pullPoints2[4], pullPoints2[5], glm::vec3(120, 0, 40));
	terrain[3] = new BezierCurve(glm::vec3(-120, -1, 120), pullPoints2[6], pullPoints2[7], glm::vec3(120, 0, 120));
	ground = new BezierBatch(terrain[0], terrain[1], terrain[2], terrain[3]);
    
    curves.push_back(curve1);
    curves.push_back(curve2);
    curves.push_back(curve3);
    curves.push_back(curve4);
    curves.push_back(curve5);
    curves.push_back(curve6);
    curves.push_back(curve7);
    curves.push_back(curve8);
    
    model = glm::scale(glm::mat4(1),glm::vec3(0.01f, 0.01f, 0.01f));
    sphereT1 = new Transform(glm::translate(glm::mat4(1), anchorPoints[0]) * model);
    sphereT2 = new Transform(glm::translate(glm::mat4(1), anchorPoints[1]) * model);
    sphereT3 = new Transform(glm::translate(glm::mat4(1), anchorPoints[2]) * model);
    sphereT4 = new Transform(glm::translate(glm::mat4(1), anchorPoints[3]) * model);
    sphereT5 = new Transform(glm::translate(glm::mat4(1), anchorPoints[4]) * model);
    sphereT6 = new Transform(glm::translate(glm::mat4(1), anchorPoints[5]) * model);
    sphereT7 = new Transform(glm::translate(glm::mat4(1), anchorPoints[6]) * model);
    sphereT8 = new Transform(glm::translate(glm::mat4(1), anchorPoints[7]) * model);
    
    sphereT1->addChild(sphereGeo);
    sphereT2->addChild(sphereGeo);
    sphereT3->addChild(sphereGeo);
    sphereT4->addChild(sphereGeo);
    sphereT5->addChild(sphereGeo);
    sphereT6->addChild(sphereGeo);
    sphereT7->addChild(sphereGeo);
    sphereT8->addChild(sphereGeo);
    
    pullT1 = new Transform(glm::translate(glm::mat4(1), pullPoints[0]) * model);
    pullT2 = new Transform(glm::translate(glm::mat4(1), pullPoints[1]) * model);
    pullT3 = new Transform(glm::translate(glm::mat4(1), pullPoints[2]) * model);
    pullT4 = new Transform(glm::translate(glm::mat4(1), pullPoints[3]) * model);
    pullT5 = new Transform(glm::translate(glm::mat4(1), pullPoints[4]) * model);
    pullT6 = new Transform(glm::translate(glm::mat4(1), pullPoints[5]) * model);
    pullT7 = new Transform(glm::translate(glm::mat4(1), pullPoints[6]) * model);
    pullT8 = new Transform(glm::translate(glm::mat4(1), pullPoints[7]) * model);
    pullT9 = new Transform(glm::translate(glm::mat4(1), pullPoints[8]) * model);
    pullT10 = new Transform(glm::translate(glm::mat4(1), pullPoints[9]) * model);
    pullT11 = new Transform(glm::translate(glm::mat4(1), pullPoints[10]) * model);
    pullT12 = new Transform(glm::translate(glm::mat4(1), pullPoints[11]) * model);
    pullT13 = new Transform(glm::translate(glm::mat4(1), pullPoints[12]) * model);
    pullT14 = new Transform(glm::translate(glm::mat4(1), pullPoints[13]) * model);
    pullT15 = new Transform(glm::translate(glm::mat4(1), pullPoints[14]) * model);
    pullT16 = new Transform(glm::translate(glm::mat4(1), pullPoints[15]) * model);
    
    pullT1->addChild(sphereGeo);
    pullT2->addChild(sphereGeo);
    pullT3->addChild(sphereGeo);
    pullT4->addChild(sphereGeo);
    pullT5->addChild(sphereGeo);
    pullT6->addChild(sphereGeo);
    pullT7->addChild(sphereGeo);
    pullT8->addChild(sphereGeo);
    pullT9->addChild(sphereGeo);
    pullT10->addChild(sphereGeo);
    pullT11->addChild(sphereGeo);
    pullT12->addChild(sphereGeo);
    pullT13->addChild(sphereGeo);
    pullT14->addChild(sphereGeo);
    pullT15->addChild(sphereGeo);
    pullT16->addChild(sphereGeo);
    
    sphereAnch = new Transform(glm::mat4(1));
    sphereAnch->addChild(sphereT1);
    sphereAnch->addChild(sphereT2);
    sphereAnch->addChild(sphereT3);
    sphereAnch->addChild(sphereT4);
    sphereAnch->addChild(sphereT5);
    sphereAnch->addChild(sphereT6);
    sphereAnch->addChild(sphereT7);
    sphereAnch->addChild(sphereT8);
    
    spherePull = new Transform(glm::mat4(1));
    spherePull->addChild(pullT1);
    spherePull->addChild(pullT2);
    spherePull->addChild(pullT3);
    spherePull->addChild(pullT4);
    spherePull->addChild(pullT5);
    spherePull->addChild(pullT6);
    spherePull->addChild(pullT7);
    spherePull->addChild(pullT8);
    spherePull->addChild(pullT9);
    spherePull->addChild(pullT10);
    spherePull->addChild(pullT11);
    spherePull->addChild(pullT12);
    spherePull->addChild(pullT13);
    spherePull->addChild(pullT14);
    spherePull->addChild(pullT15);
    spherePull->addChild(pullT16);

    lastTime = glfwGetTime();
    waterSound = SoundEngine->addSoundSourceFromFile("water.wav");
    SoundEngine->play2D("wind.wav", GL_TRUE);
    return true;
}

void Window::cleanUp()
{
    // Deallcoate the objects.


    // Delete the shader program.
    glDeleteProgram(program);
}

GLFWwindow* Window::createWindow(int width, int height)
{
    // Initialize GLFW.
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    // Apple implements its own version of OpenGL and requires special treatments
    // to make it uses modern OpenGL.

    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the GLFW window.
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    // Check if the window could not be created.
    if (!window)
    {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    // On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

    // Initialize GLEW.
    if (glewInit())
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return NULL;
    }
#endif

    // Set swap interval to 1.
    glfwSwapInterval(0);

    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);

    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    // Set the projection matrix.
    Window::projection = glm::perspective(glm::radians(60.0),
        double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{

}

void Window::displayCallback(GLFWwindow* window)
{
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Window::view = glm::lookAt(Window::eye, Window::eye + Window::direction, Window::up);
   

    
    // Specify the values of the uniform variables we are going to use.
    glm::mat4 model = sphereGeo->getModel();
    glm::vec3 color(1,0,0);
    glUseProgram(program);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glUniform3f(glGetUniformLocation(program, "cameraPos"), Window::eye.x, Window::eye.y, Window::eye.z);
    //sphereT->draw(program, glm::mat4(1));
    
    glUniform1f(glGetUniformLocation(program, "t"),waveDegree);
    waveDegree++;
    model = glm::mat4(1);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    b1->draw();
    b2->draw();
    b3->draw();
    b4->draw();
	glUseProgram(starterProgram);
	glm::vec3 ambient = glm::vec3(0.9f, 0.9f, 0.9f);
	glm::vec3 diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	glm::vec3 specular = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 lightPosition = glm::vec3(0.0f, 30.0f, -30.0f);
	float shininess = 0.0f;
	glUniformMatrix4fv(projectionCurveLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewCurveLoc, 1, GL_FALSE, glm::value_ptr(view));
	glm::vec3 translate(0.0f, 0.0f, -30.0f);
	//glm::mat4 transform = glm::translate(glm::mat4(), translate);

	glUniformMatrix4fv(modelCurveLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(ambientLoc, 1, glm::value_ptr(ambient));
	glUniform3fv(diffuseLoc, 1, glm::value_ptr(diffuse));
	glUniform3fv(specularLoc, 1, glm::value_ptr(specular));
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPosition));
	glUniform3fv(viewPosLoc, 1, glm::value_ptr(eye));
	glUniform1f(shinyLoc, shininess);
	ground->draw();
	glUniformMatrix4fv(modelCurveLoc, 1, GL_FALSE, glm::value_ptr(glm::translate(bear->getModel(),translate)));
	//glTranslatef(0.0f,0.0f,-12.0f);
	bear->draw();
    

    glUseProgram(skyboxProgram);
    
    view = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(projectionSkyLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewSkyLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelSkyLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    
    skybox->draw();

    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /*
     * Modify below to add your key callbacks.
     */
    // Check for a key press.
    if (action == GLFW_REPEAT)
    {
        
        float cameraSpeed = 0.5f;
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_1:
            // Set the mode to mode 1
            modeOne = true;
            modeTwo = false;
            modeThree = false;
            break;
        case GLFW_KEY_2:
            // Set the mode to mode 2
            modeOne = false;
            modeTwo = true;
            modeThree = false;
            break;
        case GLFW_KEY_3:
            // Set the mode to mode 3
            modeOne = false;
            modeTwo = false;
            modeThree = true;
            break;
        case GLFW_KEY_W:
            Window::eye += cameraSpeed * glm::vec3(direction.x,0,direction.z);
            if(Window::delay % 6 == 0){
                SoundEngine->play2D("Single-footstep-snow.wav", GL_FALSE);
            }
            Window::delay++;
            if(isWaterSound && glm::distance(eye, glm::vec3(0,0,-30)) < 70){
                SoundEngine->play2D(waterSound);
                isWaterSound = false;
            }
            else if(glm::distance(eye, glm::vec3(0,0,-30)) >= 70){
                if(!isWaterSound)
                {
                    isWaterSound = true;
                    SoundEngine->stopAllSoundsOfSoundSource(waterSound);
                    
                }
            }
            break;
        case GLFW_KEY_A:
            Window::eye -= glm::normalize(glm::cross(glm::vec3(direction.x, 0, direction.z), up)) * cameraSpeed;
            if(Window::delay % 3 == 0){
                SoundEngine->play2D("Single-footstep-snow.wav", GL_FALSE);
            }
            Window::delay++;
             if(isWaterSound && glm::distance(eye, glm::vec3(0,0,-30)) < 70){
                    SoundEngine->play2D(waterSound);
                    isWaterSound = false;
                }
                else if(glm::distance(eye, glm::vec3(0,0,-30)) >= 70){
                    if(!isWaterSound)
                    {
                        isWaterSound = true;
                        SoundEngine->stopAllSoundsOfSoundSource(waterSound);
                        
                    }
                }
            break;
        case GLFW_KEY_S:
            Window::eye -= cameraSpeed * glm::vec3(direction.x, 0, direction.z);
            if(Window::delay % 3 == 0){
                SoundEngine->play2D("Single-footstep-snow.wav", GL_FALSE);
            }
            Window::delay++;
            if(isWaterSound && glm::distance(eye, glm::vec3(0,0,-30)) < 70){
                    SoundEngine->play2D(waterSound);
                    isWaterSound = false;
                }
                else if(glm::distance(eye, glm::vec3(0,0,-30)) >= 70){
                    if(!isWaterSound)
                    {
                        isWaterSound = true;
                        SoundEngine->stopAllSoundsOfSoundSource(waterSound);
                        
                    }
                }
            break;
        case GLFW_KEY_D:
            Window::eye += glm::normalize(glm::cross(glm::vec3(direction.x, 0, direction.z), up)) * cameraSpeed;
            if(Window::delay % 3 == 0){
                SoundEngine->play2D("Single-footstep-snow.wav", GL_FALSE);
            }
            Window::delay++;
            if(isWaterSound && glm::distance(eye, glm::vec3(0,0,-30)) < 70){
                    SoundEngine->play2D(waterSound);
                    isWaterSound = false;
                }
            else if(glm::distance(eye, glm::vec3(0,0,-30)) >= 70){
                    if(!isWaterSound)
                    {
                        isWaterSound = true;
                        SoundEngine->stopAllSoundsOfSoundSource(waterSound);
                        
                    }
                }
            break;
        case GLFW_KEY_F1:
            // Set currentObj to bunny
            currentObj = bunny;
            break;
        case GLFW_KEY_F2:
            // Set currentObj to bear
            currentObj = bear;
            break;
        case GLFW_KEY_F3:
            // Set currentObj to dragon
            currentObj = dragon;
            break;
        case GLFW_KEY_N:
            if(isNorm == 1){
                isNorm = 0;
            }
            else{
                isNorm = 1;
            }
            glUniform1i(condLoc, isNorm);
            break;
        default:
            break;
        }
    }
}
void Window::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
    {
        fov += 7.5f;
        if(fov <= 5.0f)
          fov = 5.0f;
        if(fov >= 140.0f)
          fov = 140.0f;
        
        projection = glm::perspective(glm::radians(fov), (float)width/(float)height, 0.1f, 1000.0f);
        
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        fov -= 7.5f;
        if(fov <= 5.0f)
          fov = 5.0f;
        if(fov >= 140.0f)
        fov = 140.0f;
        projection = glm::perspective(glm::radians(fov), (float)width/(float)height, 0.1f, 1000.0f);
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
                isRotate = true;
                start = trackBallMapping(point);
        }
        
        if(action == GLFW_RELEASE){
                isRotate = false;
        }
        
    }
}
void Window::cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
     if(firstMouse)
       {
           lastX = xpos;
           lastY = ypos;
           firstMouse = false;
       }
     
       float xoffset = xpos - lastX;
       float yoffset = lastY - ypos;
       lastX = xpos;
       lastY = ypos;

       float sensitivity = 0.5;
       xoffset *= sensitivity;
       yoffset *= sensitivity;

       yaw   += xoffset;
       pitch += yoffset;

       if(pitch > 89.0f)
           pitch = 89.0f;
       if(pitch < -89.0f)
           pitch = -89.0f;

       glm::vec3 front;
       front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
       front.y = sin(glm::radians(pitch));
       front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
       direction = glm::normalize(front);
    
}

glm::vec3 Window::trackBallMapping(glm::vec2 point) {
    glm::vec3 v;
    float d;
    v.x = (2.0f * point.x - width) / width;
    v.y = (height - 2.0f * point.y) / height;
    v.z = 0.0f;
    d = glm::length(v);
    d = (d < 1.0f) ? d : 1.0f;
    v.z = sqrtf(1.001f - d * d);
    v = glm::normalize(v);
    return(v);
}

bool Window::isVisible(glm::vec3 x, float r, std::vector<std::pair<glm::vec3, glm::vec3>> planes){
    for(auto plane: planes){
        glm::vec3 p = plane.first;
        glm::vec3 n = plane.second;
        
        float dist = glm::dot((x-p), n);
        if(dist < -r){
            return false;
        }
    }
    return true;
}

