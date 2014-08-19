#include "Game.h"
#include "typesofboard.h"
//----------------------Game class Constructor------------------------//
Game::Game(ifstream& origfile){
   if(!origfile) throw FileNotOpen(Board::filename);
  	type=origfile.get();
  	if(type=='t'){
        myBoard=new TradBoard(origfile,27);
  	}else{
        myBoard=new DiagBoard(origfile,29);
    }
    myViewer = new Viewer(9, 9,*myBoard);
    myViewer->show(cout);
}
//----------------------Game class Destructor------------------------//
Game::~Game(){
    delete myBoard;
    delete myViewer;
    cout<<" Deleting Game"<<endl;
}
//---------------------To Check whether coordinates are valid or not-----//
bool coordCheck(int row, int col){
    if((row<=9 && row>=1) && (col<=9 && col>=1)){
        return true;
    }else{
        return false;
    }
}
//----------------------Delegate to get unmarked value from Board ------//
short int Game::getGameRemaining(){
   return  myBoard->getRemaining();
}
//--------- Delegate to check whether value is possible to mark or not ---//
bool Game::isvaluepossible(int r,int c,char v){
    return  myBoard->isvaluepossible(r,c,v);
}
//--------- Delegate to check whether value is constant or not ---//
bool Game::isvalueconstant(int r,int c){
    return  myBoard->isvalueconstant(r,c);
}

//----------Delegate to set the value of unmarked --------------------//
void Game::setunmarked(short int value){
    myBoard->setRemaining(value);
}
//----------Delegate to mark a value in square ------------------------//
void Game::tomarkvalue(int r,int c,char v){
    myBoard->MarkChar(r,c,v);
}
//----------Delegate to turn off a value in square --------------------//
void Game::toturnoffvalue(int r,int c,int v){
    myBoard->turnoff(r,c,v);
}
//----------To save state to file ------------------------------//
void Game::saveSta(ofstream& myfile){
    myBoard->saveState(myfile);
}
//----------To Reset State to board ---------------------------//
void Game::resetSta(ifstream& myfile1){
    myBoard->resetState(myfile1);
}
//----------Move function to mark a value in Board----------//
void Game::mov(){
    int row,column;
    char value;
    cout<<"Enter your value,row and column number: "<<endl;
    cin>>value>>row>>column;
    if(coordCheck(row,column)){
        if(Square::isValid(value)){
            if(!isvalueconstant(row,column)){
                if(isvaluepossible(row,column,value)){
                    setunmarked(getGameRemaining()-1);
                    tomarkvalue(row,column,value);
                    Frame *f=new Frame();
                    myBoard->saveState(*f);
                    undo.push(f);
                    redo.zap();
                }else{
                    throw ImpossibleError(value,row,column);
                }

            }else{
                    throw FixedError(row,column);
            }
        }else{
                throw ValueError(value);
        }
    }else{
        throw RowNumErrorColNumError(row,column);

    }
}
//-----------------Turn function to turn off a possibility list of square----------//
void Game::turn(){
     int row,column;
    char value,choice;
    cout<<"Enter row and column number: "<<endl;
    cin>>row>>column;
    char ch;
    for(;;){
        cout<<" Enter the value to turn off and 'Y' to quit from turn off "<<endl;
        cin>>value;
        choice=toupper(value);
        if(choice=='Y')break;
            if(coordCheck(row,column)){
                if(Square::isValid(value) && value !='-' ){
                if(isvaluepossible(row,column,value)){
                int c=value-'0';
                toturnoffvalue(row,column,c);
                Frame *f=new Frame();
                myBoard->saveState(*f);
                undo.push(f);
                redo.zap();
            }else{
                throw ImpossibleError(value,row,column);
            }
        }else{
            throw ValueError(value);
        }
    }else{
        throw RowNumErrorColNumError(row,column);
    }
        myViewer = new Viewer(9, 9,*myBoard);
        myViewer->show(cout);
    }
}
//-----------------Save function  to save the Board Square state----------//
void Game::save(){
    ofstream myfile;
    string filename;
    cout<<" Enter the filename: "<<endl;
    cin>>filename;
    myfile.open(filename);
    if(!myfile.is_open())
    throw FileNotOpen(filename);
    saveSta(myfile);
    myfile.close();
}
//-----------------Restore function  to restore the Board Square state----------//
void Game::restore(){
    ifstream myfile1;
    string filename;
    cout<<" Enter the filename: "<<endl;
    cin>>filename;
    myfile1.open (filename);
    if(!myfile1.is_open())
    throw FileNotOpen(filename);
    resetSta(myfile1);
    myfile1.close();
}
//-----------------Undo function to set into previous state ------------------//
void Game::undofun(){
    if(undo.size()>=2){
       redo.push(undo.top());
       undo.pop();
       Frame *f=undo.top();
       myBoard->resetState(*f);
    }
}
//-----------------Redo function to set into previous state ------------------//
void Game::redofun(){
    if(redo.size()>0){
        Frame *f=redo.top();
        redo.pop();
        myBoard->resetState(*f);
        undo.push(f);
    }
}
//-----------------------To Display Menu option -----------------------//
void Game::menu(){
    static const string options[]={" M: Move","T: TurnOFF",
    "S: Save","R: Restore","U: Undo","D: Redo:"," Q: Quit"};
    char ch,choice;
    int row,column;
    char value;
    string filename;
    ofstream myfile;
    ifstream myfile1;
    for(;;){

        if(getGameRemaining()==0){
            cout<<" User has solved the Puzzle";
        }else{
            cout<<" Unmarked square : "<<getGameRemaining()<<endl;
        }
        for(string s: options){
            cout<<s<<"   ";
        }
        cout<<endl;
        cout<<" Enter your choice: "<<endl;
        cin>>ch;
        choice=toupper(ch);

        switch(choice){
            case 'M':mov();
                     break;
            case 'T':turn();
                     break;
            case 'S':save();
                     break;
            case 'R':restore();
                     break;
            case 'U':undofun();
                     break;
            case 'D':redofun();
                     break;
            case 'Q':
                     break;
        }
        if(choice=='Q')break;
        myViewer = new Viewer(9, 9,*myBoard);
        myViewer->show(cout);
    }
}
//---------------------Run function for Game---------------------------//
void Game::run(){
 for(;;){
   try{
        menu();
        break;
    }catch(MalformedFile e){
        e.print(cout);
    }catch(RowNumErrorColNumError e){
        e.print(cout);
    }catch(ValueError e){
        e.print(cout);
    }catch(FixedError e){
        e.print(cout);
    }catch(ImpossibleError e){
        e.print(cout);
    }
  }
}
