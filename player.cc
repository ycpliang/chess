#include <iostream>
#include <string>
//#include <stdlib.h>
#include "player.h"
#include "cpiece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "grid.h"
#include "cell.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "score.h"
using namespace std;


int findCpiece(Player & white, Cell const * cell, bool wantkilled = false){
	Cpiece * temp;
	bool alive = true;
	for(int i = 0; i < maxpieces; i++){
		alive = true;
		temp = white.getpiece(i);
		if(temp->isKilled()){
			alive = false;
		}
		if(temp == 0){//safeguard (not needed if array is organized
		}else if(temp->getPos() == cell && (alive || wantkilled)){
			return i;
		}		 
	}
	return -1;
}

Player::Player(): ai(0), wpiece(0), wmove(0), levelai(0), ischecked(0), npieces(0){
	for(int i = 0; i < maxpieces; i++){
		pieces[i] = 0;
	}
}

Cpiece * Player::getpiece(int i){
	return pieces[i];
}

/*bool Player::canKill(Cell * temp){


}*/

bool Player::isStalemate(Player & other , Grid & gameOn){
	bool stalemate = true;
	for(int i = 0; i < maxpieces; i++){
		if(!pieces[i]->isKilled()){
			if(pieces[i]->returnaMove(0) != 0){
				if(i == 4){
					bool kingMoves = false;
					for(int i2 = 0; i2 < maxlegalmove; i2++){
						bool tempPos;
						Cell * origin = pieces[4]->getPos();
						Cell * temp = pieces[4]->returnaMove(i2);
					//	cout << "the r is " << temp->getR() << " C is " << temp->getC() << endl;
						if(temp != 0){
							int k =	killCheck(other,temp);
							makeMove(4,temp);
						//	addpossiblemove(gameOn);
							other.addpossiblemove(gameOn);
							tempPos = other.isChecked(temp);
							pieces[4]->reverseOn();
							makeMove(4,origin);
							if(k != -1){
								Cpiece * temp2 = other.getpiece(k);
								if(wpiece){
									temp2->revive(false);
									other.npieces++;
								}else{
									temp2->revive(true);
									other.npieces++;
								}
							}
					//		cout << " the boolean is " << tempPos << endl;
							if(!tempPos){
								kingMoves = true;
							//	cout << "breaking" << endl;
								break;	
							}
							if(pieces[4]->returnaMove(i2+1) == 0){
							//	cout << "breaking" << endl;
								break;
							}	
						}else{
						//	cout << "breaking" << endl;
							break;
						}
					}
					if(kingMoves){
						stalemate = false;
						break;
					}
				}else{
					stalemate = false;
					break;
				}
			}
		}
	}
	return stalemate;
}

bool Player::aiMoves(Grid & grid, Player & other, Score & score){
	srand(time(NULL));
	//bool success = false;
	bool wmove;
	if(levelai == 1){
	//	std::cout << "PPL AI" << std::endl;
		wmove = aiLevel1(grid, other, score);
	}else if(levelai == 2){
		wmove = aiLevel2(grid, other, score);
	}else if(levelai == 3){
		wmove = aiLevel2(grid, other, score);
	}
	return wmove;
}


int Player::killCheck(Player & other, Cell * aiNewPos){
//	Cpiece * temp2;
	int kill = findCpiece(other,aiNewPos);
	if(kill != -1){
		if(wpiece){
			cout << "KILLED BLACK PIECE" << endl;
		}else{
			cout << "KILLED WHITE PIECE" << endl;
		}
	//	temp2 = other.getpiece(kill);	
		other.killPiece(kill);
	}
	return kill;
}

