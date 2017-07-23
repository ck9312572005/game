#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

/*******************************************************************************/
/*                            EXTERNAL REFERENCE                               */
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************/
/*                              CONSTANT DEFINE                                */
/*******************************************************************************/

/*******************************************************************************/
/*                                 DATE TYPE                                   */
/*******************************************************************************/
typedef struct _NODE
{
    void *prStrct;
    struct _NODE *next;
} NODE, *P_NODE;

/*******************************************************************************/
/*                           FUNCTION DECLAIRATION                             */
/*******************************************************************************/
void InsertNode(
    NODE* n1,
    NODE* n2
    );

void RemoveNode(
    NODE* n1
    );

NODE* CreateMode(
    void *prStrct
    );

void PrintLists(
    NODE* lists
    );

void FreeLists(
    NODE* lists
    );

#endif /* LINKLIST_H_INCLUDED */
