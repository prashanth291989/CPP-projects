#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED
#pragma once
#include <iostream>
#include "Square.h"
//----------------Frame class declaration---------------------/
class Frame{
    private:
        short int unmarked;
        SqState  sqst[81];
    public:
        friend class Board;
    Frame();
    void display();
    void serialize( ostream& );
    void realize( istream& );
    SqState& operator[](int k);
    const SqState& operator[](int k) const;
};

#endif // FRAME_H_INCLUDED
