#include "cluster.h"

const char* cluster::clustype[] = {"Row","Column","Box" ,"Diag" };
//-------------------------parameterized constructor for cluster class----------//
cluster::cluster(ClusterType c, Square *sq[]){
    cttype=c;
    for(int i=0;i<9;i++){
        s[i]=sq[i];
        s[i]->addCluster(this);
    }

}
//-------------------------print function for Cluster class--------------------//
ostream& cluster::print( ostream& o){
    o<<endl<<" Cluster type : "<<clustype[cttype]<<endl;
    for(int i=0;i<9;i++){
        o<<s[i];
    }
    return o;
}
//---------------------------Shoop  function for cluster class--------------------//
void cluster::shoop(Square *m,char value){
    for(int i=0;i<9;i++){
        s[i]->turnOff(value-'0');
    }
}

