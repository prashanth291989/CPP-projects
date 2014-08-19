#include "Square.h"
#include "Board.h"
#include "tools.h"
#include "cluster.h"
#include "Game.h"
#include "exception.h"

//------------------main function------------------------------//
int main(void){
    try{
        string filename("puz1.txt");
        ifstream origfile(filename);
        Game g(origfile,filename);
        g.run();
     }catch(FileNotOpen e){
        e.print(cout);
     }catch(MalformedFile e){
        e.print(cout);
     }
    return 0;
}