bool Player::getwmove(){
	return wmove;
}
bool Player::aiCheck(Grid & gameOn, Player & black, int piece2move, Cell * cell, Cpiece * temp2, Score & score){
	if(wpiece){
		wmove = true;
	}else{
		wmove = false;
	}
	Cpiece * temp = pieces[piece2move];
	bool started = true;
	Cell * ncell = temp->getPos();
	int r = cell->getR();
	int c = cell->getC();
	int nr = ncell->getR();
	int nc = ncell->getC();
	char name =temp->getName();
	bool reverse = false;
	if(!(name == 'k' && c == 4 && (nc == 2 || nc == 6))){
		addpossiblemove(gameOn);
		black.addpossiblemove(gameOn);
	}
	if(black.isChecked(pieces[4]->getPos())){
		//ai make sure to remove
		cout << "INVALID MOVE BEING CHECKED" << endl;
		temp->reverseOn();
//		cout << "the reverse of : " << findCpiece(*this,ncell) << endl;
//		cout << "to : R" << cell->getR() << " C: " << cell->getC() << endl;
		makeMove(findCpiece(*this,ncell),cell);
		reverse = true;
		if(temp2 != 0){
			if(wpiece){
				temp2->revive(false);
				black.npieces++;
			}else{
				temp2->revive(true);
				black.npieces++;
			}
		}
		wmove = !wmove;
		addpossiblemove(gameOn);
		black.addpossiblemove(gameOn);
		//add here and make sure to refresh moves
	}else if(name == 'k' && c == 4 && (nc == 2 || nc == 6)){
		if(wpiece){	
		if(nc == 2){
			Cell * castr1 = gameOn.getcell(7,0);
			Cell * castTo = gameOn.getcell(7,3);
			makeMove(findCpiece(*this,castr1),castTo);
			gameOn.notify(7,0, 7, 3, 'r');
		}else if(nc == 6){
			Cell * castr1 = gameOn.getcell(7,7);
			Cell * castTo = gameOn.getcell(7,5);
			makeMove(findCpiece(*this,castr1),castTo);
			gameOn.notify(7,7, 7,5, 'r');
		}
		}else{
		if(nc == 2){
			Cell * castr1 = gameOn.getcell(0,0);
			Cell * castTo = gameOn.getcell(0,3);
			makeMove(findCpiece(black,castr1),castTo);
			gameOn.notify(0,0, 0, 3, 'r');
		}else if(nc == 6){
			Cell * castr1 = gameOn.getcell(0,7);
			Cell * castTo = gameOn.getcell(0,5);
			makeMove(findCpiece(black,castr1),castTo);
			gameOn.notify(0,7, 0, 5, 'r');
		}
		}
		addpossiblemove(gameOn);
		black.addpossiblemove(gameOn);
	}

	if(temp->getName() == 'p'){
		if(wpiece){
			if(nr == 0){
				char promoteU = 'Q';
				cout << "PROMOTE TO " << promoteU << " "<< endl;
				cout << piece2move << endl;
				promote(piece2move, ncell, tolower(promoteU));
				addpossiblemove(gameOn);
				black.addpossiblemove(gameOn);
			}
		}else{
			if(nr == 7){
				char promoteU = 'Q';
				cout << "PROMOTE TO " << promoteU << " "<< endl;
				cout << piece2move << endl;
				promote(piece2move, ncell, tolower(promoteU));
				addpossiblemove(gameOn);
				black.addpossiblemove(gameOn);
			}

		}
	}
	Cpiece * bKing = black.getpiece(4);
	//	cout << "IS CHECKING OTHER PLAYER" << isChecked(bKing->getPos()) <<endl;
		if(isChecked(bKing->getPos())){
			cout << "CHECKED" << endl;
		if(isCheckmate(bKing)){ //white checks black
	//		cout << "IS GAME FOR OTHER PLAYER" << endl;
		if(temp->getName() == 'n' || !black.canBlock(ncell)) {
		if(!black.isChecked(ncell)){
			if(wpiece){
			cout << "__________" << endl;
			cout << "White wins" << endl;		
			cout << "----------" << endl;
			score.addWhite();
			gameOn.printResult(1, false, false, score.whiteScore(), score.blackScore());
			}else{
			cout << "__________" << endl;
			cout << "Black wins" << endl;
			cout << "----------" << endl;	
			score.addBlack();
			gameOn.printResult(2, false, false, score.whiteScore(), score.blackScore());
			}	
			wmove = true;
			started = false;
			//break;
		}
		}		
		}
		}

		if(black.isStalemate(*this, gameOn)){
			if(wpiece){
				cout << "BLACK CAN NOT MOVE" << endl;
			}else{
				cout << "WHITE CAN NOT MOVE" << endl;
			}
			cout << "STALEMATE" << endl;
			score.addWhite();
			score.addBlack();
			wmove = true;
			if(wpiece){
				gameOn.printResult(0, true, false, score.whiteScore(), score.blackScore());
			}else{
				gameOn.printResult(0, false, false, score.whiteScore(), score.blackScore());
			}	
			started = false;
		}
//		cout << "the reverse is " <<  reverse << endl;
		if(!reverse){
			gameOn.notify(r,c, nr, nc, temp->getName());
		}
	if(reverse){
		if(levelai == 1){
			aiLevel1(gameOn, black, score);
		}	
	}
		wmove = !wmove;		
				
	return started; //which tells you whether a new game is needed		
}

