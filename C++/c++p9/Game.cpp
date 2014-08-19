#include "Game.h"
#include "Board.h"
//----------------------Game class Constructor------------------------//
Game::Game(ifstream& origfile,string filename){
    myBoard=new Board(origfile,filename);
    Viewer fancyView(9, 9,myBoard);
    fancyView.show(cout);
}
//----------------------Game class Destructor------------------------//
Game::~Game(){
    delete myBoard;
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
                                Viewer fancyView(9, 9,myBoard);
                                fancyView.show(cout);
                            }else{
                                 throw FixedError(row,column);
                                 Viewer fancyView(9, 9,myBoard);
                                fancyView.show(cout);
                            }
                        }else{
                            throw ValueError(value);
                             Viewer fancyView(9, 9,myBoard);
                                fancyView.show(cout);
                        }
                    }else{
                        throw RowNumErrorColNumError(row,column);
                         Viewer fancyView(9, 9,myBoard);
                        fancyView.show(cout);
                    }
}
//-----------------Turn function to turn off a possibility list of square----------//
void Game::turn(){
    int row,column;
    char value;
    cout<<"Enter your value,row and column number: "<<endl;
    cin>>value>>row>>column;
    if(coordCheck(row,column)){
        if(Square::isValid(value) && value !='-' ){
            if(isvaluepossible(row,column,value)){
            int c=value-'0';
            toturnoffvalue(row,column,c);
            Viewer fancyView(9, 9,myBoard);
            fancyView.show(cout);
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
        Viewer fancyView(9, 9,myBoard);
        fancyView.show(cout);
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
                        fatal(" File couldn't open. ");
                    saveSta(myfile);
                    myfile.close();

                        Viewer fancyView(9, 9,myBoard);
                        fancyView.show(cout);

}
//-----------------Restore function  to restore the Board Square state----------//
void Game::restore(){
    ifstream myfile1;
    string filename;
    cout<<" Enter the filename: "<<endl;
                    cin>>filename;
                    myfile1.open (filename);
                    if(!myfile1.is_open())
                        fatal(" File couldn't open. ");
                    resetSta(myfile1);
                    myfile1.close();

                        Viewer fancyView(9, 9,myBoard);
                        fancyView.show(cout);
}
//-----------------Undo function to set into previous state ------------------//
void Game::undofun(){
    if(undo.size()>=2){
       redo.push(undo.top());
       undo.pop();
       Frame *f=undo.top();
       myBoard->resetState(*f);
    }
    Viewer fancyView(9, 9,myBoard);
    fancyView.show(cout);
}
//-----------------Redo function to set into previous state ------------------//
void Game::redofun(){
    if(redo.size()>0){
        Frame *f=redo.top();
        redo.pop();
        myBoard->resetState(*f);
        undo.push(f);
    }
    Viewer fancyView(9, 9,myBoard);
    fancyView.show(cout);
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
            case 'Q':exit(0);
                     break;
        }
    }
}
//---------------------Run function for Game---------------------------//
void Game::run(){
    try{
        menu();
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
