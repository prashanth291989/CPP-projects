#include "Square.h"
#include "Board.h"
#include "tools.h"
#include "cluster.h"
#include "Game.h"

//----------------main function----------------//
int main(void){
    try{
        ifstream origfile(Board::filename);
        Game g(origfile);
        g.run();
     }catch(FileNotOpen e){
        e.print(cout);
     }catch(MalformedFile e){
        e.print(cout);
     }
    return 0;
}
