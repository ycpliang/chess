#ifndef __SCORE2_H__
#define __SCORE2_H__
#include <iostream>

class Score{
int whitescore;
int blackscore;
public:
	Score();
	int whiteScore();
	int blackScore();
	void addWhite();
	void addBlack();
};

#endif
