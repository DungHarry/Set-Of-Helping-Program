/*
 * Author: Dung Harry
 * Date created: 25th, May 2014
 * Compiler: GNU Compiler 4.9.0 / MingW for GCC 4.8.2
 * 
 * Description: this is the header file of program, , that does some following works:
 * 		- Storing information about name, address and fee
 * 		- All information can enter from keyboard with number of clients
 *		- Sorting list of clients by name
 *		- Display all clients, who have fee is more than 20 million
 */

#ifndef _JOY_H_
#define _JOY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <float.h>

#define JOY_LIST_DEFAULT_BUFFER_SIZE 2048

#define JOY_LIST_TYPE_NAME 0
#define JOY_LIST_TYPE_ADDRESS 1
#define JOY_LIST_DEFAULT_CAPACITY 1024
#define JoyList_vSwapInfo(pFirst, pSecond, pTmp) \
	pTmp = *(pFirst); \
	*(pFirst) = *(pSecond); \
	*(pSecond) = pTmp

typedef struct JOY_INFO JOY_INFO;
typedef struct JOY_LIST JOY_LIST;

struct JOY_INFO {
	char *pcName;
	char *pcAddress;
	float fFee;
};

struct JOY_LIST {
	uint16_t uiCapacity;
	uint16_t uiNumber;

	JOY_INFO **pData;
};

JOY_INFO* JOY_INFO1(const char *cpcName, const char *cpcAddress, float fFee);
void JoyInfo_vDes(JOY_INFO **pInfo);

JOY_LIST* JOY_LIST1();
void JoyList_vDes(JOY_LIST **pList);

void JoyList_vEnterString(char *pcString, const char *cpcTitle);
void JoyList_vEnterInfos(JOY_LIST *pList);
void JoyList_vAdd(JOY_LIST *pList, JOY_INFO **pInfo);
uint16_t JoyList_uiGetMaxLength(JOY_LIST *pList, uint8_t uiType);
char JoyList_cGetCharAt(JOY_LIST *pList, int iInfoIndex, int iCharIndex, uint8_t uiType);
void JoyList_vSortRange(JOY_LIST *pList, int iCharIndex, int iHeadIndex, int iTailIndex, uint8_t uiType);
void JoyList_vSortByName(JOY_LIST *pList);
void JoyList_vSortByAddress(JOY_LIST *pList);
void JoyList_vSortByFee(JOY_LIST *pList);
void JoyList_vDisplay(JOY_LIST *pList);
void JoyList_vDisplayByFee(JOY_LIST *pList, float fLowBound, float fHightBound, const char *cpcFileName);
void JoyList_vStoreToFile(JOY_LIST *pList, const char *cpcFileName);

#endif
