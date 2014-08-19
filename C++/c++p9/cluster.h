#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED
#include "Square.h"
//---------------forward declaration for  Square -----------------//
class Square;
//---------------Enum declaration for clustertype ----------------//
enum  ClusterType{ row,column ,box  };

//---------------Cluster class declaration -----------------------//
class cluster{
    private:
        ClusterType  cttype;

    public:
        Square* s[9];
        static const char* clustype[3];
        cluster(ClusterType , Square* sq[9]);
        ostream& print( ostream& o);
        void shoop( Square* s,char);
};
//---------Inline definition for output operator << -----/
inline ostream& operator<<( ostream& out, cluster* s ) {
    return s->print( out );
}
inline ostream& operator<<( ostream& out, cluster& s ) {
    return s.print( out );
}


#endif // CLUSTER_H_INCLUDED
