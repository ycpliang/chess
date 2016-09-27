#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class Queen : public Cpiece {
  public:
    Queen(Cell *);
    char getName();
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
