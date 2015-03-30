//
// Created by TriD on 23.03.2015.
//

#ifndef _QUICK_GAME_CPP_GAMECHARACTER_H_
#define _QUICK_GAME_CPP_GAMECHARACTER_H_


#include <SDL2/SDL.h>

class PlayerCharacter {
private:
    int x = 1, y = 1;
    SDL_Texture* texture;
public:
    PlayerCharacter();
    void draw();
};


#endif //_QUICK_GAME_CPP_GAMECHARACTER_H_
