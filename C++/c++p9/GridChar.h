#ifndef GRIDCHAR_H_INCLUDED
#define GRIDCHAR_H_INCLUDED
/*
 * grid.hpp
 *
 *  Created on: Oct 27, 2012
 *      Author: mike
 */

#pragma once

//class GridChar : public map<short unsigned, const char*> {
class GridChar {
public:
	enum LineType { none, minor, major, edge1, edge2, numLineType };
private:
	char utfChar[3][3][3][3];
	char boxChar[numLineType][numLineType];
	const char getUtfChar(int a, int b, int c, int d);

public:
	GridChar();
	const char boxGlyph(LineType rt, LineType ct) {
		return boxChar[rt][ct];
	}
};

#endif // GRIDCHAR_H_INCLUDED
