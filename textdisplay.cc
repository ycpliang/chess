#include <iostream>
#include <string>
#include <ctype.h>
#include "textdisplay.h"
using namespace std;


string initpiece = "rnbqkbnr"; //the starting order 

TextDisplay::TextDisplay(): gridSize(8){
	theDisplay = new char*[gridSize];
	for(int i=0; i<gridSize; i++){
		char *displayr = new char[gridSize];
		for(int i2 = 0; i2 < gridSize; i2++){
			//the pawns rows of board
			if(i == 6){
				displayr[i2] = 'P'; 
			}else if(i == 1){
				displayr[i2] = 'p';
			}else if(i == 0){
				displayr[i2] = initpiece[i2];
			}else if(i == 7){
				displayr[i2] = toupper(initpiece[i2]); 
			}else if((i + i2)%2 == 0){
				displayr[i2] = '_';
			}else{
				displayr[i2] = ' ';
			}
		}
		theDisplay[i] = displayr;
	}
}

void TextDisplay::notify(int nr, int nc, int r, int c, char p, bool wpiece){
		if(wpiece){
			*(theDisplay[nr] + nc) = toupper(p);
		}else{
			*(theDisplay[nr] + nc) = p;
		}
		if((r + c)%2 == 0){
			*(theDisplay[r] + c) = '_';
		}else{
			*(theDisplay[r] + c) = ' ';
		}
}

TextDisplay::~TextDisplay(){
//	if(theDisplay){
	for(int i = 0; i < gridSize; i++){
		char * temp = theDisplay[i];
		delete [] temp;
	}
	delete [] theDisplay;
//	}
}

ostream &operator<<(ostream &out, const TextDisplay &td){
//cout << "hello12312" << endl;
//cout << "game " << td.theDisplay[0][0];
	for(int i = 0; i < td.gridSize; i++){
		out << td.gridSize - i << " ";
		for(int i2 = 0; i2 < td.gridSize; i2++){
		//cout << "number 2" << endl;
			out << td.theDisplay[i][i2];
		}
		out << endl;
	}
	out << endl << "  abcdefgh" << endl << endl;
	return out;
}

