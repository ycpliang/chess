#include <iostream>
#include "pawn.h"



Pawn::Pawn(Cell * pos): Cpiece('p', pos , 1){}

char Pawn::getName(){return piecename;}

void Pawn::addPossibleMove(Grid & grid){
	if(killedpiece){
		return;
	}		
	clearMove();
	bool colour = pos->whitepiece();
	int r = pos->getR();
	int c = pos->getC();
	int i = 0;
	int addnum = 1;
	Cell * temp;
	if(colour){
		addnum = -1;
	}
	if(r+addnum >= 0 && r+addnum <= 7){ 
		temp = grid.getcell(r + addnum,c);
		if(!temp->isoccupied()){
		possiblemove[i] = temp;
		i++;
		}
	}
	if((r + (2 * addnum)) >= 0 && (r + (2 * addnum)) <= 7 && piecemoved == 0){
		temp = grid.getcell(r + addnum,c);
		if(!temp->isoccupied()){
			temp = grid.getcell(r + (2 * addnum),c);
			if(!temp->isoccupied()){
				possiblemove[i] = temp;
				i++;
			}
		}
	}
	if(r+addnum >= 0 && r+addnum <= 7 && c-1 >= 0){
		temp = grid.getcell(r + addnum, c - 1);
		if(temp->isoccupied() && temp->whitepiece() != colour){
			possiblemove[i] = temp;
			i++;
		}
	}
	if(r+ addnum >= 0 && r+addnum <= 7 && c + 1 <= 7){
		temp = grid.getcell(r+addnum,c+1);
		if(temp->isoccupied() && temp->whitepiece() != colour){
			possiblemove[i] = temp;
			i++;
		}
	}
}
