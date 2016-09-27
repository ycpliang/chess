#ifndef __KING_H__
#define __KING_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class King : public Cpiece {
  public:
    King(Cell *);
    char getName();
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
