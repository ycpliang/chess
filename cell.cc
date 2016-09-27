#include <iostream>
#include <string>
#include <sstream>
#include "cell.h"
using namespace std;

Cell::Cell():occupied(false),wpiece(false),r(0), c(0), width(0), height(0), x(0), y(0), xw(0){
}

void Cell::setCoords(int r, int c, int x, int y, int width, int height,Xwindow *w){
	this->r = r;
	this->c = c;
	this->x = x;
	this->y = y;
	this->width = width;
	this->xw = w;
}


void Cell::notifyDisplay(TextDisplay &t, int nr , int nc, char p){
//	cout << "fsdfadsf" << endl;	
	t.notify(nr,nc,r,c,p,wpiece);
}
bool Cell::isoccupied(){
	return occupied;
}

bool Cell::whitepiece()
{
	return wpiece;
}

void Cell::toggle(){
	occupied = !occupied;
}

bool Cell::checkcell(int r, int c)
{
	return (this->r == r && this->c == c);
}

void Cell::changewpiece(bool colour)
{
	this->wpiece = colour;
}

int Cell::getR(){
	return r;
}

int Cell::getC(){

	return c;
}

void Cell::erasepiece(char p){
		stringstream kk;
		string g;
		kk << p;
		kk >>  g;
		//	cout << "hello " <<endl;
		if((r + c) % 2){
		//	xw->fillRectangle(x,y,height,width,Xwindow::White);
			xw->drawString(x + 25, y + 25, g, Xwindow::Orange);
		}else {
		//	xw->fillRectangle(x,y,height,width);
			xw->drawString(x + 25, y + 25, g, Xwindow::Brown);
		}  
}
void Cell::drawpiece(char p){
	erasepiece(p);
	stringstream kk;
	string g;
	kk << p;
	kk >> g;
	if(isupper(p)){
		xw->drawString(x + 25, y + 25, g, Xwindow::White);
	}else{
		xw->drawString(x + 25, y + 25, g);
	}
}
