#ifndef CANVIEW_H_INCLUDED
#define CANVIEW_H_INCLUDED
/*
 * CanView.hpp
 *
 *  Created on: May 15, 2014
 *      Author: mike
 */

// Interface class for a viewable Sudoku model


#include <string>
using namespace std;

class CanView {
public:
	virtual ~CanView() {};
	virtual char getMarkChar(int row, int col) const =0;
	virtual string getPossibilityString(int row, int col) const =0;

};


#endif // CANVIEW_H_INCLUDED
