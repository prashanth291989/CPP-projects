/*
 * MixedChar.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: mike
 */

#include "tools.h"
#include "MixedChar.h"

ostream& MixedChar::print(ostream& out) const {
	switch (tag) {
	case single:
		out << singleChar;
		break;
	case multi:
		out << multiChar;
		break;
	default:
		break;
	}
	return out;
}