bool Player::aiLevel3(Grid & grid, Player & other, Score & score)
{	
//	cout << "ai LEVEL 3 in " << endl;
	Cell * aMove;
	int piece2move = rand() % 16;
	int possiblemove1 = rand() % 27;
	Cell * start;
	do{
	piece2move = rand() % 16;
	while(pieces[piece2move]->isKilled() || pieces[piece2move]->returnaMove(0) == 0){
		piece2move = rand() % 16;
	}
	start = pieces[piece2move]->getPos();
//	std::cout << pieces[piece2move]->getName() << std::endl;
	//int r = start->getR();
	//int c = start->getC();
	possiblemove1 = rand() % 27;
	while((aMove = pieces[piece2move]->returnaMove(possiblemove1)) == 0){
		possiblemove1 = rand() % 27;
	}
	}while(other.isChecked(aMove));
	
	bool k = false;
	//int nr = aMove->getR();
	//int nc = aMove->getC();
//	cout << "THE POSSIBLE AI 1 MOVE IS " << possiblemove1 << endl;
//	bool success;
	int kill = killCheck(other,aMove); 
//	int success;
	 makeMove(piece2move,aMove);
	Cpiece * temp2 = 0; 
	if(kill != -1){
		temp2 = other.getpiece(kill);
	}
//	if(success){
		k = aiCheck(grid, other, piece2move, start, temp2, score);
//	}
//	grid.notify(r, c, nr,nc, pieces[piece2move]->getName());
	return k;
}
bool Player::aiLevel2(Grid & grid, Player & p, Score & s)
{
	Cpiece * tmpp; // temp piece
	Cpiece * movep; // the piece which will be moved
	Cpiece * opp;  // opponent piece
	Cell * aMove; // the destination
	Cell * tmpc; // temp cell
	int pval = 0;  // piece value
	int tmpval; // temp value
	int position; // piece index position inside the piece array in player object
	int piece2move; // piece index position for movep
	int prep2m = -1;
	bool killedaPiece = false;
	Cell * currentpos; // current position(cell) of a piece
	
	if(p.isChecked(pieces[4]->getPos())){
//		cout << "calling ai level 1" << endl;
		return aiLevel1(grid,p,s);

	}else{

	for(int i=0; i<16; i++)  //prefers check
	{
		if(pieces[i]->isKilled() == false)
		{
			tmpp = pieces[i];
			currentpos = tmpp->getPos();
			for(int j=0; j<27; j++)
			{
				int preval = pval;  //  backup
				Cell * preaMove = aMove;  // backup
				Cpiece * premovep = movep;  //  backup
				//cout << "22222222222222" << endl;
				tmpc = tmpp->returnaMove(j);
			
			//	cout << "i is now: " << i << " " << "j is now: " << j << endl;
				if(tmpc == NULL){break;}
				else
				{
					//cout << "313123213" << endl;
				//	cout << "tmpc is occupied? " << tmpc->isoccupied() << endl;
					
					if(tmpc->isoccupied() == true)
					{
					//	cout << "is occupied !!!" << endl;
						
						position = findCpiece(p, tmpc);
					//	cout << "position is : " << position << endl;
						opp = p.getpiece(position);
					//	cout << "name : " << opp->getName() << endl;
						tmpval = opp->value;	
						//cout << "33333333333" << endl;
					//	cout << "opp value : " <<tmpval<<" "<< "pval : " <<pval << endl;
						if(tmpval > pval)
						{
							preval = pval; // backup
							pval = tmpval;
							preaMove = aMove;  // backup
							aMove = tmpc;
							premovep = movep; // backup
							movep = tmpp;
							prep2m = piece2move;
							if(prep2m == -1){prep2m = i;}
							else{prep2m = piece2move;}
							piece2move = i;
						//	cout << "changed a move !!!1111111" << endl;
						}						
						killCheck(*this, tmpc);
						killCheck(p,tmpc);
						killedaPiece = true;
					//	cout << "after a kill" << endl;
					//	cout << "44444444444444" << endl;
					}
					{
						tmpval = 0;
					}
					
					//cout << "i : " << i  << endl;
					makeMove(i,tmpc); 
					addpossiblemove(grid);  //make the move and check if it checks the other player's king
					p.addpossiblemove(grid);  //
					
					//cout << "middle !!" << endl;
					
					if(p.isChecked(pieces[4]->getPos()) == false)  //if the above move is valid, test if there exist any check move
					{
						for(int k=0; k<27; k++) //
						{
							Cell * tmpcell = tmpp->returnaMove(k);

							if(tmpcell == NULL){break;}
							else
							{
								if(tmpcell->isoccupied() == true)
								{
								//	cout << "look for check - start-" << endl;
									position = findCpiece(p, tmpcell);  // king -> position 5
									Cpiece * oppiece = p.getpiece(position);
									int tmpvalue = oppiece->value;
								//	cout << "look for check - mid" << endl;						
									if(tmpvalue + tmpval > pval && position == 4)  // when checks a king
									{
										pval = tmpvalue + tmpval;
										aMove = tmpc;
										movep = tmpp;
										piece2move = i;
									//	cout << "changed move !!! 2222222" << endl;
									}
								//	cout << "look for check - end" << endl;
								}
							}
						}
					}
					else
					{
						pval = preval; // invalid move, change all the variable to backup (since we already updated the variable)
						aMove = preaMove; // change back
						movep = premovep; // change back, avoid invalid move
						piece2move = prep2m;
					}
					
					/*
					if(p.isChecked(pieces[4]->getPos()) == false)
					{
						if()
					}*/
					//--------------------------------------------------------------------
					// for ai level 3, add a loop here to check if tmpc is a valid move for an opponent piece or not
					//
					/*
					for(int m=0; m<16; m++)
					{
						Cpiece * opponentP = p.pieces[m]; // test each opponent's piece
						for(int n=0; n<27; n++)
						{
							if(tmpc == NULL){break;}
							else
							{
								Cell * opponentMove = opponentP->returnaMove(m);
								if(opponentMove == tmpc) // invalide move due to might get killed
								{
									pval = preval; // change all the variable to backup (since we already updated the variable)
									aMove = preaMove; // change back
									movep = premovep; // change back, avoid invalid move
								}
								//cout << "test test test" << endl;
							}
						}
					}
					*/
					//----------------------------------------------------------------------
					
					pieces[i]->reverseOn();
					makeMove(i, currentpos);
					if(killedaPiece == true)
					{
						opp->revive(!wpiece); //revive the killed opponent's piece
						killedaPiece = false;
				//		cout << "revived a piece " << endl;
					}
					//pieces[i]->reverseOn();	
					//makeMove(i, currentpos); //move the piece back to its original position
					//cout << "666666666666" << endl;
					
					addpossiblemove(grid);
					p.addpossiblemove(grid);

				}
			}
		}
	}
	if(movep != NULL && aMove != NULL && pval > 0) //make the move if it captures or checks
	{
	//	cout << "AI level 2 made the move !!!" << endl;
	//	if(pval < 20)
	//	{
			killCheck(p,aMove);
			killCheck(*this, aMove);
		//	cout << "AI killed a piece" << endl;
	//	}
		int r = pieces[piece2move]->getPos()->getR();
		int c = pieces[piece2move]->getPos()->getC();
		int nr = aMove->getR();
		int nc = aMove->getC();
		
		pieces[piece2move]->reverseOn();
		makeMove(piece2move,aMove);
//		cout << "true and false " << tf << endl;
		grid.notify(r, c, nr, nc, pieces[piece2move]->getName());
//		cout << "AI moved the piece in array index: " << piece2move << endl;
		//
		//*******************<<<<<<add checkmate here>>>>>>********************
		//
		return true;
	}
	else{
		if(levelai == 2){
			return aiLevel1(grid, p, s);
		}else{
			return aiLevel3(grid, p ,s);
		}
	}
	}
	//return false;
}

