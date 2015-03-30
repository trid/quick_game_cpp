//
// Created by TriD on 23.03.2015.
//

#include <SDL2/SDL_image.h>
#include "PlayerCharacter.h"
#include "View.h"

PlayerCharacter::PlayerCharacter() {
    texture = IMG_LoadTexture(View::getInstance().getRenderer(), "res/images/character.png");
}

void PlayerCharacter::draw() {
    SDL_Rect rect { x * 32, y * 32 - 16, 32, 48};
    SDL_RenderCopy(View::getInstance().getRenderer(), texture, nullptr, &rect);
}
