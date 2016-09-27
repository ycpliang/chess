#include <iostream>
#include "queen.h"

Queen::Queen(Cell * pos): Cpiece('q', pos, 8){}

char Queen::getName(){return piecename;}


void Queen::addPossibleMove(Grid & grid){
	if(killedpiece){
		return;
	}		
	clearMove();
	bool colour = pos->whitepiece();
	int r = pos->getR();
	int c = pos->getC();
	int i = 0;
	int i2 = 0;
	int addnum = 1;
	Cell * temp;
	int zr, zc;
	bool abool[8] = {true, true, true, true, true, true, true, true};
	while(addnum < 8 && (abool[0] || abool[1] || 
		abool[2] || abool[3] || abool[4] || abool[5]
		|| abool[6] || abool[7])){
	int ar = r - addnum; int ac = c - addnum;
	int br = r - addnum; int bc = c;
	int cr = r - addnum; int cc = c + addnum;
	int dr = r; 	     int dc = c + addnum;
	int er = r + addnum; int ec = c + addnum;
	int fr = r + addnum; int fc = c;
	int gr = r + addnum; int gc = c - addnum;
	int hr = r; 	     int hc = c - addnum;
	while(i2 < 8){
		if(i2 == 0){
			if(abool[i2]){
				zr = ar;
				zc = ac;
			}else{
				i2++;
			}
		}
		if(i2 == 1){
			if(abool[i2]){
				zr = br;
				zc = bc;
			}else{
				i2++;
			}
		}
		if(i2 == 2){
			if(abool[i2]){
				zr = cr;
				zc = cc;
			}else{
				i2++;
			}	
		}
		if(i2 == 3){
			if(abool[i2]){
				zr = dr;
				zc = dc;
			}else{
				i2++;
			}
		}
		if(i2 == 4){
			if(abool[i2]){
				zr = er;
				zc = ec;
			}else{
				i2++;
			}
		}
		if(i2 == 5){
			if(abool[i2]){
				zr = fr;
				zc = fc;
			}else{
				i2++;
			}
		}
		if(i2 == 6){
			if(abool[i2]){
				zr = gr;
				zc = gc;
			}else{
				i2++;
			}
		}
		if(i2 == 7){
			if(abool[i2]){
				zr = hr;
				zc = hc;
			}else{
				i2++;
			}
		}

		if(i2 == 8){
			break;
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
				abool[i2] = false;
			}else{
				possiblemove[i] = temp;
				i++;
			}	
		}
		i2++;
	}
		i2 = 0;
		addnum++;
	}
}