bool Player::aiLevel1(Grid & grid, Player & other, Score & score){
	int piece2move = rand() % 16;
	while(pieces[piece2move]->isKilled() || pieces[piece2move]->returnaMove(0) == 0){
		piece2move = rand() % 16;
	}
	Cell * start = pieces[piece2move]->getPos();
	std::cout << pieces[piece2move]->getName() << std::endl;
	//int r = start->getR();
	//int c = start->getC();
	int possiblemove1 = rand() % 27;
	Cell * aMove;
	while((aMove = pieces[piece2move]->returnaMove(possiblemove1)) == 0){
		possiblemove1 = rand() % 27;
	}
	bool k = false;
	//int nr = aMove->getR();
	//int nc = aMove->getC();
//	cout << "THE POSSIBLE AI 1 MOVE IS " << possiblemove1 << endl;
//	bool success;
	int kill = killCheck(other,aMove); 
//	bool success = makeMove(piece2move,aMove);
	makeMove(piece2move, aMove);
	Cpiece * temp2 = 0; 
	if(kill != -1){
		temp2 = other.getpiece(kill);
	}
//	if(success){
		k = aiCheck(grid, other, piece2move, start, temp2, score);
//	}
//	grid.notify(r, c, nr,nc, pieces[piece2move]->getName());
	return k;
}



