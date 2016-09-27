#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"
//#include "window.h"

class Grid{
  Cell **theGrid;
  int gridSize;
  TextDisplay *td;
  Xwindow *xw;
  void cleargame();
 public:
  Grid();
  ~Grid();
  void notify(int, int, int , int , char);
  Cell * getcell(int r, int c); //get the cell pointer
  //void changecell(int r, int c); //change the cell(do not need I think 
  bool isblocked(int r, int c, int nr, int nc);
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
//  bool checkmate();
//  bool checkblock();
  void init(); //call constructor on the cell.
  void printResult(int, bool, bool, int , int);
};

#endif
  	
