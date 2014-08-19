#ifndef CANVIEW_H_INCLUDED
#define CANVIEW_H_INCLUDED
#include <string>
using namespace std;

class CanView {
public:
	virtual ~CanView() {};
	virtual char getMarkChar(int row, int col)=0;
	virtual string getPossibilityString(int row, int col)=0;

};

#endif // CANVIEW_H_INCLUDED
