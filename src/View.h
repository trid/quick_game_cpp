//
// Created by TriD on 22.03.2015.
//

#ifndef _QUICK_GAME_CPP_VIEW_H_
#define _QUICK_GAME_CPP_VIEW_H_


#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL2/SDL.h>


//GLM is just great!
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"

class GameMap;

class View {
private:
    View();
    View(View&) = delete;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_GLContext glContext;

    void initOpenGL();
    void loadShaders();

    //Shader data
    GLuint shaderProgram;

    //Map data
    GLuint floorVertices;
    GLuint floorIndices;
    int mapSize;

    //Camera data.
    glm::vec3 cameraLocation;
public:
    glm::vec3 cameraDirection;
    SDL_Renderer* getRenderer() { return renderer; }

    static View &getInstance();

    void generateMapView(GameMap* map);
    void draw();
};


#endif //_QUICK_GAME_CPP_VIEW_H_
