#include <iostream>
#include "GameMap.h"
#include "View.h"
#include "PlayerCharacter.h"
#include "Monster.h"

using namespace std;

enum Status{
    STATUS_RUNNING,
    STATUS_WIN,
    STATUS_LOSE
};

Status gameStatus = STATUS_RUNNING;

int main(int argc, char* argv[]) {
    View& view = View::getInstance();
    GameMap gameMap;
    PlayerCharacter playerCharacter;
    Monster monster;

    view.generateMapView(&gameMap);

    while (gameStatus == STATUS_RUNNING) {
        /*gameMap.draw();
        playerCharacter.draw();
        monster.draw();

        SDL_RenderPresent(view.getRenderer());*/
        view.draw();
    }
    return 0;
}