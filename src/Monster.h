//
// Created by TriD on 23.03.2015.
//

#ifndef _QUICK_GAME_CPP_MONSTER_H_
#define _QUICK_GAME_CPP_MONSTER_H_


#include <SDL2/SDL.h>

class Monster {
private:
    int x = 7, y = 4;
    SDL_Texture* texture;
public:
    Monster();
    void draw();
};


#endif //_QUICK_GAME_CPP_MONSTER_H_
