#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#pragma once
#define Windows7

#if  defined Windows7
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

#include <cstdio>      // for NULL
#include <cstdlib>     // for malloc() and calloc()
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>      // for isspace() and isdigit()
#include <cstdarg>     // for functions with variable # of arguments
#else
    // If you are not using a WINDOWS system, put non-WINDOWS #includes here.
#endif

using namespace std;

istream& flush( istream& is );
void fatal (const char* format, ...);

#endif // TOOLS_H_INCLUDED
