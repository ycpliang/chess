#include <ctype.h>
#include <cstring>
#include <sstream>
#include "grid.h"
#include "score.h"
#include "player.h"
#include "cpiece.h"
#include "pawn.h"
using namespace std;

//helper function because find piece is used multiple times
int findpiece(Player & white, Cell const * cell, bool wantkilled = false){
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


int main(){
	string x;
	Grid gameOn;
	int level;
	Player white;
	bool started = true;
	bool wmove = true; // white's move if true, black move if false
	bool wai = false;
	bool begin = false;
	Player black;
	Score total = Score();
	bool bai = false;
	while(cin >> x){
		if( x == "game"){
			begin = true;
			started = false;
			gameOn.init();
			cout << "GAME START" << endl;
			cin >> x;
			if(x == "human"){
				white.initPlayer(false,true);
				white.initPieces(gameOn);
		//		cout << " HEDFSFAD" << endl;
			}else{
				cin >> level;
				white.initPlayer(true ,true , level);
				white.initPieces(gameOn);
				wai = true;
			}
			cin >> x;
			if(x == "human"){
				black.initPlayer(false, false);	
				black.initPieces(gameOn);
				white.addpossiblemove(gameOn);
				black.addpossiblemove(gameOn);
			}else{
				cin >> level;
				black.initPlayer(true, false , level);
				black.initPieces(gameOn);
				white.addpossiblemove(gameOn);
				black.addpossiblemove(gameOn);
				bai = true;
			}
			cout << gameOn;		
		}else if(x == "move" && begin == false){
			cerr << "unable to move without a new game " << endl;
		}else if(x == "move"){
			started = true;
			string pos;//position
			bool success = true;
			int r; // current row
			int c; // current column
			Cpiece * temp; //the piece being moved
			Cpiece * temp2;
			Cell * cell;
			Cell * ncell;
			int nr; //new row
			int nc; // new column
			char a; 
			if((wmove && !wai) || (!wmove && !bai)){
			cin >> pos;
			cout << "MOVE " << pos;
			istringstream ss(pos.substr(1,1));
			ss >> r;
			r = 8  - r;
			istringstream bb(pos.substr(0,1));
			bb >> a;			
			c = a - 97;
			cin >> pos;
			cout << " TO " << pos << endl;
			istringstream kk(pos.substr(1,1));
			kk >> nr;
			nr = 8 - nr;
			istringstream cc(pos.substr(0,1));
			cc >> a;			
			nc = a - 97;
			cell = gameOn.getcell(r,c);
			ncell = gameOn.getcell(nr,nc);
			}
			int loc;
			bool endgame;
//			cout << "cell occu" << cell->isoccupied() << " " << !cell->whitepiece() << " " << findpiece(black, cell)  << endl;
			if(wmove && wai){
				cout << "WHITE AI MOVE " << endl;
				endgame = white.aiMoves(gameOn, black, total);
				begin = endgame;
				if(begin){
					wmove = white.getwmove();
					white.addpossiblemove(gameOn);
					black.addpossiblemove(gameOn);
				}else{
					started = false;
					wmove = true;
				}
				cout << gameOn;
			}else if(!wmove && bai){
				cout << "BLACK AI MOVE " << endl;
				endgame = black.aiMoves(gameOn, white, total);
				begin = endgame;
				if(begin){
					wmove = black.getwmove();
					white.addpossiblemove(gameOn);
					black.addpossiblemove(gameOn);
				}else{
					started = false;
					wmove = true;
				}
				cout << gameOn;
			}else if(wmove && cell->isoccupied() && cell->whitepiece() && (loc = findpiece(white,cell)) != -1){
				white.addpossiblemove(gameOn);
				black.addpossiblemove(gameOn);
				temp = white.getpiece(loc);
				char name = temp->getName();
				cout << "white moves ";
				cout << name << endl;
				cout << endl;
				int kill = findpiece(black,ncell);
				if(kill != -1){
					cout << "KILLED BLACK PIECE" << endl;
					temp2 = black.getpiece(kill);	
					black.killPiece(kill);
				}
				success = white.makeMove(loc, ncell);
				if(!success && kill != -1){
			//		cout << "is it successful " << success << endl;
					temp2->revive(false);
					black.npieces++;
				}
				if(success){
					bool reverse = false;
					if(!(name == 'k' && c == 4 && (nc == 2 || nc == 6))){
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}
					if(black.isChecked(white.getpiece(4)->getPos())){
						cout << "INVALID MOVE BEING CHECKED" << endl;
							temp->reverseOn();
							reverse = white.makeMove(findpiece(white,ncell),cell);
						if(kill != -1){
							temp2->revive(false);
							black.npieces++;
						}
						wmove = !wmove;
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}else if(name == 'k' && c == 4 && (nc == 2 || nc == 6)){
						if(nc == 2){
							Cell * castr1 = gameOn.getcell(7,0);
							Cell * castTo = gameOn.getcell(7,3);
						        white.makeMove(findpiece(white,castr1),castTo);
							gameOn.notify(7,0, 7, 3, 'r');
						}else if(nc == 6){
							Cell * castr1 = gameOn.getcell(7,7);
							Cell * castTo = gameOn.getcell(7,5);
							white.makeMove(findpiece(white,castr1),castTo);
							gameOn.notify(7,7, 7,5, 'r');
						}
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}

					if(temp->getName() == 'p'){
						if(nr == 0){
							char promoteU;
							cin >> promoteU;
							cout << "PROMOTE TO " << promoteU << endl;
							white.promote(loc, ncell, tolower(promoteU));
							white.addpossiblemove(gameOn);
							black.addpossiblemove(gameOn);
						}
					}
					
					Cpiece * bKing = black.getpiece(4);
					if(white.isChecked(bKing->getPos())){
						cout << "CHECKED" << endl;
					if(white.isCheckmate(bKing)){ //white checks black
					if(temp->getName() == 'n' || !black.canBlock(ncell)) {
					if(!black.isChecked(ncell)){
						cout << "__________" << endl;
						cout << "White wins" << endl;		
						cout << "----------" << endl;
						total.addWhite();
						wmove = true;
						gameOn.printResult(1, false, false, total.whiteScore(), total.blackScore());
						started = false;
						begin = false;
						//break;
					}
					}	
					}
					}
					if(!reverse){
						gameOn.notify(r,c, nr, nc, temp->getName());
					}
					wmove = !wmove;
				}else{
					cout << "invalid move 1" << endl;
				}
		//		cout << "white stalemates black" << black.isStalemate(white,gameOn) << endl;	
				if(black.isStalemate(white, gameOn)){
					cout << "BLACK CAN NOT MOVE" << endl;
					cout << "STALEMATE" << endl;
					total.addWhite();
					total.addBlack();
					wmove = true;
					gameOn.printResult(0, true, false, total.whiteScore(), total.blackScore());	
					started = false;
					begin = false;
				}
	
				cout << gameOn;
			//same thing when black makes move	
			}else if(!wmove && cell->isoccupied() && !cell->whitepiece() && (loc = findpiece(black,cell)) != -1){
				temp = black.getpiece(loc);
				char name = temp->getName();
				cout << "black moves ";
				cout << name << endl;
				cout << endl;
				int kill = findpiece(white,ncell);
				if(kill != -1){
					temp2 = white.getpiece(kill);	
					white.killPiece(kill);
				}
				success = black.makeMove(loc, ncell);
			//	cout << "is it successful " << success << endl;
				if(!success && kill != -1){
					temp2->revive(true);
					white.npieces++;
				}
				if(success){
					bool reverse = false;
					if(!(name == 'k' && c == 4 && (nc == 2 || nc == 6))){
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}
					if(white.isChecked(black.getpiece(4)->getPos())){
						cout << "INVALID MOVE BEING CHECKED" << endl;
						temp->reverseOn();
						reverse = black.makeMove(findpiece(black,ncell),cell);
						if(kill != -1){
							temp2->revive(true);
							white.npieces++;
						}
						wmove = !wmove;
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}else if(name == 'k' && c == 4 && (nc == 2 || nc == 6)){
						if(nc == 2){
							Cell * castr1 = gameOn.getcell(0,0);
							Cell * castTo = gameOn.getcell(0,3);
							black.makeMove(findpiece(black,castr1),castTo);
							gameOn.notify(0,0, 0, 3, 'r');
						}else if(nc == 6){
							Cell * castr1 = gameOn.getcell(0,7);
							Cell * castTo = gameOn.getcell(0,5);
							black.makeMove(findpiece(black,castr1),castTo);
							gameOn.notify(0,7, 0, 5, 'r');
						}
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
					}


					
					if(temp->getName() == 'p'){
						if(nr == 7){
							char promoteU;
							cin >> promoteU;
							black.promote(loc, ncell, tolower(promoteU));
							white.addpossiblemove(gameOn);
							black.addpossiblemove(gameOn);
						}
					}
					Cpiece * wKing = white.getpiece(4);
					if(black.isChecked(wKing->getPos())){
						cout << "CHECKED" << endl;
					if(black.isCheckmate(wKing)){ //white checks black
					if(temp->getName() == 'n' || !white.canBlock(ncell)){
					if(!white.isChecked(ncell)){
						// check for save
						cout << "__________" << endl;
						cout << "Black wins" << endl;
						cout << "----------" << endl;	
						total.addBlack();
						wmove = true;
						gameOn.printResult(2, false, false, total.whiteScore(), total.blackScore());
						started = false;
						begin = false;
						//break;
					}
					}
					}
					}
					if(!reverse){
					gameOn.notify(r,c, nr, nc, temp->getName());
					}
					wmove = !wmove;
				}else{
					cout << "invalid move 2" << endl;
				}

		//		cout << "black stalemates white" << white.isStalemate(black, gameOn) << endl;	
				if(white.isStalemate(black, gameOn)){
					cout << "WHITE CAN NOT MOVE" << endl;
					cout << "STALEMATE" << endl;
					total.addWhite();
					total.addBlack();
					wmove = true;
					gameOn.printResult(0, false, false, total.whiteScore(), total.blackScore());	
					started = false;
					begin = false;
				}

				cout << gameOn;
			}else{
				cerr << "invalid move 3" << endl;
			}
		}else if(x == "resign"){
			if(wmove){
				cout << "_____________" << endl;
				cout << "White RESIGNS" << endl;
				cout << "_____________" << endl;
				cout << "__________" << endl;
				cout << "Black wins" << endl;
				cout << "----------" << endl;
				total.addBlack();
				wmove = true;
				gameOn.printResult(2, true, false, total.whiteScore(), total.blackScore());	
				started = false;
				begin = false;
				//break
			}else{
				cout << "_____________" << endl;
				cout << "Black RESIGNS" << endl;
				cout << "_____________" << endl;
				cout << "__________" << endl;
				cout << "White wins" << endl;
				cout << "----------" << endl;
				total.addWhite();
				wmove = true;
				gameOn.printResult(1, true, false, total.whiteScore(), total.blackScore());	
				started = false;
				begin = false;
				//break;
			}

		}else if(x == "setup"){
			if(!started){
			cout << "you entered setup mode. Enter command '+' '-' '='" << endl;
			cout << "sample input '+ K e1' '- e1' '= colour', and 'done' to end" << endl;
			string piecename;
			string pos;
			char piecetype;
			int nr;
			int nc;
			char c;
			Cpiece * temp;
			int counter = 0;
			bool wpiece;
			while(cin >> x){
				counter = 0;
				if(x == "+"){
					cin >> piecename;
					istringstream aa(piecename);
					aa >> piecetype;
					cin >> pos;
					istringstream ss(pos.substr(1,1));
					ss >> nr;
					nr = 8  - nr;
					istringstream bb(pos.substr(0,1));
					bb >> c;			
					nc = c - 97;
					Cell * cell = gameOn.getcell(nr,nc);
					bool aliveOk = false;
					wpiece = isupper(piecetype);
					piecetype = tolower(piecetype);
				//	cout << "GGSEFD " << piecetype << endl;
						while(true){
							if(wpiece){		
								temp = white.getpiece(counter);
							}else{	
								temp = black.getpiece(counter);
							}
							if(temp->getName() == piecetype && (temp->isKilled() || aliveOk)){
								break;
							}
							counter++;
							if(counter == 16){
								aliveOk = true;
								counter = 0;
							}
						}
					Cell * pcell = temp->getPos();
					int r = pcell->getR();
					int c = pcell->getC();
						temp->reverseOn();
						black.killCheck(white,cell);
						white.killCheck(black,cell);
						if(temp->isKilled()){
							temp->revive(wpiece);
						}
						temp->reverseOn();
						if(wpiece){
							white.makeMove(counter,cell);	
						}else{
							black.makeMove(counter,cell);	
						}
						white.addpossiblemove(gameOn);
						black.addpossiblemove(gameOn);
						cout << r << " " << c << " " << nr << " " << nc << " " << piecetype << endl;
						gameOn.notify(r,c, nr, nc, piecetype);
						cout << gameOn;
				}else if(x == "-"){
					cin >> pos;
					istringstream ss(pos.substr(1,1));
					ss >> nr;
					nr = 8  - nr;
					istringstream bb(pos.substr(0,1));
					bb >> c;			
					nc = c - 97;
			//		bool whiteP = true;
					Cell * cell = gameOn.getcell(nr,nc);
			/*		int find = findpiece(white, cell);
					if(find == -1){
						find = findpiece(black,cell);
					}*/
					
					white.killCheck(black,cell);
					black.killCheck(white,cell);
					if((nr + nc) % 2){
						gameOn.notify(nr,nc, nr, nc, '_');
					}else{
						gameOn.notify(nr,nc, nr, nc, ' ');
					
					}
				/*	if(whiteP){
						if(find != -1){
							black.killPiece(find);
						}
						//black.killCheck(white,cell);
					}else{
						if(find != -1){
						white.killPiece(find);
						}
						//white.killCheck(black,cell);
					}	*/
					cout << gameOn;
				}else if(x == "="){
					string colour;
					cin >> colour;
					if(colour == "white"){
						wmove = true;
					}else if(colour == "black"){
						wmove = false;
					}else{
						cerr << "Not a recognized colour" << endl;
					}
				}else if(x == "done"){
					bool canExit = true;
					white.addpossiblemove(gameOn);
					black.addpossiblemove(gameOn);
					//add if king exist
					if((white.getpiece(4))->isKilled()){
						cerr << "White King is dead Can not exit" << endl;
						canExit = false;
					} 
					if((black.getpiece(4))->isKilled()){
						cerr << "Black King is dead Can not exit" << endl;
						canExit = false;
					}
					
					//no pawn on the first and last row of the board
					for(int ie = 0; ie < 2; ie++){
					for(int i = 8; i < maxpieces; i++){
						Cpiece * temp;
						if(ie == 0){
							temp = white.getpiece(i);
						}else if(ie == 1){
							temp = black.getpiece(i);
						}
						Cell * endPos = temp->getPos();
						int endr = endPos->getR();
						if(endr == 7 || endr == 0){
							cout << "Pawn at end of board" << endl;
							canExit = false;
						}
					}
					}
					
					//neither king are checked
				
			//		white.addpossiblemove(gameOn);
			//		black.addpossiblemove(gameOn);
					if(white.isChecked(black.getpiece(4)->getPos())){
						cout << "black being checked can not exit setup" << endl;
						canExit = false;
					}
					if(black.isChecked(white.getpiece(4)->getPos())){
						cout << "white being checked can not exit setup" << endl;
						canExit = false;
					}
					if(canExit){
						break;
					} 
				}else{
					cerr << "INVALID SETUP COMMAND" << endl;
				}
			}
			}else{
				cerr << "A GAME ALREADY STARTED" << endl;
			}	
		}		
	}
	gameOn.printResult(2, false, true, total.whiteScore(), total.blackScore());
	cout << "type x to close window or CTRL+D" << endl;
//	bool e = true;
	cin.clear();
//	cin.ignore();
//	bool end;
/*	while(end && cin >> x){
		char p;
		stringstream zz(x);
		zz >> p;
		cout << "the break is " << p << " " << (p == 120) << endl;
		if(p == 120){
			end = true;
			break;
		}
	}
	*/
//	system("PAUSE");
	sleep(30);
}
