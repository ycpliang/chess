#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <iostream>
#include "cpiece.h"
#include "score.h"
class Grid;
const int maxpieces = 16;

class Player {
  bool ai;
  bool wpiece;
  bool wmove;
  int levelai;
  bool ischecked;
//  bool checkmate;
  Cpiece * pieces[maxpieces];
  bool addpiece(); //to add on a new piece after pawn is promoted
  public:
  	 int npieces;
	 Player();
	 Cpiece * getpiece(int i);
	 void initPlayer(bool, bool);//initialize player
	 void initPlayer(bool, bool, int);//initialize ai
	 void initPieces(Grid &); //initialize all the pieces
	 bool canBlock(Cell * ncell);
	 bool getwmove();
	 bool makeMove(int whichpiece, Cell * cell);//also notify display
	 bool isChecked(Cell *);
	 void promote(int, Cell * , char);
//	 int totalWorth(); //return the current worth of player pieces
         void killPiece(int whichpiece); //kill the piece
	 bool isStalemate(Player &, Grid &);
	 bool isCheckmate(Cpiece *);
	 void addpossiblemove(Grid &);
	 bool aiMoves(Grid &, Player &, Score &);
	 int killCheck(Player & other, Cell * aiNewPos);
         bool aiCheck(Grid & gameOn, Player & black, int, Cell * cell, Cpiece * temp2, Score &);
//         bool allCheck(Grid & gameOn, Player & black, Cpiece * temp, Cell * cell, Cpiece * temp2, Score &);
	 bool aiLevel1(Grid &, Player &, Score &);
	 bool aiLevel2(Grid &, Player &, Score &);
	 bool aiLevel3(Grid &, Player &, Score &);
	 void clearPieces();
	 ~Player();
	
};
#endif
