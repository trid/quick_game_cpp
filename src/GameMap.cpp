//
// Created by TriD on 22.03.2015.
//

#include "GameMap.h"
#include "View.h"

#include <fstream>
#include "SDL2/SDL_image.h"

using std::fstream;

GameMap::GameMap() {
    fstream mapFile("res/maps/map.txt");
    mapData.push_back(MapRow());
    while (!mapFile.eof()) {
        char c = (char)mapFile.get();
        if (c != '\n') {
            mapData.back().push_back(c);
        }
        else {
            mapData.push_back(MapRow());
        }
    }
    SDL_Renderer* renderer = View::getInstance().getRenderer();

    wallTexture = IMG_LoadTexture(renderer, "res/images/wall.png");
    floorTexture = IMG_LoadTexture(renderer, "res/images/floor.png");
    chestTexture = IMG_LoadTexture(renderer, "res/images/chest.png");
}

void GameMap::draw() {
    SDL_Renderer* renderer = View::getInstance().getRenderer();

    for (int i = 0; i < mapData.size(); i++) {
        for (int k = 0; k < mapData[i].size(); k++) {
            SDL_Rect rect = { k * 32, i * 32, 32, 32 };
            switch (mapData[i][k]) {
                case '1':
                    SDL_RenderCopy(renderer, wallTexture, NULL, &rect);
                    break;
                case '2':
                    SDL_RenderCopy(renderer, floorTexture, NULL, &rect);
                    break;
                case '3':
                    SDL_RenderCopy(renderer, chestTexture, NULL, &rect);
                    break;
                default:
                    break;
            }
        }
    }
}
