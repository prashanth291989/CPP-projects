#include "Square.h"
#include "Cluster.h"
#include "string.h"

char SqState::input[]="1 2 3 4 5 6 7 8 9 -";
//-------------Mark function for Square----------------------------------//
void Square::mark( char v,int row,int column ){
    if(!isValid(v)){
        throw ValueError(v);
    }else if(this->inp==false){
            if(isPossible(v)){
                chara=v;
                inp=false;
                posscount=0;
                posslist=0;
                vector<cluster*>::iterator scan;
                for(  scan = clues.begin();scan<clues.end(); ++scan ){
                    (*scan)->shoop(this,v);
                }
            }else{
                throw ImpossibleError(v,row,column);
            }
    }else{
        throw FixedError(row,column);
    }
}
//-------------Get Possibility String ------------------------------------//
string Square::getPossibilityString()const{
    stringstream ss;
    for (int k = 1; k <= 9; ++k) {
        if(isPossible(k)){
            ss<<k;
        }else{
            ss << '-';
        }
    }
    return ss.str();
}
//------------Turn off bits in possibility list----------------/
void SqState::turnOff( int n){
    int mask = 0x1,temp,temp1;
    temp=mask << n;
    temp1=(temp&posslist);

    for(int k=1;k<=n;k++){
        temp1=temp1>>1;
    }
		if((1 & temp1)==1){
            posslist=((~temp)& posslist);
            posscount--;
		}
}

//---------Default Constructor for SqState---------------/
SqState::SqState(){
    chara=0;
    posslist=0;
    posscount=0;
}
//---------Parameterized Constructor for SqState--------/
SqState::SqState(char in){
    if(isValid(in) ){
        if(!isdigit(in)){
            chara=in;
            inp=false;
            posslist=0x03FE;
            posscount=9;
        }else{
            inp=true;
            chara=in;
            posslist=0;
            posscount=0;
        }
    }else{
        throw ValueError(in);
    }
}
//---------Default Constructor for Square---------------------/
Square::Square(){
     row=0;
     column=0;
}
//---------Parameterized Constructor for Square---------------/
Square::Square(char d,short int r,short int w):SqState(d){
    if((r<=9 && r>=1) && (w<=9 && w>=1)){
        row=r;
        column=w;
    }else{
        throw ValueError(d);
    }
}
//----------Print function for SqState------------------------/
ostream& SqState::print( ostream& o){
    o<<"  Value: "<<chara<<" Possibilities: " <<posscount<<":"<<"   ";

     int temp=posslist;
     for(int k=1;k<=9;k++){
        temp=temp>>1;
        if((1 & temp)==1){
            o<< k;
        }else{
            o<<" ";
        }
     }
    return o;
}
//----------Print function for Square------------------------------/
ostream& Square::print( ostream& o){
    if((row<=9 && row>=1) && (column<=9 && column>=1)){
        o<<" Square [" <<row<<","<<column<<"]";
        SqState::print(o)<<endl;
    }
    return o;
}
//---------Destructor for SqState-----------------------------------/
SqState::~SqState(){
   // cout<<" Deleting SqState"<<endl;
}
//---------Destructor for Square------------------------------------/
Square::~Square(){
  //  cout<<" Deleting Square " <<row<<","<<" "<<column<<endl;
}
//---------Add Cluster to vector------------------------------------/
void Square::addCluster(cluster* c){
    clues.push_back(c);
}
 //----------Write SqState into file -------------------------------/
void SqState::serialize(ostream& file) const{
        if(this->inp==true){
            file<<1<<"\n";
        }else{
            file<<0<<"\n";
        }
        file<<this->chara<<"\n";
        file<<this->posscount<<"\n";
        file<<this->posslist<<"\n";
}
//----------To Restore file contents into SqState -----------------/
 void SqState::realize(istream& file){
        string line;
        getline(file,line);
        char c=line.at(0);
        if(c-'0'){
            inp=true;
        }else{
            inp=false;
        }
        getline(file,line);
        this->chara=line.at(0);
        getline(file,line);
        this->posscount=atoi(line.c_str());
        getline(file,line);
        this->posslist=atoi(line.c_str());
 }
//---------Shoop function for square-----/
void Square::shoop(){
    vector<cluster*>::iterator scan;
    for(  scan = clues.begin();scan<clues.end(); ++scan ){
        (*scan)->shoop(this,this->chara);
    }
}
//---------Getter for chara-----------------------------------------/
 char SqState::getchara()const{
    return chara;
 }
 //---------To check square is constant or not ---------------------/
bool SqState::isconstant(){
    if(inp)
        return true;
    return false;
}
