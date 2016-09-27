#ifndef __ROOK_H__
#define __ROOK_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class Rook : public Cpiece {
  public:
    Rook(Cell *);
    char getName();
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
