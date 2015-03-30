//
// Created by TriD on 22.03.2015.
//

#ifndef _QUICK_GAME_CPP_GAMEMAP_H_
#define _QUICK_GAME_CPP_GAMEMAP_H_

#include <vector>
#include <SDL2/SDL.h>

using std::vector;

typedef vector<char> MapRow;

class GameMap {
friend class View;
private:
    vector<MapRow> mapData;
    SDL_Texture* wallTexture;
    SDL_Texture* floorTexture;
    SDL_Texture* chestTexture;
public:
    GameMap();
    void draw();
    int getItem(int x, int y) { return mapData[y][x]; }
};


#endif //_QUICK_GAME_CPP_GAMEMAP_H_
