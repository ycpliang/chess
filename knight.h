#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class Knight : public Cpiece {
  public:
    Knight(Cell *);
    char getName();
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
