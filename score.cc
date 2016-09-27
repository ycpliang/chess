#include "score.h"
#include <iostream>


Score::Score():whitescore(0), blackscore(0){}

int Score::whiteScore(){
	return whitescore;
}

int Score::blackScore(){
	return blackscore;
}

void Score::addWhite(){
	whitescore++;
}

void Score::addBlack(){
	blackscore++;
}
