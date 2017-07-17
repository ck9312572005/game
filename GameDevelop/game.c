/*
 * game.c
 *
 * Copyright 2017 bruce2 <bruce2@bruce2-PORTEGE-R30-A>
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
/*                              PRIVATE VARIABLE                               */
/*******************************************************************************/

ACTION grActHistory = {HISTORY_UNDEFINED, HISTORY_UNDEFINED};
unsigned char gucRound = 0;
unsigned char gucMap[MAP_ROW_SIZE][MAP_COL_SIZE] = {{BLACK,BLACK,BLACK,BLACK,BLACK},
                                                    {BLACK,BLACK,BLACK,BLACK,BLACK},
                                                    {WHITE,BLACK,WHITE,BLACK,WHITE},
                                                    {BLACK,BLACK,BLACK,BLACK,BLACK}};

/*******************************************************************************/
/*                                  FUNCTION                                   */
/*******************************************************************************/
void SwitchState(
    unsigned char *pucMapUnit
    )
{
    switch (*pucMapUnit) {
    case BLACK:
        *pucMapUnit = WHITE;
        break;

    case WHITE:
        *pucMapUnit = BLACK;
        break;

    default:
        break;
    }
}

bool IsRowIdxValid(
    unsigned char ucRowIdx,
    bool fgUserCordinate
    )
{
    unsigned char ucLowerBnd[2] = {0, 1};
    unsigned char ucUpperBnd[2] = {MAP_ROW_SIZE-1, MAP_ROW_SIZE};

    if (ucRowIdx < ucLowerBnd[fgUserCordinate])
        return false;

    if (ucRowIdx > ucUpperBnd[fgUserCordinate])
        return false;

    return true;
}

bool IsColIdxValid(
    unsigned char ucColIdx,
    bool fgUserCordinate
    )
{
    unsigned char ucLowerBnd[2] = {0, 1};
    unsigned char ucUpperBnd[2] = {MAP_COL_SIZE-1, MAP_COL_SIZE};

    if (ucColIdx < ucLowerBnd[fgUserCordinate])
        return false;

    if (ucColIdx > ucUpperBnd[fgUserCordinate])
        return false;

    return true;
}

bool IsGameFinish(
    )
{
    bool fgGameFinish = true;
    unsigned char ucRowIdx, ucColIdx;

    for (ucRowIdx = 0; ucRowIdx < MAP_ROW_SIZE; ucRowIdx++) {
		for (ucColIdx = 0; ucColIdx < MAP_COL_SIZE; ucColIdx++) {
            if (BLACK == gucMap[ucRowIdx][ucColIdx])
                fgGameFinish = false;
		}
    }

    return fgGameFinish;
}

bool IsTimeOut(
    )
{
    bool fgTimeOut = false;

    if (gucRound > ROUND_MAX)
        fgTimeOut = true;

    return fgTimeOut;
}

void SaveActHistory(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    /* update action history */
    grActHistory.ucRowIdx = ucRowIdx;
    grActHistory.ucColIdx = ucColIdx;

    /* Round increment */
    gucRound += 1;
}

void ClearScreen(
    )
{
#if defined(_WIN64) || defined(_WIN32)
        system("cls");
#else
        system("clear");
#endif
}

void DisplayGameExplan(
    )
{
    printf("Rule: Please make each unit to be \"O\"!!\n\n");
}

void DisplayRoundInfo(
    )
{
    printf("==================================\n");
    printf("Round:  (%u-%d)\n", gucRound, ROUND_MAX);

    if (HISTORY_UNDEFINED != grActHistory.ucRowIdx)
        printf("Action: Row: %u, Col: %u\n", grActHistory.ucRowIdx + 1, grActHistory.ucColIdx + 1);
    else
        printf("\n");

    printf("==================================\n\n");
}

void DisplayUnit(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    switch (gucMap[ucRowIdx][ucColIdx]) {
    case BLACK:
        printf("X    ");
        break;

    case WHITE:
        printf("O    ");
        break;

    default:
        break;
    }

    return;
}

