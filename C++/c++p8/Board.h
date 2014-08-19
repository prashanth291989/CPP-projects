#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#pragma once
#include "Square.h"
#include "CanView.h"
#include "Frame.h"
#include "exception.h"

//---------------------------Board class Declaration  -------------------------//
class Board :public CanView{
    protected:
        int n;
        Square  bd[81];
        cluster **clus;
        short int unmarked;
        void shoopAll();
    public:
        Board(ifstream &,int);
        virtual ~Board();
        static const char* filename;
        char getMarkChar( int ,int )const;
        void resetState(Frame& fr);
        void resetState(ifstream& in);
        void saveState(Frame& fr);
        void saveState(ofstream& out);
        void MarkChar( int,int,char);
        void turnoff(int,int,int);
        string getPossibilityString( int row, int col )const;
        bool isvalueconstant(int ,int );
        short int getRemaining();
        bool isvaluepossible(int ,int ,char);
        void setRemaining(short int);        int sub(short int ,short int );
        const Square& sub(short int ,short int )const;
        ostream& print( ostream& );
        void display();

};
//-------------------------inline function for Board class << operator ----------//
inline ostream& operator<<(ostream& out, Board* b){
    return b->print( out );
}
#endif // BOARD_H_INCLUDED
