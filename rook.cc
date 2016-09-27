#include <iostream>
#include "rook.h"



Rook::Rook(Cell * pos): Cpiece('r', pos, 7){}

char Rook::getName(){return piecename;}


void Rook::addPossibleMove(Grid & grid)
{
	if(killedpiece){
		return;
	}		
	clearMove();
	bool colour = pos->whitepiece();
	int r = pos->getR();
	int c = pos->getC();
	int nr = r;
	int nc = c;
	int i = 0;
	Cell * tmp;

	while(nc < 8)  //r remains the same, c increase
	{
		if(nc == c){nc++;}
		if(nc >= 8){break;} 
		tmp = grid.getcell(r, nc);
		if(tmp->isoccupied())
		{
			if(colour != tmp->whitepiece())
			{
				possiblemove[i] = tmp;
				i++;
				//break;
			}
			break;
		}
		else
		{
			possiblemove[i] = tmp;
			i++;
		}
		nc++;
	}

	nc = c;

	while(nc >= 0)
	{
		if(nc == c){nc--;}
		if(nc < 0){break;}
                tmp = grid.getcell(r, nc);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                                //break;
			}
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nc--;
	}
	
	while(nr < 8)
	{
		if(nr == r){nr++;}
		if(nr >= 8){break;}
                tmp = grid.getcell(nr, c);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                                //break;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nr++;
	}
	
	nr = r;
	
	while(nr >= 0)
        {
                if(nr == r){nr--;}
		if(nr < 0){break;}
                tmp = grid.getcell(nr, c);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                                //break;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nr--;
        }
}





