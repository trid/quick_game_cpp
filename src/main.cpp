#include <iostream>
#include "GameMap.h"
#include "View.h"
#include "PlayerCharacter.h"
#include "Monster.h"

using namespace std;

enum Status{
    STATUS_RUNNING,
    STATUS_WIN,
    STATUS_LOSE,
    STATUS_EXIT
};

Status gameStatus = STATUS_RUNNING;

int main(int argc, char* argv[]) {
    View& view = View::getInstance();
    GameMap gameMap;
    PlayerCharacter playerCharacter;
    Monster monster;

    view.generateMapView(&gameMap);

    while (gameStatus == STATUS_RUNNING) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameStatus = STATUS_EXIT;
            }
            if (event.type == SDL_KEYUP) {
                view.cameraDirection.z += 0.5f;
            }
        }
        /*gameMap.draw();
        playerCharacter.draw();
        monster.draw();

        SDL_RenderPresent(view.getRenderer());*/
        view.draw();
    }
    return 0;
}