/*
 * linklist.c
 *
 * Copyright 2017 BY Huang <ck9312572005@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

/*******************************************************************************/
/*                            EXTERNAL REFERENCE                               */
/*******************************************************************************/
#include "linklist.h"

/*******************************************************************************/
/*                              PRIVATE VARIABLE                               */
/*******************************************************************************/

/*******************************************************************************/
/*                                  FUNCTION                                   */
/*******************************************************************************/

void InsertNode(
    NODE* n1,
    NODE* n2
    )
{
    /* Insert Node2 after Node1 */
    n2->next = n1->next;
    n1->next = n2;
}

void RemoveNode(
    NODE* n1
    )
{
    /* Delete Node after Node1 */
    n1->next = n1->next->next;
}

NODE* CreateMode(
    void *prStrct
    )
{
    /* Dynamic allocate memory */
    NODE* n = (NODE*)malloc(sizeof(NODE));

    n->prStrct = prStrct;
    n->next = NULL;

    return n;
}

void PrintLists(
    NODE* lists
    )
{
    NODE* n = lists;

    /* Prinf out all Node content sequentially */
    while (n != NULL)
    {
        /* Need function pointer to replace printf */
        printf("%p ", n->prStrct);

        n = n->next;
    }

    printf("\n");
}

void FreeLists(
    NODE* lists
    )
{
    /* Delete all Note recursively */
    if (lists->next != NULL)
        FreeLists(lists->next);

    /* free dynamic memory for content */
    free(lists->prStrct);

    /* free dynamic memory for Node */
    free(lists);
}
