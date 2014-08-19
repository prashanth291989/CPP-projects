#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <vector>
#include "Frame.h"

//-----------------------Stack class Declaraction ------------------------------//
class Stack : private vector<Frame*> {
public:
    Stack();
    ~Stack();
    void pop();                 //Delegate to vector::pop_back()
    Frame* top();               //Delegate to vector::top()
    void push( Frame* );        //Delegate to vector::push_back( Frame* )
    int size();                 //Return the number of Frames on the stack (in the vector).
    void serialize(ostream& out); //Write all the Frame data from the stack to the out stream.
    void realize(istream& in);  //Construct a new Frame and read Frame data into it
                                //from the in stream. Push the new Frame onto the stack.
    void zap();                 //Empty the entire stack by popping everything oﬀ it.
};

#endif // STACK_H_INCLUDED
