/*
 * GridChar.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: mike
 */

#include "tools.h"
#include "GridChar.h"

GridChar::GridChar() {
	// Boxes are built from glyphs describing box parts.  Each
	// glyph is a 4-spoke figure, with the 4 spokes radiating out
	// from a central hub to the north, east, south, and west.
	// Each spoke may be blank (0), thin (1), or thick (2).
	//
	// The 4-dimensional array utfChar maps the four spokes to the
	// UTF-8 unicode encoding for the corresponding glyph. For
	// example, utfChar[1][2][0][2] is the glyph with a thin line
	// radiating upwards, a thick line radiating horizontally in
	// both directions, and a blank spoke radiating downwards.
	// Not all such glyphs are present here; only those needed to
	// draw a Sudoku board (and a few others).  Undefined glyphs
	// return NULL.

	for (int a = 0; a < 2; a++)
		for (int b = 0; b < 2; b++)
			for (int c = 0; c < 2; c++)
				for (int d = 0; d < 2; d++)
					utfChar[a][b][c][d] = NULL;



	char vertical[1] = {179};

	// blank
	utfChar[0][0][0][0] = ' ';  // ordinary ascii space

	// lines
	utfChar[0][1][0][1] = 196;  // light horiz line
	utfChar[0][2][0][2] = 205;  // heavy horiz line

	utfChar[1][0][1][0] = 179;  // light vert line
	utfChar[2][0][2][0] = 186;  // heavy vert line

	// corners
	utfChar[0][1][1][0] = 218;  // light UL corner
	utfChar[0][2][2][0] = 201;  // heavy UL corner

	utfChar[0][0][1][1] = 191;  // light UR corner
	utfChar[0][0][2][2] = 187;  // heavy UR corner

	utfChar[1][1][0][0] = 217;  // light LL corner
	utfChar[2][2][0][0] = 200;  // heavy LL corner

	utfChar[1][0][0][1] = 192;  // light LR corner
	utfChar[2][0][0][2] = 188;  // heavy LR corner

	// tees
	utfChar[1][1][1][0] = 195;  // light vert light right: L tee |-
	utfChar[1][2][1][0] = 198;  // light vert heavy right: L tee |=
	utfChar[2][1][2][0] = 199;  // heavy vert light right: L tee ||-
	utfChar[2][2][2][0] = 204;  // heavy vert heavy right: L tee ||=

	utfChar[1][0][1][1] = 180;  // light vert light left: R tee -|
	utfChar[1][0][1][2] = 181;  // light vert heavy left: R tee =|
	utfChar[2][0][2][1] = 182;  // heavy vert light left: R tee -||
	utfChar[2][0][2][2] = 185;  // heavy vert heavy left: R tee =||

	utfChar[0][1][1][1] = 194;  // light down light horiz: T tee
	utfChar[0][2][1][2] = 209;  // light down heavy horiz: T tee
	utfChar[0][1][2][1] = 210;  // heavy down light horiz: T tee
	utfChar[0][2][2][2] = 203;  // heavy down heavy horiz: T tee

	utfChar[1][1][0][1] = 193;  // light up light horiz: B tee
	utfChar[1][2][0][2] = 207;  // light up heavy horiz: B tee
	utfChar[2][1][0][1] = 208;  // heavy up light horiz: B tee
	utfChar[2][2][0][2] = 202;  // heavy up heavy horiz: B tee

	// crossings
	utfChar[1][1][1][1] = 197;  // light vert light horiz crossing
	utfChar[1][2][1][2] = 216;  // light vert heavy horiz crossing
	utfChar[2][1][2][1] = 215;  // heavy vert light horiz crossing
	utfChar[2][2][2][2] = 206;  // heavy vert heavy horiz crossing

	// To facilitate the construction of a Sudoku board, we
	// create a matrix indexed by the kind of row and column.
	// There are find kinds of rows/columns:
	//   none:   not a grid line
	//   minor:  a minor (thin) grid line
	//   major:  a major (thick) grid line
	//   edge1:  a major grid line at the top/left of the board
	//   edge2:  a major grid line at the bottom/right of the board
	// Edge lines differ from major lines in that the spokes pointing
	// away from the board should all be blank.

	// Matrix of glyph descriptions for each kind of line crossing are
	// determined below

	// Data line
	boxChar[none][none] = getUtfChar(0,0,0,0);
	boxChar[none][minor] = getUtfChar(1,0,1,0);
	boxChar[none][major] = getUtfChar(2,0,2,0);
	boxChar[none][edge1] = getUtfChar(2,0,2,0);
	boxChar[none][edge2] = getUtfChar(2,0,2,0);

	// Minor line
	boxChar[minor][none] = getUtfChar(0,1,0,1);
	boxChar[minor][minor] = getUtfChar(1,1,1,1);
	boxChar[minor][major] = getUtfChar(2,1,2,1);
	boxChar[minor][edge1] = getUtfChar(2,1,2,0);
	boxChar[minor][edge2] = getUtfChar(2,0,2,1);

	// Major line
	boxChar[major][none] = getUtfChar(0,2,0,2);
	boxChar[major][minor] = getUtfChar(1,2,1,2);
	boxChar[major][major] = getUtfChar(2,2,2,2);
	boxChar[major][edge1] = getUtfChar(2,2,2,0);
	boxChar[major][edge2] = getUtfChar(2,0,2,2);

	// Top line
	boxChar[edge1][none] = getUtfChar(0,2,0,2);
	boxChar[edge1][minor] = getUtfChar(0,2,1,2);
	boxChar[edge1][major] = getUtfChar(0,2,2,2);
	boxChar[edge1][edge1] = getUtfChar(0,2,2,0);
	boxChar[edge1][edge2] = getUtfChar(0,0,2,2);

	// Bottom line
	boxChar[edge2][none] = getUtfChar(0,2,0,2);
	boxChar[edge2][minor] = getUtfChar(1,2,0,2);
	boxChar[edge2][major] = getUtfChar(2,2,0,2);
	boxChar[edge2][edge1] = getUtfChar(2,2,0,0);
	boxChar[edge2][edge2] = getUtfChar(2,0,0,2);

}

const char GridChar::getUtfChar(int a, int b, int c, int d){
	const char uch = utfChar[a][b][c][d];
//	if (uch==NULL)// fatal("Undefined utfChar[%d][%d][%d][%d]", a, b, c, d);
	return uch;
}
