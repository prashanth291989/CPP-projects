#ifndef TYPESOFBOARD_H_INCLUDED
#define TYPESOFBOARD_H_INCLUDED
#include "board.h"
#include <iostream>
//----------------Diagonal Board class declaration ---------------//
class DiagBoard:public Board{
public:
    DiagBoard(ifstream & ,int);
     ~DiagBoard();
};
//-----------------Traditional Board classs declaration -----------//
class TradBoard:public Board{
public:
    TradBoard(ifstream &,int);
    ~TradBoard();
};

#endif // TYPESOFBOARD_H_INCLUDED
