#include "typesofboard.h"
#include "cluster.h"
//---------------Diagonal Board constructor ----------------------//
DiagBoard::DiagBoard(ifstream &origfile,int n):Board(origfile,n){
        int temp;
        Square *sq[9];
        for(int j=1;j<10;j++){
            temp=sub(j,j);
            sq[j-1]=&bd[temp];
        }
        clus[27]=new cluster(diag,sq);
        int j=9;
        for(int i=1;i<10;i++){
            temp=sub(i,j);
            sq[i-1]=&bd[temp];
            j--;
        }
        clus[28]=new cluster(diag,sq);
        shoopAll();
}
//---------------Diagonal board destructor ----------------------//
DiagBoard::~DiagBoard(){

}
//---------------Tradiational Board destructor -------------------//
TradBoard::~TradBoard(){

}
//---------------Tradiational board constructor -------------------//
TradBoard::TradBoard(ifstream &origfile,int n):Board(origfile,n){
    shoopAll();
}
