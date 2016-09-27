#include <iostream>
#include "knight.h"



Knight::Knight(Cell * pos): Cpiece('n', pos, 5){}

char Knight::getName(){return piecename;}


void Knight::addPossibleMove(Grid & grid){
	if(killedpiece){
		return;
	}		
	clearMove();
	bool colour = pos->whitepiece();
	int r = pos->getR();
	int c = pos->getC();
	int i = 0;
	int i2 = 0;
	int ar = r - 2; int ac = c - 1;
	int br = r - 2; int bc = c + 1;
	int cr = r - 1; int cc = c + 2;
	int dr = r + 1; int dc = c + 2;
	int er = r + 2; int ec = c + 1;
	int fr = r + 2; int fc = c - 1;
	int gr = r + 1; int gc = c - 2;
	int hr = r - 1; int hc = c - 2;
	//grid[ar][ac].isoccupied();
	while(i2 <= 8){
	if(ar>=0 && ar <= 7 && ac >=0 && ac <= 7)
	{
		Cell * temp = grid.getcell(ar,ac);
		if(temp->isoccupied())
		{
			if(colour != temp->whitepiece())
			{
				possiblemove[i] = temp;
				i++;
			}
		}
		else
		{
			possiblemove[i] = temp;
			i++;
		}
	}
	if(i2 == 1){
		ar = br;
		ac = bc;
	}else if(i2 == 2){
		ar = cr;
		ac = cc;	
	}else if(i2 == 3){
		ar = dr;
		ac = dc;
	}else if(i2 == 4){
		ar = er;
		ac = ec;
	}else if(i2 == 5){
		ar = fr;
		ac = fc;
	}else if(i2 == 6){
		ar = gr;
		ac = gc;
	}else if(i2 == 7){
		ar = hr;
		ac = hc;
	}
		i2++;
	}
}
