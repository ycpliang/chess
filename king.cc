#include <iostream>
#include "king.h"



King::King(Cell * pos): Cpiece('k', pos, 10){}

char King::getName(){return piecename;}


void King::addPossibleMove(Grid & grid){
	if(killedpiece){
		return;
	}		
	clearMove();
	bool colour = pos->whitepiece();
	int r = pos->getR();
	int c = pos->getC();
	int i = 0;
	int i2 = 0;
	Cell * temp;
	int zr, zc;
	int ar = r - 1; int ac = c - 1;
	int br = r - 1; int bc = c;
	int cr = r - 1; int cc = c + 1;
	int dr = r; 	int dc = c + 1;
	int er = r + 1; int ec = c + 1;
	int fr = r + 1; int fc = c;
	int gr = r + 1; int gc = c - 1;
	int hr = r; 	int hc = c - 1;
	while(i2 < 8){
		if(i2 == 0){
			zr = ar;
			zc = ac;
		}else if(i2 == 1){
			zr = br;
			zc = bc;
		}else if(i2 == 2){
			zr = cr;
			zc = cc;	
		}else if(i2 == 3){
			zr = dr;
			zc = dc;
		}else if(i2 == 4){
			zr = er;
			zc = ec;
		}else if(i2 == 5){
			zr = fr;
			zc = fc;
		}else if(i2 == 6){
			zr = gr;
			zc = gc;
		}else if(i2 == 7){
			zr = hr;
			zc = hc;
		}
		if(zr>=0 && zr <= 7 && zc >=0 && zc <= 7)
		{
			temp = grid.getcell(zr,zc);
			if(temp->isoccupied())
			{
				if(colour != temp->whitepiece())
				{	
					possiblemove[i] = temp;
					i++;
				}
			}else{
				possiblemove[i] = temp;
				i++;
			}	
		}
		i2++;
	}
	int row;
	if(colour){
		row = 7;
	}else{
		row = 0;
	}

	if(piecemoved == 0){
		bool emptyd1 = (grid.getcell(row,3))->isoccupied();
		bool emptyc1 = (grid.getcell(row, 2))->isoccupied();
		bool emptyb1 = (grid.getcell(row, 1))->isoccupied();
		bool hasa1 = (grid.getcell(row, 0))->isoccupied();
		Cell * castling = grid.getcell(row, 2);
		if(!emptyd1 && !emptyc1 && !emptyb1 && hasa1){
			possiblemove[i] = castling;
			i++;
		}	
		bool emptyf1 = (grid.getcell(row,5))->isoccupied();
		bool emptyg1 = (grid.getcell(row, 6))->isoccupied();
		bool hash1 = (grid.getcell(row, 7))->isoccupied();
		castling = grid.getcell(row, 6);
		if(!emptyf1 && !emptyg1 && hash1){
			possiblemove[i] = castling;
			i++;
		}	
		
	}
	

}
