#ifndef __PAWN_H__
#define __PAWN_H__
#include <iostream>
#include <string>
#include "cpiece.h"

class Pawn : public Cpiece {
// bool reverse;
 public:
    Pawn(Cell *);
//    void reverseOn();
    char getName();
  //  void promote(char changeTo);
//    bool makeMove(Cell *);
    void addPossibleMove(Grid &);	
};

#endif
