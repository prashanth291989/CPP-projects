#include "Board.h"
#include "cluster.h"
#include "exception.h"
//------------------------Parameterized constructor of Board -------------------//
Board::Board(ifstream &inputpuzzle,string filename){
    char input;int temp;
    Square *sq[9];
    unmarked=81;
    if(!inputpuzzle) throw FileNotOpen(filename);
        for( int j=1; j<10; j++){
            for( int k=1; k<10; k++){
                input=inputpuzzle.get();
                if(isdigit(input)|| input=='-'){
                    if(input!='-')
                        unmarked--;
                    temp=sub(j,k);
                    bd[temp]=Square(input,j,k);
                    sq[k-1]=&bd[temp];
                }else{
                     throw MalformedFile(filename);
                }
            }
            clus[j-1]=new cluster(row,sq);
            input=inputpuzzle.get();  // the newline.
        }
        inputpuzzle.close();
        int i=9;

        // Make the clusters for the columns.
        for(int j=1;j<10;j++){
            for(int k=1;k<10;k++){
                temp=sub(k,j);
                sq[k-1]=&bd[temp];
            }
            clus[i]=new cluster(column,sq);
            i++;
        }
        int count1=0,count2=0,count3=0,b=18;temp=0;
        Square *sq1[9],*sq2[9];

        // Make the clusters for the boxes.
        for(int i=0;i<27;i++){
                temp=i%9;
            if(temp==0 || temp==1 || temp==2){
                sq[count1]=&bd[i];
                count1++;
            }else if(temp==3 || temp==4 || temp==5){
                sq1[count2]=&bd[i];
                 count2++;
            }else{
                sq2[count3]=&bd[i];
                count3++;
            }
        }
        clus[b]=new cluster(box,sq);
        clus[++b]=new cluster(box,sq1);
        clus[++b]=new cluster(box,sq2);
        count1=0,count2=0,count3=0;

         for(int j=27;j<54;j++){
              temp=j%9;
            if(temp==0 || temp==1 || temp==2){
                sq[count1]=&bd[j];
                count1++;
            }else if(temp==3 || temp==4 || temp==5){
                sq1[count2]=&bd[j];
                count2++;
            }else{
                sq2[count3]=&bd[j];
                count3++;
            }
        }
        clus[++b]=new cluster(box,sq);
        clus[++b]=new cluster(box,sq1);
        clus[++b]=new cluster(box,sq2);
        count1=0,count2=0,count3=0;

        for(int j=54;j<81;j++){
              temp=j%9;
            if(temp==0 || temp==1 || temp==2){
                sq[count1]=&bd[j];
                count1++;
            }else if(temp==3 || temp==4 || temp==5){
                sq1[count2]=&bd[j];
                count2++;
            }else{
                sq2[count3]=&bd[j];
                count3++;
            }
        }
        clus[++b]=new cluster(box,sq);
        clus[++b]=new cluster(box,sq1);
        clus[++b]=new cluster(box,sq2);

        shoopAll();
}
//---------------------Return the number of remaining unmarked squares.---------//
short int Board::getRemaining(){
    return unmarked;
}
//---------------------set the number of remaining unmarked squares.---------//
void  Board::setRemaining(short int s){
    unmarked=s;
}
//---------------------Write data from file into Square -------------------------//
void Board::resetState(Frame& fr){
     this->unmarked=fr.unmarked;
     for(int i=0;i<81;i++){
        (SqState&)bd[i]=(fr).sqst[i];
     }
}
//---------------------shoop the digit out of all its clusters---------------//
void Board::shoopAll(){
    for(int i=0;i<81;i++){
        bd[i].shoop();
    }
}
//-------------------Write data from file into Square ---------------//
void Board::resetState(ifstream& in){
    Frame f;
    f.realize(in);
    resetState(f);
}

//-------------------Write data into frame from Square---------------------------//
void Board::saveState(Frame& fr){
    fr.unmarked=unmarked;
    for(int i=0;i<81;i++){
        fr[i]=(SqState)bd[i];
     }
}
//------------------Write data into frame from Square---------------------------//
void Board::saveState(ofstream& out) {
    Frame f;
    saveState(f);
    f.serialize(out);
}
//----------------To Get Mark character -------------------------------------//
void Board::MarkChar( int row, int col,char value ){
     bd[sub(row,col)].mark(value);
}
//-----------------To Get Possibility String --------------------------------//
string Board::getPossibilityString( int row, int col ) {
     return bd[sub(row,col)].getPossibilityString();
}
//-----------------------Sub script function for  Board ---------------------//
int Board::sub(short int j,short int k ){
    return (j-1)*9+(k-1);
}
//-----------------To Turn off value in square ----------------------------//
void Board::turnoff(int row ,int col,int value){
     bd[sub(row,col)].turnOff(value);
}
//------------------------Print function for Board --------------------------//
ostream& Board::print( ostream& o){
    for(int i=0; i<27; i++){
        o<<"--------------------------------------------------------------";
        o<<clus[i]<<endl;
        o<<"--------------------------------------------------------------";
    }
    return o;
}
//-----------------------Destructor for Board--------------------------------//
Board::~Board(){
    for(int i=0; i<27; i++){
        delete clus[i];
        cout<<" Deleting Board"<<endl;
    }
}

//-------------Delegate to square to check whether value is possible to mark--//
bool Board::isvaluepossible(int r,int c,char v){
    return bd[sub(r,c)].isPossible(v);
}
//-------------Delegate to square to check whether value is possible to mark--//
bool Board::isvalueconstant(int r,int c){
    return  bd[sub(r,c)].isconstant();
}
//----------------To Get Mark character -------------------------------------//
char Board::getMarkChar( int row, int col ){
    return bd[sub(row,col)].getchara();
}
