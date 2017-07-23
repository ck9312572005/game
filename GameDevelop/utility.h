#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

/*******************************************************************************/
/*                            EXTERNAL REFERENCE                               */
/*******************************************************************************/
#include <stdio.h>
#include <string.h>

/*******************************************************************************/
/*                           FUNCTION DECLAIRATION                             */
/*******************************************************************************/

char* sfgets(
    char* buf,
    int num,
    FILE* fp,
    bool fgIgnore
    );

#endif // UTILITY_H_INCLUDED
