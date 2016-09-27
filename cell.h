#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "textdisplay.h"
#include "window.h"
class Cell{
  bool occupied;
  bool wpiece;
  int r,c;
  int width, height;
  int x,y;
  Xwindow *xw;
 public:
  Cell();
  bool checkcell(int r, int c); //check if cell is current cell
  void setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w);
  void notifyDisplay(TextDisplay &t, int nr , int nc, char p);
  bool isoccupied(); //return occupied
  bool whitepiece();//return wpiece
  void toggle();//change occupied
  void changewpiece(bool);	
  int getR();
  int getC();
  void erasepiece(char p);
  void drawpiece(char p);
};

#endif
