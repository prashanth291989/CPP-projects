#include "Frame.h"
//------------Default null constructor for frame---------------/
Frame::Frame(){
}
//------------Write SqState into file -------------------------/
void Frame::serialize( ostream& file){
    file<<unmarked<<"\n";

    for(int i=0;i<81;i++){
        sqst[i].serialize(file);
    }
}
//------------Write file into SqState--------------------------/
void Frame::realize(istream&  file){
    string line;
    getline(file,line);
    unmarked=atoi(line.c_str());
    for(int i=0;i<81;i++){
        sqst[i].realize(file);
    }
}
//------------Subscript Operator overloading ------------------/
SqState& Frame::operator[](int k){
   return sqst[k];
}
//------------Subscript Operator overloading ------------------/
const SqState& Frame::operator[](int k) const{
    return sqst[k];
}
