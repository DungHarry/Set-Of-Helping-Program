/*
 * Author: Maito Ly
 * Date created: 24th, May 2014
 * Compiler: GNU Compiler 4.9.0 / MingW for GCC 4.8.2
 * 
 * Description: this is the program that will compute the sum of a string that contain number and chain of character
 * 
 * Example: 
 * 	Input: I am working! 4 34.5 10
 * 	Output: 48.5
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JOY_NUMBER_INVALID 0
#define JOY_NUMBER_TYPE_INTERGER 1
#define JOY_NUMBER_TYPE_DOUBLE 2

typedef struct Joy_stElement Joy_stElement;
typedef struct Joy_stList Joy_stList;

struct Joy_stList {
	Joy_stElement *pHead;
	Joy_stElement *pTail;
};

struct Joy_stElement {
	char *pcString;

	Joy_stElement *pNextElement;
};

void Joy_vEnterString(char **pcString);
Joy_stList* Joy_pSplitByCharacter(char *pcString, char cSplitCharacter);
int Joy_iCheckNummberType(char *pcString);
double Joy_dbGetSum(Joy_stList *pList);

void main(int argc, char *argv[]) {
	char *pString;
	Joy_stList *pList;
	Joy_stElement *pTmpPrev, *pTmpNext;

	Joy_vEnterString(&pString);
	pList = Joy_pSplitByCharacter(pString, ' ');

	printf("Sum is: %lf\n", Joy_dbGetSum(pList));

	free(pString);

	for(pTmpNext = pList->pHead; pTmpNext != NULL; pTmpPrev = pTmpNext, pTmpNext = pTmpNext->pNextElement, free(pTmpPrev->pcString), free(pTmpPrev));
}

void Joy_vEnterString(char **pcString) {
	int i;
	char *pcTmpString = (char *) malloc(sizeof(char) * 2048);

	printf("Enter the string: ");
	scanf("%s", pcTmpString);

	for(i = 0; *(pcTmpString + i) != '\0'; i ++);

	for(; (*(pcTmpString + i) = getc(stdin)) != '\n'; i ++);

	*(pcTmpString + i) = '\0';

	*pcString = (char *) malloc(sizeof(char) * (strlen(pcTmpString) + 1));

	strcpy(*pcString, pcTmpString);

	free(pcTmpString);
}

Joy_stList* Joy_pSplitByCharacter(char *pcString, char cSplitCharacter) {
	if(pcString == NULL)
		return NULL;

	Joy_stElement* pTmpElement;
	Joy_stList* pResult;
	char *pcTmpString = (char *) malloc(sizeof(char) * 2048);
	int i, j;

	pResult = (Joy_stList *) malloc(sizeof(Joy_stList));

	pResult->pHead = NULL;
	pResult->pTail = NULL;

	for(i = 0; *(pcString + i) != '\0'; i ++) {
		for(j = 0; (*(pcTmpString + j) = *(pcString + i)) != cSplitCharacter && *(pcString + i) != '\0'; j ++, i ++);

		if(*(pcString + i) != '\0')
			*(pcTmpString + j) = '\0';

		pTmpElement = (Joy_stElement *) malloc(sizeof(Joy_stElement));

		pTmpElement->pNextElement = NULL;
		pTmpElement->pcString = (char *) malloc(sizeof(char) * (strlen(pcTmpString) + 1));

		strcpy(pTmpElement->pcString, pcTmpString);

		if(pResult->pHead == NULL && pResult->pTail == NULL)
			pResult->pTail = pResult->pHead = pTmpElement;
		else if(pResult->pHead == pResult->pTail) {
			pResult->pHead->pNextElement = pTmpElement;
			pResult->pTail = pTmpElement;
		} else {
			pResult->pTail->pNextElement = pTmpElement;
			pResult->pTail = pTmpElement;		
		}

		if(*(pcString + i) == '\0')
			break;
	}

	free(pcTmpString);

	return pResult;
}

int Joy_iCheckNummberType(char *pcString) {
	if(pcString == NULL)
		return JOY_NUMBER_INVALID;

	int iNumComma;
	int i;

	for(i = *pcString == '-' ? 1 : 0, iNumComma = 0; *(pcString + i) != '\0'; i ++)
		if(*(pcString + i) == '.')
			iNumComma ++;
		else if(*(pcString + i) < '0' || *(pcString + i) > '9')
			return JOY_NUMBER_INVALID;

	if(iNumComma == 0)
		return JOY_NUMBER_TYPE_INTERGER;
	else if(iNumComma == 1)
		return JOY_NUMBER_TYPE_DOUBLE;
	else
		return JOY_NUMBER_INVALID;
}

double Joy_dbGetSum(Joy_stList *pList) {
	if(pList == NULL || pList->pHead == NULL || pList->pTail == NULL)
		return -1;

	Joy_stElement *pTmpElement;
	double dbSumResult = 0;
	int iTmpResult;

	for(pTmpElement = pList->pHead; pTmpElement != NULL; pTmpElement = pTmpElement->pNextElement)
		if((iTmpResult = Joy_iCheckNummberType(pTmpElement->pcString)) == JOY_NUMBER_TYPE_INTERGER)
			dbSumResult += (double) (atoi(pTmpElement->pcString));
		else if(iTmpResult == JOY_NUMBER_TYPE_DOUBLE) 
			dbSumResult += (double) (atof(pTmpElement->pcString));

	return dbSumResult;
}
