#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#pragma once
#include "Viewer.h"
#include "Board.h"
#include "stack.h"
#include "Game.h"
//-------------Game class declaration-----------------//
class Game{
    private:
        Board *myBoard;
        Viewer *myViewer;
        Stack undo,redo;
        char type;
    public:
        Game(ifstream&);
        ~Game();
        short int getGameRemaining();
        bool isvaluepossible(int ,int ,char);
        void setunmarked(short int );
        void tomarkvalue(int ,int ,char );
        void toturnoffvalue(int ,int ,int );
        bool isvalueconstant(int ,int );
        void mov( );
        void saveSta(ofstream& );
        void resetSta(ifstream& );
        void menu();
        void run();
        void save();
        void turn();
        void restore();
        void undofun();
        void redofun();
};

#endif // GAME_H_INCLUDED
