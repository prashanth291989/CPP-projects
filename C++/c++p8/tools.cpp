#include "tools.h"

// ---------------------------------------------------------------------------
// Used to flush the cin buffer as in cin >> x >> flush;  or cin >> flush;
istream& flush( istream& is )
{
    return is.seekg( 0, ios::end );
}

// ----------------------------------------------------------------------------
//  Error handling and error recovery functions.
//-----------------------------------------------------------------------------
// h is function is for error messages.
//    It takes a format argument priored by any number of data arguments.
//    It formats and prints an error message, then exits.

void fatal (const char* format, ...)
{   va_list vargs;                               // optional arguments

    cout << flush;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    fprintf(stderr, "\n");
    fputs( "\n Error exit; press '.' and 'Enter' to continue", stderr );
    while (getchar() != '.')  // tight loop  ;
    exit(1);
}



