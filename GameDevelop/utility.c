/*
 * utility.c
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

#include "game.h"

/*******************************************************************************/
/*                                  FUNCTION                                   */
/*******************************************************************************/

char* sfgets(
    char* buf,
    int num,
    FILE* fp,
    bool fgIgnore
)
{
    char* find = 0;

    if (!fgets(buf, num, fp))
        return NULL;

    if ((find = strrchr(buf, '\n')))
        *find = '\0';

    if (fgIgnore)
    {
        char ch;
        while (((ch = fgetc(fp)) != EOF) && (ch != '\n'));
    }

    return buf;
}
