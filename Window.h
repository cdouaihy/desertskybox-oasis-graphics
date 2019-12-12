#ifndef _WINDOW_H_
#define _WINDOW_H_

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "Transform.h"
#include "Node.h"
#include "Geometry.h"
#include "Skybox.h"
#include "BezierCurve.h"
#include "shader.h"
#include "BezierBatch.h"

#include "./irrKlang-64bit-1.6.0/include/irrKlang.h"

class Window
{
public:
    static int width;
    static int height;
    static const char* windowTitle;
    static Cube* cube;
    static PointCloud * cubePoints;
    static PointCloud * bunny;
    static PointCloud * bear;
    static PointCloud * dragon;
    static PointCloud * sphere;
    static Geometry * robot;

    static Transform * robotroot;
    static Transform * head;
    static Transform * body;
    static Transform * larm;
    static Transform * rarm;
    static Transform * lleg;
    static Transform * rleg;
    static Transform * leye;
    static Transform * reye;
    static Transform * sphereT;
    static Transform * sphereAnch;
    static Transform * sphereT1;
    static Transform * sphereT2;
    static Transform * sphereT3;
    static Transform * sphereT4;
    static Transform * sphereT5;
    static Transform * sphereT6;
    static Transform * sphereT7;
    static Transform * sphereT8;
    
    static Transform * spherePull;
    static Transform * pullT1;
    static Transform * pullT2;
    static Transform * pullT3;
    static Transform * pullT4;
    static Transform * pullT5;
    static Transform * pullT6;
    static Transform * pullT7;
    static Transform * pullT8;
    static Transform * pullT9;
    static Transform * pullT10;
    static Transform * pullT11;
    static Transform * pullT12;
    static Transform * pullT13;
    static Transform * pullT14;
    static Transform * pullT15;
    static Transform * pullT16;
    
    static Transform * track;
    
    static Geometry * headGeo;
    static Geometry * bodyGeo;
    static Geometry * limbGeo;
    static Geometry * eyeGeo;
    static Geometry * sphereGeo;
    
    static Skybox * skybox;
    
    static std::vector<glm::vec3> anchorPoints;
    static std::vector<glm::vec3> pullPoints;
    static BezierCurve * curve1;
    static BezierCurve * curve2;
    static BezierCurve * curve3;
    static BezierCurve * curve4;
    static BezierCurve * curve5;
    static BezierCurve * curve6;
    static BezierCurve * curve7;
    static BezierCurve * curve8;
    static BezierCurve * curve9;
    static BezierCurve * curve10;
    static BezierCurve * curve11;
    static BezierCurve * curve12;
    static BezierCurve * curve13;
    static BezierCurve * curve14;
    static BezierCurve * curve15;
    static BezierCurve * curve16;
	static BezierCurve* terrain[4];
    static int curr;
    static float waveDegree;
    static std::vector<BezierCurve *> curves;
    
    static BezierBatch * b1;
    static BezierBatch * b2;
    static BezierBatch * b3;
    static BezierBatch * b4;
	static BezierBatch* ground;

    static Object * currentObj;
    static Geometry * currentNode;
    static float lastTime;
    static float currentTime;
    
    static float deltaTime;
    static float lastFrame;
    
    static float lastX;
    static float lastY;
    
    static float yaw;
    static float pitch;
    
    static int delay;
    
    static irrklang::ISoundEngine * SoundEngine;
    static irrklang::ISoundSource * waterSound;
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 eye, center, up, direction, cameraRight, cameraUp;
    static glm::vec2 point;
    static glm::vec3 start;
    static glm::vec3 lightPos;
    static bool isRotate, modeOne, modeTwo, modeThree, isScaled, isWaterSound, firstMouse, isWave;
    static int isNorm;
    static float fov;
    static GLuint starterProgram, program, anchProgram, pullProgram, skyboxProgram, projectionLoc, viewLoc, projectionSkyLoc, viewSkyLoc, projectionCurveLoc, viewCurveLoc, modelCurveLoc,projectionAnchLoc, viewAnchLoc, modelAnchLoc, projectionPullLoc, viewPullLoc, modelPullLoc,modelLoc, modelSkyLoc, colorLoc, lightPosLoc, lightColorLoc, viewPosLoc, ambientLoc, diffuseLoc, specularLoc, shinyLoc, condLoc;

    static bool initializeProgram();
    static bool initializeObjects();
    static void cleanUp();
    static void animateWaves();
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);
    static void idleCallback();
    static void initializeBatch();
    static void displayCallback(GLFWwindow*);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    static glm::vec3 trackBallMapping(glm::vec2 point);
    static bool isVisible(glm::vec3 x, float r, std::vector<std::pair<glm::vec3, glm::vec3>> planes);
};

#endif
