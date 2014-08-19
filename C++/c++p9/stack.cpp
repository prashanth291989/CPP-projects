    #include "stack.h"
//----------------------Stack constructor -----------------------//
    Stack::Stack() : vector<Frame*>() {
    }
//----------------------Stack destructor------------------------//
    Stack::~Stack(){
    }
//----------------------Pop function to pop from vector---------//
    void Stack::pop(){
       vector::pop_back();
    }
//--------Top function to get back element from vector---------//
    Frame* Stack::top(){
        return vector::back();
    }
//---------Push function to push frame into vector -------------//
    void Stack::push( Frame* f){
        vector::push_back(f);
    }
//----------Return size of the vector -------------------------//
    int Stack::size(){
        return vector::size();
        //Return the number of Frames on the stack (in the vector).
    }
//-------Write all the Frame data from the stack to the out stream----//
    void Stack::serialize(ostream& out) {
        for(std::vector<Frame*>::iterator it = this->begin() ; it != this->end(); ++it){
            (*it)->serialize(out);
        }
    }
//-------Read Frame data into frame from the in stream and push into stack---------------//
    void Stack::realize(istream& in){
        Frame f,*pf=&f;
        pf->realize(in);
        push(pf);
    }
//-------------------Empty stack by popping everything on it --------------------------//
    void Stack::zap(){
      while (!this->empty()){
        this->pop_back();
      }
    }
