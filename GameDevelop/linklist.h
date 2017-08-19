#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

/*******************************************************************************/
/*                            EXTERNAL REFERENCE                               */
/*******************************************************************************/
#include "define.h"

/*******************************************************************************/
/*                              CONSTANT DEFINE                                */
/*******************************************************************************/

/*******************************************************************************/
/*                                 DATE TYPE                                   */
/*******************************************************************************/
typedef struct _LIST
{
    void *prStrct;
    struct _LIST *next;
} LIST, *P_LIST;

/*******************************************************************************/
/*                           FUNCTION DECLAIRATION                             */
/*******************************************************************************/
void InsertNode(
    LIST* n1,
    LIST* n2
    );

void RemoveNode(
    LIST* n1
    );

LIST* CreateMode(
    void *prStrct
    );

void PrintLists(
    LIST* n1,
    unsigned short u2Length
    );

void FreeLists(
    LIST* lists
    );

#endif /* LINKLIST_H_INCLUDED */
