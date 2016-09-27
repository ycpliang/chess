#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class Bishop : public Cpiece {
  public:
    Bishop(Cell *);
    char getName();
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
