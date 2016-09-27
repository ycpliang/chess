#include <iostream>
#include <sstream>
#include "grid.h"
#include "cell.h"
//#include "grid.h"
//#include <iostream>
using namespace std;

void Grid::cleargame(){
	for(int i = 0; i < gridSize; i++){
		Cell *temp = theGrid[i];
		delete [] temp;
	}
	delete td;
	delete xw;
	delete [] theGrid;
}

void Grid::printResult(int whitewin, bool resign, bool end, int wscore, int bscore){
	if(end){
		string whitescore;
		string blackscore;
		stringstream ss;
		ss << wscore;
		ss >> whitescore;
		stringstream kk;
		kk << bscore;
		kk >> blackscore;
		xw->drawString(425, 25, "Final Score", Xwindow::Red);
		xw->drawString(425, 35, "White: ", Xwindow::Red);	
		xw->drawString(475, 35, whitescore, Xwindow::Red);
		xw->drawString(425, 45, "Black: ", Xwindow::Red);
		xw->drawString(475, 45, blackscore, Xwindow::Red);
		return;
	}
	if(!whitewin){
		//white resigns basically
		if(resign){
			xw->drawString(25, 25, "Black has no move", Xwindow::Red);
		}else{
			xw->drawString(25, 25, "White has no move", Xwindow::Red);
			
		}
		xw->drawString(25, 35, "Draw", Xwindow::Red);
		return;
	}
	if(resign){
		if(whitewin){
			xw->drawString(25, 25, "Black Resign", Xwindow::Red);
		}else {
			xw->drawString(25, 25, "White Resign", Xwindow::Red);	
		}
	}
	if(whitewin){
		xw->drawString(25, 35, "White wins", Xwindow::Red);
	}else{
		xw->drawString(25, 35, "Black wins", Xwindow::Red);
	}
	
}

Grid::~Grid(){
	cleargame();
}

void Grid::notify(int r, int c, int nr , int nc, char p){
	theGrid[r][c].notifyDisplay(*td ,nr, nc,p); 
	
}

Grid::Grid(){
	this->theGrid = 0;
	this->gridSize = 8;
	this->td = 0;
	this->xw = 0;
}

Cell * Grid::getcell(int r, int c){
 	Cell * temp = &theGrid[r][c];
	return temp;
}



void Grid::init()
{ 
/*	if(theGrid != NULL){
	//	cleargame();
	    TextDisplay *old = td; //free the old grid if exists
	    Cell **oldgrid = theGrid;
	    int oldsize = gridSize;
	  Xwindow *oldxw = xw;
	delete old; //delete the old grid if exists
   	for(int i=0;i<oldsize;i++){
        	delete [] oldgrid[i];
        
    	}
    	delete [] oldgrid;
 	delete oldxw;
//		Grid();
	cout << "asdfadfasfasdfsdf" << endl;
	}*/
	int windowSize = 500;
	if(theGrid != NULL){cleargame();} 
	xw = new Xwindow(windowSize,windowSize);
	td = new TextDisplay();
	theGrid = new Cell* [gridSize];
 
	for(int i=0; i<gridSize; i++)
 	{
  		theGrid[i] = new Cell[gridSize];
	}
 
	xw->drawString(160, 25 , "Chess Program of ycpliang");
	xw->drawString(25, 75, "8", Xwindow::Red);	
	xw->drawString(25, 125, "7", Xwindow::Red);
	xw->drawString(25, 175, "6", Xwindow::Red);	
	xw->drawString(25, 225, "5", Xwindow::Red);
	xw->drawString(25, 275, "4", Xwindow::Red);	
	xw->drawString(25, 325, "3", Xwindow::Red);
	xw->drawString(25, 375, "2", Xwindow::Red);	
	xw->drawString(25, 431, "1", Xwindow::Red); 
	xw->drawString(72, 475, "a", Xwindow::Red);
	xw->drawString(125, 475, "b", Xwindow::Red);
	xw->drawString(175, 475, "c", Xwindow::Red);
	xw->drawString(225, 475, "d", Xwindow::Red);
	xw->drawString(275, 475, "e", Xwindow::Red);
	xw->drawString(325, 475, "f", Xwindow::Red);
	xw->drawString(375, 475, "g", Xwindow::Red);
	xw->drawString(425, 475, "h", Xwindow::Red);


	for (int r=0;r<gridSize;r++)
	{
        	for(int c=0;c<gridSize;c++)
		{
            		theGrid[r][c] = Cell();
            		theGrid[r][c].setCoords(r,c, c* 50 + 50, r * 50 + 50, 50, 50, xw);
			if((r + c) % 2){
				xw->fillRectangle(r * 50 + 50, c * 50 + 50, 50, 50,Xwindow::Orange);
			}else {
				xw->fillRectangle(r * 50 + 50, c * 50 + 50, 50, 50, Xwindow::Brown);
			}  
        	}
 	}

}
ostream &operator<<(ostream &out, const Grid &g){
	out << *(g.td);
	return out;
}

bool Grid::isblocked(int r, int c, int nr, int nc) {
	return true;
}
