/*
 * main.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: Carol
 */

#include "../headers/StateManager.h"
#include <time.h>

int main(int argc, char *argv[]) {

	srand (time(NULL));
    StateManager *stateManager = new StateManager();
    stateManager->run();

    return 0;
}


