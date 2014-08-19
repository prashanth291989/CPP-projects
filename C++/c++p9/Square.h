#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "tools.h"
#pragma once
class cluster;

//--------SqState class declaration-------------/
class SqState{
protected:
    bool inp;                       //value came from the user
                                    //or from the original puzzle input.
    short int posscount;            //A list of possible non-conflicting values
    short int posslist;             //The number of possibilities in the list
    char chara;                     //A digit or a dash

public:
    static char input[];
    void turnOff( int n);
    void serialize(ostream& out) const;
    void realize(istream& in);
    char getchara();
    SqState();
    SqState(char);
    ~SqState();
    ostream& print( ostream& );

//-------Check whether input char is present in valid input string------//
    static bool isValid (char ch ){
        if(strchr(input,ch)!=NULL)
            return true;
        return false;
    }
};
//--------Square  class declaration------------/
class Square:public SqState{
private:
    short int row;
    short int column;
    vector<cluster *> clues;
public:
    Square();
    Square(char,short int,short int );
    ~Square();
    void mark( char );
    void shoop();
    bool isconstant();
    string getPossibilityString();
    void addCluster(cluster * );
    ostream& print( ostream& );
//---------Check whether character is possible to turn off---------//
    bool isPossible( char digit ){
        return isPossible(digit-48);
    }
//---------Check whether number is possible to turn off-----------//
    bool isPossible( int digit ){
        int mask = 0x1,temp=0,temp1=0;
        temp=mask << digit;

        temp1=(temp&posslist);
        for(int k=1; k<=digit; k++){
            temp1=temp1>>1;
        }

        if((1 & temp1)==1)
            return true;
        return false;
    }
};
//---------Inline definition for output operator << -----/
inline ostream& operator <<( ostream& out, Square* s ){
    return s->print( out );
}



#endif // SQUARE_H_INCLUDED
