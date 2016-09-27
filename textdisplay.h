#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>

//use char, let capital letters be black piece
// and lower case letter be white piece
class TextDisplay {
  char **theDisplay;
  int gridSize;
 public:
  TextDisplay();
  void notify(int nr, int nc, int r , int c, char p , bool wpiece);
  ~TextDisplay();
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
