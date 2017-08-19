/*
 * game.c
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
#include "utility.h"
#include "linklist.h"

/*******************************************************************************/
/*                            INTERNAL REFERENCE                               */
/*******************************************************************************/
#include "game.h"

/*******************************************************************************/
/*                              PRIVATE VARIABLE                               */
/*******************************************************************************/

static ACTION _rActHistory = {HISTORY_UNDEFINED, HISTORY_UNDEFINED};
static unsigned char _ucRound = 0;
static LIST* _pListBegin = NULL;
static LIST* _pListEnd = NULL;
static unsigned char _ucMap[MAP_ROW_SIZE][MAP_COL_SIZE] = {{BLACK,BLACK,BLACK,BLACK,BLACK},
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
            if (BLACK == _ucMap[ucRowIdx][ucColIdx])
                fgGameFinish = false;
		}
    }

    return fgGameFinish;
}

bool IsTimeOut(
    )
{
    bool fgTimeOut = false;

    if (_ucRound > ROUND_MAX)
        fgTimeOut = true;

    return fgTimeOut;
}

void SaveActHistory(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    LIST* NextNode;

    /* allocate dynamic memory for action history */
    ACTION* prActionHist = (ACTION*)malloc(sizeof(ACTION));

    /* update action history */
    prActionHist->ucRowIdx = ucRowIdx;
    prActionHist->ucColIdx = ucColIdx;

    /* create node */
    NextNode = CreateMode(prActionHist);

    /* first round check */
    if(0 == _ucRound)
    {
        /* create first node and assign pointer to global variable */
        _pListBegin = NextNode;
        _pListEnd = NextNode;
    }
    else
    {
        /* insert new node */
        InsertNode(_pListEnd, NextNode);

        /* update last node to be node appended */
        _pListEnd = NextNode;
    }

    /* round increment */
    _ucRound += 1;
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
    printf("Goal: Please make each unit to be \"O\"!!\n\n");
    printf("Rule: Key in the coordination and the star range would be flipped!!\n\n");

    printf("Example:\n");
    printf("                Column       \n\n");
    printf("        1    2    3    4    5\n\n");
    printf("Row 1   O    O    O    O    O\n\n");
    printf("Row 2   O    O    O    O    O\n\n");
    printf("Row 3   O    O    O    O    O\n\n");
    printf("Row 4   O    O    O    O    O\n\n\n\n");
    printf("after key in Row 2 and column 3....\n\n");
    printf("                Column       \n\n");
    printf("        1    2    3    4    5\n\n");
    printf("Row 1   O    O    X    O    O\n\n");
    printf("Row 2   O    X    X    X    O\n\n");
    printf("Row 3   O    O    X    O    O\n\n");
    printf("Row 4   O    O    O    O    O\n\n");
}

void DisplayRoundInfo(
    )
{
    printf("==================================\n");
    printf("Round: %u,  Max Round: %d\n", _ucRound, ROUND_MAX);

    if (HISTORY_UNDEFINED != _rActHistory.ucRowIdx)
        printf("Action: Row: %u, Col: %u\n", _rActHistory.ucRowIdx + 1, _rActHistory.ucColIdx + 1);
    else
        printf("\n");

    printf("==================================\n\n");
}

void DisplayUnit(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    switch (_ucMap[ucRowIdx][ucColIdx]) {
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
        printf("Row %d   ", ucRowIdx + 1);

		for (ucColIdx = 0; ucColIdx < MAP_COL_SIZE; ucColIdx++) {
			DisplayUnit(ucRowIdx, ucColIdx);
		}

		/* space line for display */
        printf("\n\n\n");
	}

	return;
}

unsigned char QueryAction(
    ACTION_COORDINATE eActCordin,
    bool (*check)(unsigned char, bool)
    )
{
    bool fgParamValid;
    unsigned char ucValue;
    char cstr[3];

    do
    {
        /* get Row Index parameter to temp buffer */
        printf("Please key in %s Index (1-%d):", (ACTION_COORDINATE_ROW == eActCordin)? ("Row") : ("Column"), MAP_ROW_SIZE);

        /* get user input to buffer */
        sfgets(cstr, sizeof(char)*3, stdin, true);

        /* assign temp buffer content to Row Index */
        ucValue = (unsigned char)strtol(cstr, NULL, 10);

        /* sanity check for Row Index parameter */
        fgParamValid = check(ucValue, USER_COORDINATE);

        /* sanity fail log */
        if (!fgParamValid)
            printf("Your input is %u, which is invalid %s Index!!\n\n", ucValue, (ACTION_COORDINATE_ROW == eActCordin)? ("Row") : ("Column"));
    } while (!fgParamValid);

	return ucValue;
}

void Operation(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    )
{
    /* Up-Direction map unit state transition */
    if (IsRowIdxValid(ucRowIdx-1, SYS_COORDINATE))
        SwitchState(&_ucMap[ucRowIdx-1][ucColIdx]);

    /* Down-Direction map unit state transition */
    if (IsRowIdxValid(ucRowIdx+1, SYS_COORDINATE))
        SwitchState(&_ucMap[ucRowIdx+1][ucColIdx]);

    /* Left-Direction map unit state transition */
    if (IsColIdxValid(ucColIdx-1, SYS_COORDINATE))
        SwitchState(&_ucMap[ucRowIdx][ucColIdx-1]);

    /* Right-Direction map unit state transition */
    if (IsColIdxValid(ucColIdx+1, SYS_COORDINATE))
        SwitchState(&_ucMap[ucRowIdx][ucColIdx+1]);

    /* Self-position map unit state transition */
    SwitchState(&_ucMap[ucRowIdx][ucColIdx]);
}

int main(
    int argc,
    char **argv
    )
{
	unsigned char ucRowIdx, ucColIdx;
	char cstr[2];
    bool fgIsReady;

    /* game rule explanation */
    DisplayGameExplan();

    do
    {
        /* get Column Index parameter */
        printf("Ready to play? (Enter \"P\")");

        /* get user input to buffer */
        sfgets(cstr, sizeof(char)*2, stdin, true);

        /* sanity check for Ready flag */
        fgIsReady = ((cstr[0] == 'P') && (cstr[1] == '\0'))? (true) : (false);
    } while (!fgIsReady);

    /* clear screen */
    ClearScreen();

	while (!IsGameFinish()) {

        /* Timeout Check */
        if (IsTimeOut())
            goto lose;

        /* Display Round Information and Action History */
        DisplayRoundInfo();

        /* Display to screen */
        Display(_ucMap);

        /* Player action query */
        ucRowIdx = QueryAction(ACTION_COORDINATE_ROW, IsRowIdxValid);
        ucColIdx = QueryAction(ACTION_COORDINATE_COL, IsColIdxValid);

        printf("Your action is Row %u and Column %u.\n\n", ucRowIdx, ucColIdx);

        /* coordinate transformation for Row Index */
        ucRowIdx -= 1;

        /* coordinate transformation for Column Index */
        ucColIdx -= 1;

        /* save action to history list and Round Increment */
        SaveActHistory(ucRowIdx, ucColIdx);

        /* Operation for specific action */
        Operation(ucRowIdx, ucColIdx);

        /* clear screen */
        ClearScreen();
    }

    printf("You win the game!! Congratulations!!\n");

    /* pause the screen */
    system("pause");

	return 0;

lose:
    printf("Time out!! You lose the game!!\n");

    return 0;
}
