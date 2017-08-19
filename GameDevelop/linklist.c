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

/*******************************************************************************/
/*                            INTERNAL REFERENCE                               */
/*******************************************************************************/
#include "linklist.h"

/*******************************************************************************/
/*                              PRIVATE VARIABLE                               */
/*******************************************************************************/

/*******************************************************************************/
/*                                  FUNCTION                                   */
/*******************************************************************************/

void InsertNode(
    LIST* n1,
    LIST* n2
    )
{
    /* Insert Node2 after Node1 */
    n2->next = n1->next;
    n1->next = n2;
}

void RemoveNode(
    LIST* n1
    )
{
    /* Delete Node after Node1 */
    n1->next = n1->next->next;
}

LIST* CreateMode(
    void *prStrct
    )
{
    /* Dynamic allocate memory */
    LIST* n = (LIST*)malloc(sizeof(LIST));

    n->prStrct = prStrct;
    n->next = NULL;

    return n;
}

void PrintLists(
    LIST* n1,
    unsigned short u2Length
    )
{
    LIST* n = n1;
    unsigned char ucIndex;

    /* Prinf out all Node content sequentially */
    while (n != NULL)
    {
        /* hex dump  */
        for (ucIndex = 0; ucIndex <= u2Length; ucIndex++)
            printf("%x ", ((char*)n->prStrct)[ucIndex]);

        /* update pointer to next node */
        n = n->next;
    }

    printf("\n");
}

void FreeLists(
    LIST* lists
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
