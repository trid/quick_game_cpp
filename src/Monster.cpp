//
// Created by TriD on 23.03.2015.
//

#include <SDL2/SDL_image.h>
#include "Monster.h"
#include "View.h"

Monster::Monster() {
    texture = IMG_LoadTexture(View::getInstance().getRenderer(), "res/images/monster.png");
}

void Monster::draw() {
    SDL_Rect rect { x * 32, y * 32, 32, 32};
    SDL_RenderCopy(View::getInstance().getRenderer(), texture, nullptr, &rect);
}
