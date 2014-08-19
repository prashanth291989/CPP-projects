#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#pragma once
#include "tools.h"
#include "Square.h"
#include "CanView.h"
#include "Frame.h"

//---------------------------Board class Declaration  -------------------------//
class Board :public CanView{
    private:
        Square  bd[81];
        cluster *clus[27];
        short int unmarked;
        void shoopAll();
    public:
        Board(ifstream &,string);
        ~Board();
        char getMarkChar( int ,int );
        void resetState(Frame& fr);
        void resetState(ifstream& in);
        void saveState(Frame& fr);
        void saveState(ofstream& out);
        void MarkChar( int,int,char);
        void turnoff(int,int,int);
        string getPossibilityString( int row, int col );
        bool isvalueconstant(int ,int );
        short int getRemaining();
        bool isvaluepossible(int ,int ,char);
        void setRemaining(short int);
        int sub(short int ,short int );
        ostream& print( ostream& );

};
//-------------------------inline function for Board class << operator ----------//
inline ostream& operator<<(ostream& out, Board* b){
    return b->print( out );
}

#endif // BOARD_H_INCLUDED
