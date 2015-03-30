//
// Created by TriD on 22.03.2015.
//

#ifndef _QUICK_GAME_CPP_VIEW_H_
#define _QUICK_GAME_CPP_VIEW_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>

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

    //Map data
    GLuint floorVertices;
    GLuint floorIndices;
public:
    SDL_Renderer* getRenderer() { return renderer; }

    static View &getInstance();

    void generateMapView(GameMap* map);
    void draw();
};


#endif //_QUICK_GAME_CPP_VIEW_H_