void Player::promote(int whichpiece, Cell * pos, char p){
	delete pieces[whichpiece];
	
	char k = 'p';
	if(wpiece){
		k = toupper(k);
		p = toupper(p);
	}
	pos->erasepiece(k);
	//pos->erasepiece(toupper(k));
//	std::cout << "sdfadsfasdfasdfasdfasdfasdfa" << std::endl;
	if(tolower(p) == 'p'){
		pieces[whichpiece] = new Pawn(pos);
	//	pieces[whichpiece]->addpossibleMove();
	}else if(tolower(p) == 'r'){
		pieces[whichpiece] = new Rook(pos);
	}else if(tolower(p) == 'n'){
		pieces[whichpiece] = new Knight(pos);
	}else if(tolower(p) == 'b'){
		pieces[whichpiece] = new Bishop(pos);
	}else if(tolower(p) == 'q'){
		pieces[whichpiece] = new Queen(pos);
	}else{
		std::cout << "invalid promote piece" << std::endl;
	}
	pos->drawpiece(p);

}

void Player::initPlayer(bool ai, bool wpiece)
{             
	this->ai = ai;
	this->wpiece = wpiece;
}

bool Player::canBlock(Cell * ncell){
	Cell * king = pieces[4]->getPos();
	int cr = ncell->getR();
	int cc = ncell->getC();
	int r = king->getR();
	int c = king->getC();
//	std::cout << cr << " " << cc <<  std::endl;
//	std::cout << r << "fasdfas " << c <<  std::endl;
	while( r != cr || c != cc){
//	std::cout << r << "fasdfas " << c <<  std::endl;
	
	if(r > cr){
		r--;
	}else if(r < cr){
		r++;
	}
	if(c > cc){
		c--;
	}else if(c < cc){
		c++;
	}
//	std::cout << r << "fasdfas " << c <<  std::endl;
	if(r < 0 || r > 7 || c < 0 || c > 7){
		break;
	} 
	for(int i = 0; i < maxpieces; i++){
		if(pieces[i]->isKilled() == 0 && i != 4){
			for(int i2 = 0; i2 < maxlegalmove; i2++){
				//std::cout << " asdfasdf " << i << std::endl;
				Cell *temp = pieces[i]->returnaMove(i2);
				if(temp != 0){
			 	if(temp->checkcell(r,c)){
					return true;
				}
				}	
			}
		}
	}
	}
	return false;
}

void Player::initPlayer(bool ai, bool wpiece, int level)
{
	this->ai = ai;
	this->wpiece = wpiece;
	this->levelai = level;
}

