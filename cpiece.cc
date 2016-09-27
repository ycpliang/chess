#include <ctype.h>
#include "cpiece.h"
#include "cell.h"

Cpiece::Cpiece(char piecename, Cell * pos, int v): piecename(piecename),pos(pos), reverse(false),killedpiece(0), piecemoved(0), value(v){
	for(int i = 0; i < maxlegalmove; i++){
		possiblemove[i] = 0;
	}
} 

bool Cpiece::isKilled(){
	return killedpiece;
}

Cell * Cpiece::returnaMove(int a){
	return possiblemove[a];
}

void Cpiece::removePiece(){
	killedpiece = 1;
	pos->toggle();
//	pos = 0;
}
void Cpiece::reverseOn(){
	this->reverse = true;
}

bool Cpiece::makeMove(Cell * ncell){
	if(killedpiece){
		return false;
	}
	int i = 0;
	bool colour = pos->whitepiece();
//	std::cout << "the reverse is " << reverse << std::endl;
	while(possiblemove[i] != 0 || reverse){
		if(ncell == possiblemove[i] || reverse)
		{	
			if(colour){
				pos->erasepiece(toupper(piecename));
			}else{
				pos->erasepiece(piecename);
			}
			pos->toggle();
			pos = ncell;
			if(colour){
				pos->drawpiece(toupper(piecename));
			}else{
				pos->drawpiece(piecename);
			}
			if(!pos->isoccupied()){
				pos->toggle();
			}
			pos->changewpiece(colour);
			piecemoved += 1;
			if(reverse){
				reverse = false;
				piecemoved -= 1;
			}
			
			return true;
		//never exit
		}
		i++;
	} 
	return false;
}

void Cpiece::revive(bool wcpiece){
//	std::cout << "reviving " << piecename << std::endl;
	killedpiece = 0;
	pos->toggle();
	pos->changewpiece(wcpiece);
	if(wcpiece){
		pos->drawpiece(toupper(piecename));	
	}else{
		pos->drawpiece(piecename);	
	
	}
}

Cell * Cpiece::getPos(){
	return pos;
}

void Cpiece::clearMove(){
	for(int i = 0; i < maxlegalmove; i++){
		possiblemove[i] = 0;
	}
}

