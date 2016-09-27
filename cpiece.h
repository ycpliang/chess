#ifndef __CPIECE_H__
#define __CPIECE_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "grid.h"

const int maxthreat = 8;
const int maxlegalmove = 27;

class Cpiece{
protected:
	char piecename;
//	bool canmove; //is there moves available for this piece
	Cell * pos;
	bool reverse;
	bool killedpiece;
	int piecemoved; //the number of move the piece made (also for AI)
//	Cell *attacking[maxthreat]; //the number of attacking cell (needed to check whether move threatens the king)
   	Cell *possiblemove[maxlegalmove]; //needed for stalemate and checkmate // endcheck
	public:
		int value;
	        Cpiece(char piecename, Cell * pos , int);
		void removePiece();
		bool isKilled();
		void reverseOn();
		virtual char getName() = 0;
		Cell * returnaMove(int);
		void revive(bool);
//		virtual void reverseOn();
//		bool behaviour() = 0; //pure virtual behaviour
//		bool attacking() = 0; //make move assigns the attacking cells
		virtual bool makeMove(Cell *); //pure virtual makemove 
		 		//(dont know if it is neccessary)
		Cell * getPos(); //return cell
		virtual void addPossibleMove(Grid &) = 0; //add possible move
		void clearMove();//clear possiblemove
//		~Cpiece();		 		
};

#endif
