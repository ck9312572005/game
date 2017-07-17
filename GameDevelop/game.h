#ifndef GMAE_H_INCLUDED
#define GMAE_H_INCLUDED

/*******************************************************************************/
/*                            EXTERNAL REFERENCE                               */
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************/
/*                              CONSTANT DEFINE                                */
/*******************************************************************************/
#define MAP_ROW_SIZE      4
#define MAP_COL_SIZE      5

#define ROUND_MAX         20

#define BLACK             1
#define WHITE             0

#define USER_COORDINATE   true
#define SYS_COORDINATE    false

#define HISTORY_UNDEFINED 0xFF

#define KNRM              "\x1B[0;m"
#define KRED              "\x1b[;31m;1m"
#define KGRN              "\x1b[;32m;1m"
#define KYEL              "\x1b[;33m;1m"
#define KBLU              "\x1b[;34m;1m"
#define KMAG              "\x1b[;35m;1m"
#define KCYN              "\x1b[;36m;1m"
#define KWHT              "\x1b[;37m;1m"

#define RESET             "\x1b[0;m"
#define RED_BOLD          "\x1b[;31;1m"
#define GRN_BOLD          "\x1b[;32;1m"
#define YEL_BOLD          "\x1b[;33;1m"
#define BLU_BOLD          "\x1b[;34;1m"
#define MAG_BOLD          "\x1b[;35;1m"
#define CYN_BOLD          "\x1b[;36;1m"
#define WHT_BOLD          "\x1b[;37;1m"
#define RED_BOLD_ITALIC   "\x1b[;31;1;3m"
#define GRN_BOLD_ITALIC   "\x1b[;32;1;3m"
#define YEL_BOLD_ITALIC   "\x1b[;33;1;3m"
#define BLU_BOLD_ITALIC   "\x1b[;34;1;3m"
#define MAG_BOLD_ITALIC   "\x1b[;35;1;3m"
#define CYN_BOLD_ITALIC   "\x1b[;36;1;3m"
#define WHT_BOLD_ITALIC   "\x1b[;37;1;3m"

/*******************************************************************************/
/*                                 DATE TYPE                                   */
/*******************************************************************************/

typedef struct _ACTION
{
    unsigned char ucRowIdx;
    unsigned char ucColIdx;
} ACTION, *P_ACTION;

/*******************************************************************************/
/*                           FUNCTION DECLAIRATION                             */
/*******************************************************************************/

void SwitchState(
    unsigned char *pucMapUnit
    );

bool IsRowIdxValid(
    unsigned char ucRowIdx,
    bool fgUserCordinate
    );

bool IsColIdxValid(
    unsigned char ucColIdx,
    bool fgUserCordinate
    );

bool IsGameFinish(
    );

bool IsTimeOut(
    );

void SaveActHistory(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    );

void ClearScreen(
    );

void DisplayRoundInfo(
    );

void DisplayUnit(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    );

void Display(
    );

void QueryAction(
    unsigned char *pucRowIdx,
    unsigned char *pucColIdx
    );

void Operation(
    unsigned char ucRowIdx,
    unsigned char ucColIdx
    );

#endif // GMAE_H_INCLUDED
