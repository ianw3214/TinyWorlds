#include "gameState.hh"

// EMPTY DEFAULT CONSTRUCTOR
gameState::gameState() {

}

// functions to handle changing game states
bool gameState::getChangeState() {
	return this->changeState;
}
gameState * gameState::getNextState() {
	return this->nextState;
}