void Player::initPieces(Grid & g)
{
	if(pieces != NULL){
		clearPieces();
	}
	Cell * tmp;
	int r;
	if(wpiece == true){r = 7;}
	else{r = 0;}
		
	for(int i=0; i<maxpieces; i++)
	{
		if(i==0 || i == 7) // Rock
		{
			tmp = g.getcell(r, i);
//			if(r == 0) { std::cout << " r " << r << "c " << c << " o: " <<tmp->isoccupied() << std::endl;}
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('R');
			}else{
				tmp->drawpiece('r');
			}
			pieces[i] = new Rook(tmp);
		}
		else if(i==1 || i==6) // knight
		{
			tmp = g.getcell(r, i);
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('N');
			}else{
				tmp->drawpiece('n');
			}
			pieces[i] = new Knight(tmp);
		}
		else if(i==2 || i==5) // bishop
		{
			tmp = g.getcell(r, i);
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('B');
			}else{
				tmp->drawpiece('b');
			}
			pieces[i] = new Bishop(tmp); 
		}
		else if(i==3) // Queen
		{
			tmp = g.getcell(r, i);
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('Q');
			}else{
				tmp->drawpiece('q');
			}
			pieces[i] = new Queen(tmp);
		}
		else if(i==4) // King
		{
			tmp = g.getcell(r, i);
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('K');
			}else{
				tmp->drawpiece('k');
			}
			pieces[i] = new King(tmp);
		}
		else // Pawn
		{
			if(wpiece == true){r = 6;}
			else{ r = 1;}
			tmp = g.getcell(r, (i - maxpieces/2));
			tmp->toggle();
			tmp->changewpiece(wpiece);
			if(wpiece){
				tmp->drawpiece('P');
			}else{
				tmp->drawpiece('p');
			}
			pieces[i] = new Pawn(tmp);
		}
	}
	npieces = 16;
}

bool Player::makeMove(int whichpiece, Cell * cell)
{
	bool tmp;
	
	tmp = pieces[whichpiece]->makeMove(cell);
	//std::cout << "I made here " << std::endl;	
	return tmp;
}

bool Player::isChecked(Cell * kingother){
	for(int i = 0; i < maxpieces; i++){
		if(pieces[i]->isKilled() == 0){
			for(int i2=0; i2 < maxlegalmove; i2++){
				Cell * temp = pieces[i]->returnaMove(i2);
				if(temp == 0){
					break;
				}else if(temp == kingother){
					return true;
				} 
			} 			
			
		}
	}
	return false;
}

bool Player::isCheckmate(Cpiece * kingother)
{
/*	if(checkmate){	
	return checkmate;
	}*/
	bool alive = true;
	for(int i = 0; i < maxlegalmove; i++){//king possiblemove
		Cell * temp = kingother->returnaMove(i);
		if(temp == 0){
			return true;
		}
		for(int i2 = 0; i2 < maxpieces; i2++){//the element of piece
			if(pieces[i2] == 0){break;}
			if(pieces[i2]->isKilled() == 0){
			for(int i3 = 0; i3 < maxpieces; i3++){ // pieces possiblemove
				Cell * hasloc = pieces[i2]->returnaMove(i3);
				if(hasloc == temp){
					alive = false;
					break;
				}
			}
			}
		}
		if(alive){
			return false;
		}else{
			alive = true;
		}	
	}
	return true;
}

void Player::clearPieces(){
	for(int i = 0; i < maxpieces; i++){
		if(pieces[i] != NULL){
			delete pieces[i];
		}
	}

}

Player::~Player(){
	clearPieces();
//	delete [] pieces;
}

void Player::killPiece(int whichpiece){ //kill the piece
	pieces[whichpiece]->removePiece();
	char p;
	if(wpiece){
		p = toupper(pieces[whichpiece]->getName());
	}else{	
		p = pieces[whichpiece]->getName();
	}
	(pieces[whichpiece]->getPos())->erasepiece(p);
	npieces -= 1; //kill and then revive cause one less piece
	
}
void Player::addpossiblemove(Grid & h){
	int i = 0;
	while(i < maxpieces){
		if(pieces[i] != NULL){
		//	std::cout << "ith piece" << i << std::endl;
			pieces[i]->addPossibleMove(h);
		}
		i++;
	}

}
