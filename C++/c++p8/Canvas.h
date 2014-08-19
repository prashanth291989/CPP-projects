#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED
/*
 * Canvas.hpp
 *
 *  Created on: Oct 27, 2012
 *      Author: mike
 */

#pragma once

#include "MixedChar.h"
#include "GridChar.h"

// Create a character drawing canvas for producing pseudo-graphical output

class Canvas {
private:

	const int height;
	const int width;
	const GridChar gc;

	MixedChar* pixel;

	MixedChar& sub(int sr, int sc) {
		return pixel[sr * width + sc];
	}

public:
	Canvas(int nr, int nc);
	~Canvas();

	void setPixel(int sr, int sc, MixedChar c) {
		sub(sr, sc) = c;
	}

	void show(ostream& out);

};

#endif // CANVAS_H_INCLUDED