void Display(
    )
{
	unsigned char ucRowIdx, ucColIdx;

	    /* print Column Index coordination */
        printf("                Column       \n\n");
        printf("        1    2    3    4    5\n\n");

	for (ucRowIdx = 0; ucRowIdx < MAP_ROW_SIZE; ucRowIdx++) {

        /* print Row Index coordination */
        printf("Row %d   ", ucRowIdx+1);

		for (ucColIdx = 0; ucColIdx < MAP_COL_SIZE; ucColIdx++) {
			DisplayUnit(ucRowIdx, ucColIdx);
		}

		/* space line for display */
        printf("\n\n\n");
	}

	return;
}

void QueryAction(
    unsigned char *pucRowIdx,
    unsigned char *pucColIdx
    )
{
    bool fgParamValid;
    unsigned int *pu4Value;

    /* allocate dynamic memory for parameter temp buffer */
    pu4Value = malloc(sizeof(unsigned int));

    do
    {
        /* get Row Index parameter to temp buffer */
        printf("Please key in Row Index (1-%d):", MAP_ROW_SIZE);
        scanf("%u", pu4Value);

        /* assign temp buffer content to Row Index */
        *pucRowIdx = (unsigned char)*pu4Value;

        /* sanity check for Row Index parameter */
        fgParamValid = IsRowIdxValid(*pucRowIdx, USER_COORDINATE);
        /* sanity fail log */

        if (!fgParamValid)
            printf("Your input is %u, which is invalid Row Index!!\n\n", *pucRowIdx);
    } while (!fgParamValid);

    do
    {
        /* get Column Index parameter */
        printf("Please key in Column Index (1-%d):", MAP_COL_SIZE);
        scanf("%u", pu4Value);

        /* assign temp buffer content to Column Index */
        *pucColIdx = (unsigned char)*pu4Value;

        /* sanity check for Column Index parameter*/
        fgParamValid = IsColIdxValid(*pucColIdx, USER_COORDINATE);

        /* sanity fail log */
        if (!fgParamValid)
            printf("Your input is %u, which is invalid Column Index!!\n\n", *pucColIdx);
    } while (!fgParamValid);

    printf("Your action is Row %u and Column %u.\n\n", *pucRowIdx, *pucColIdx);

    /* coordinate transformation for Row Index */
    *pucRowIdx -= 1;

    /* coordinate transformation for Column Index */
    *pucColIdx -= 1;

    /* free dynamic allocated memory */
    free(pu4Value);

	return;
}

void Operation(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    /* Up-Direction map unit state transition */
    if (IsRowIdxValid(ucRowIdx-1, SYS_COORDINATE))
        SwitchState(&gucMap[ucRowIdx-1][ucColIdx]);

    /* Down-Direction map unit state transition */
    if (IsRowIdxValid(ucRowIdx+1, SYS_COORDINATE))
        SwitchState(&gucMap[ucRowIdx+1][ucColIdx]);

    /* Left-Direction map unit state transition */
    if (IsColIdxValid(ucColIdx-1, SYS_COORDINATE))
        SwitchState(&gucMap[ucRowIdx][ucColIdx-1]);

    /* Right-Direction map unit state transition */
    if (IsColIdxValid(ucColIdx+1, SYS_COORDINATE))
        SwitchState(&gucMap[ucRowIdx][ucColIdx+1]);

    /* Self-position map unit state transition */
    SwitchState(&gucMap[ucRowIdx][ucColIdx]);
}

int main(
    int argc,
    char **argv
    )
{
	unsigned char ucRowIdx, ucColIdx;

    /* game rule explanation */
    DisplayGameExplan();

	while (!IsGameFinish()) {

        /* Timeout Check */
        if (IsTimeOut())
            goto lose;

        /* Display Round Information and Action History */
        DisplayRoundInfo();

        /* Display to screen */
        Display(gucMap);

        /* Player action query */
        QueryAction(&ucRowIdx, &ucColIdx);

        /* save action to history list and Round Increment */
        SaveActHistory(ucRowIdx, ucColIdx);

        /* Operation for specific action */
        Operation(ucRowIdx, ucColIdx);

        /* clear screen */
        ClearScreen();
    }

    printf("You win the game!! Congratulations!!\n");

	return 0;

lose:
    printf("Time out!! You lose the game!!\n");

    return 0;
}
