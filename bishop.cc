#include <iostream>
#include "bishop.h"


Bishop::Bishop(Cell * pos): Cpiece('b', pos, 6){}

char Bishop::getName(){return piecename;}

void Bishop::addPossibleMove(Grid & grid){
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

	while(nr < 8 && nc < 8)
        {
                if(nc == c && nr == r)
		{
			nr++;
			nc++;
		}
                if(nc >= 8 || nr >= 8){break;}
                tmp = grid.getcell(nr, nc);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
		nr++;
                nc++;
        }

	nr = r;
	nc = c;

	
	while(nr >= 0 && nc >= 0)
        {
                if(nc == c && nr == r)
                {
                        nr--;
                        nc--;
                }
                if(nc < 0 ||  nr < 0){break;}
                tmp = grid.getcell(nr, nc);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nr--;
                nc--;
        }
	
	nr = r;
	nc = c;

	while(nr < 8 && nc >= 0)
        {
                if(nc == c && nr == r)
		{
			nr++;
			nc--;
                }
                if(nc < 0 ||  nr >= 8){break;}
                tmp = grid.getcell(nr, nc);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nr++;
                nc--;
        }

	nr = r;
	nc = c;

	 while(nr >= 0 && nc < 8)
        {
                if(nc == c && nr == r)
                {
                        nr--;
                        nc++;
                }
                if(nc >= 8 ||  nr < 0){break;}
                tmp = grid.getcell(nr, nc);
                if(tmp->isoccupied())
                {
                        if(colour != tmp->whitepiece())
                        {
                                possiblemove[i] = tmp;
                                i++;
                        }
			break;
                }
                else
                {
                        possiblemove[i] = tmp;
                        i++;
                }
                nr--;
                nc++;
        }

}
