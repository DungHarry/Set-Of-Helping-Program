/*
 * Author: Dung Harry
 * Date created: 25th, May 2014
 * Compiler: GNU Compiler 4.9.0 / MimgW for GCC 4.8.2
 * 
 * Description: this is the source code of simple management program
 */

#include "joy.h"

void main(int argc, char *argv[]) {
	JOY_LIST *pList = JOY_LIST1();

	printf("Enter the input...\n\n");

	JoyList_vEnterInfos(pList);

	printf("\nHalt of entering input...\n\n");

	printf("List after entering from keyboard is as following: \n\n");

	JoyList_vDisplay(pList);
	JoyList_vStoreToFile(pList, "input_keyboard.txt");

	JoyList_vSortByName(pList);

	printf("\nList after sorting by name is as following: \n\n");

	JoyList_vDisplay(pList);
	JoyList_vStoreToFile(pList, "sorting_name.txt");

	JoyList_vSortByAddress(pList);

	printf("\nList after sorting by address is as following: \n\n");

	JoyList_vDisplay(pList);
	JoyList_vStoreToFile(pList, "sorting_address.txt");

	JoyList_vSortByFee(pList);

	printf("\nList after sorting by value of fee is as following: \n\n");

	JoyList_vDisplay(pList);
	JoyList_vStoreToFile(pList, "sorting_fee.txt");

	printf("\nAll of element that had value of fee more than 20 millions is as following: \n\n");

	JoyList_vDisplayByFee(pList, 20000000, FLT_MAX, "result_more_than_20_millions.txt");

	JoyList_vDes(&pList);
}

JOY_INFO* JOY_INFO1(const char *cpcName, const char *cpcAddress, float fFee) {
	JOY_INFO *pNewInfo = (JOY_INFO *) malloc(sizeof(JOY_INFO));

	pNewInfo->pcName = (char *) malloc(sizeof(char) * (strlen(cpcName) + 1));
	strcpy(pNewInfo->pcName, cpcName);

	pNewInfo->pcAddress = (char *) malloc(sizeof(char) * (strlen(cpcAddress) + 1));
	strcpy(pNewInfo->pcAddress, cpcAddress);

	pNewInfo->fFee = fFee >= 0 ? fFee : 0;

	return pNewInfo;
}

void JoyInfo_vDes(JOY_INFO **pInfo) {
	if(pInfo == NULL || *pInfo == NULL)
		return;

	if((*pInfo)->pcName != NULL)
		free((*pInfo)->pcName);

	if((*pInfo)->pcAddress != NULL)
		free((*pInfo)->pcAddress);

	free(*pInfo);
	*pInfo = NULL;
}


JOY_LIST* JOY_LIST1() {
	JOY_LIST *pNewList = (JOY_LIST *) malloc(sizeof(JOY_LIST));

	pNewList->uiCapacity = JOY_LIST_DEFAULT_CAPACITY;
	pNewList->uiNumber = 0;
	pNewList->pData = (JOY_INFO **) malloc(sizeof(JOY_INFO *) * pNewList->uiCapacity);

	return pNewList;
}

void JoyList_vDes(JOY_LIST **pList) {
	if(pList == NULL || *pList == NULL)
		return;

	int i;

	for(i = 0; i < (*pList)->uiNumber; i ++)
		if(*((*pList)->pData + i) != NULL)
			JoyInfo_vDes((*pList)->pData + i);

	free((*pList)->pData);
	free(*pList);

	*pList = NULL;
}


void JoyList_vEnterString(char *pcString, const char *cpcTitle) {
	if(pcString == NULL)
		return;

	int i;

	printf("%s", cpcTitle);
	scanf("%s", pcString);

	for(i = 0; *(pcString + i) != '\0'; i ++);

	for(; (*(pcString + i) = getc(stdin)) != '\n'; i ++);

	*(pcString + i) = '\0';
}

void JoyList_vEnterInfos(JOY_LIST *pList) {
	if(pList == NULL)
		return;

	JOY_INFO *pTmpInfo;
	char *pcTmpName = (char *) malloc(sizeof(char) * JOY_LIST_DEFAULT_BUFFER_SIZE);
	char *pcTmpAddress = (char *) malloc(sizeof(char) * JOY_LIST_DEFAULT_BUFFER_SIZE);
	float fTmpFee;
	int i;

	do {
		printf("Enter number of elements: ");
		scanf("%d", &(pList->uiNumber));

		if(pList->uiNumber > pList->uiCapacity)
			printf("The number of elements can not be greater than capacity of list! Enter again...\n\n");
	} while(pList->uiNumber > pList->uiCapacity);

	for(i = 0; i < pList->uiNumber; i ++) {
		printf("Enter information of element %d...\n\n", i);		

		JoyList_vEnterString(pcTmpName, "Enter name: ");
		JoyList_vEnterString(pcTmpAddress, "Enter address: ");

		printf("Enter the value of fee: ");
		scanf("%f", &fTmpFee);

		pTmpInfo = JOY_INFO1(pcTmpName, pcTmpAddress, fTmpFee);
		*(pList->pData + i) = pTmpInfo;
	}

	free(pcTmpName);
	free(pcTmpAddress);
}

void JoyList_vAdd(JOY_LIST *pList, JOY_INFO **pInfo) {
	if(pList == NULL || pInfo == NULL || *pInfo == NULL)
		return;

	*(pList->pData + pList->uiNumber) = *pInfo;
	pList->uiNumber ++;
}

uint16_t JoyList_uiGetMaxLength(JOY_LIST *pList, uint8_t uiType) {
	if(pList == NULL)
		return 0;

	int i;
	int iTmpLength;
	uint16_t uiResult = 0;

	for(i = 0; i < pList->uiNumber; i ++)
		if((iTmpLength = strlen(uiType == JOY_LIST_TYPE_NAME ? (*(pList->pData + i))->pcName : (*(pList->pData + i))->pcAddress)) > uiResult)
			uiResult = iTmpLength;

	return uiResult;
}

char JoyList_cGetCharAt(JOY_LIST *pList, int iInfoIndex, int iCharIndex, uint8_t uiType) {
	if(pList == NULL || iInfoIndex < 0 || iInfoIndex >= pList->uiNumber || iCharIndex < 0 || iCharIndex >= (uiType == JOY_LIST_TYPE_NAME ? strlen((*(pList->pData + iInfoIndex))->pcName) : strlen((*(pList->pData + iInfoIndex))->pcAddress)))
		return 1;

	return uiType == JOY_LIST_TYPE_NAME ? *((*(pList->pData + iInfoIndex))->pcName + iCharIndex) : *((*(pList->pData + iInfoIndex))->pcAddress + iCharIndex);
}

void JoyList_vSortRange(JOY_LIST *pList, int iCharIndex, int iHeadIndex, int iTailIndex, uint8_t uiType) {
	if(pList == NULL)
		return;

	int i, j, k, iFirstSum, iSecondSum;
	JOY_INFO *pTmpInfo;

	for(i = iHeadIndex; i <= iTailIndex; i ++) {
		for(j = i; j <= iTailIndex; j ++) {
			if(JoyList_cGetCharAt(pList, i, iCharIndex, uiType) > JoyList_cGetCharAt(pList, j, iCharIndex, uiType)) {
				iFirstSum = iSecondSum = 0;

				for(k = 0; k < iCharIndex; k ++) {
					iFirstSum += JoyList_cGetCharAt(pList, i, k, uiType);
					iSecondSum += JoyList_cGetCharAt(pList, j, k, uiType);
				}

				if(iFirstSum == iSecondSum) {
					JoyList_vSwapInfo(pList->pData + i, pList->pData + j, pTmpInfo);
				}
			}
		}
	}
}

void JoyList_vSortByName(JOY_LIST *pList) {
	int iMax = JoyList_uiGetMaxLength(pList, JOY_LIST_TYPE_NAME);
	int iHead, iTail, iTemp, i, j;

	JoyList_vSortRange(pList, 0, 0, pList->uiNumber - 1, JOY_LIST_TYPE_NAME);

	for(j = 1; j <= iMax; j ++) {
		i = 0;

		while(i < pList->uiNumber) {
			iHead = i;

			iTemp = JoyList_cGetCharAt(pList, i, j - 1, JOY_LIST_TYPE_NAME);

			while(JoyList_cGetCharAt(pList, ++ i, j - 1, JOY_LIST_TYPE_NAME) == iTemp) {
				if(i >= pList->uiNumber - 1) {
					i ++;

					break;
				}
			}

			iTail = i - 1;

			JoyList_vSortRange(pList, j, iHead, iTail, JOY_LIST_TYPE_NAME);
		}
	}
}

void JoyList_vSortByAddress(JOY_LIST *pList) {
	int iMax = JoyList_uiGetMaxLength(pList, JOY_LIST_TYPE_ADDRESS);
	int iHead, iTail, iTemp, i, j;

	JoyList_vSortRange(pList, 0, 0, pList->uiNumber - 1, JOY_LIST_TYPE_ADDRESS);

	for(j = 1; j <= iMax; j ++) {
		i = 0;

		while(i < pList->uiNumber) {
			iHead = i;

			iTemp = JoyList_cGetCharAt(pList, i, j - 1, JOY_LIST_TYPE_ADDRESS);

			while(JoyList_cGetCharAt(pList, ++ i, j - 1, JOY_LIST_TYPE_ADDRESS) == iTemp) {
				if(i >= pList->uiNumber - 1) {
					i ++;

					break;
				}
			}

			iTail = i - 1;

			JoyList_vSortRange(pList, j, iHead, iTail, JOY_LIST_TYPE_ADDRESS);
		}
	}
}

void JoyList_vSortByFee(JOY_LIST *pList) {
	if(pList == NULL)
		return;

	int i, j;
	JOY_INFO *pTmpInfo;

	for(i = 0; i < pList->uiNumber; i ++)
		for(j = 0; j <= i; j ++)
			if((*(pList->pData + i))->fFee > (*(pList->pData + j))->fFee) {
				JoyList_vSwapInfo(pList->pData + i, pList->pData + j, pTmpInfo);
			}
}

void JoyList_vDisplay(JOY_LIST *pList) {
	if(pList == NULL)
		return;

	int i;

	for(i = 0; i < pList->uiNumber; i ++) {
		printf("%d. Name: %s\n", i, (*(pList->pData + i))->pcName);
		printf("Address: %s\n", (*(pList->pData + i))->pcAddress);
		printf("Fee: %f\n\n", (*(pList->pData + i))->fFee);
	}	

	printf("Number of elements is: %d\n\n", pList->uiNumber);
}

void JoyList_vDisplayByFee(JOY_LIST *pList, float fLowBound, float fHightBound, const char *cpcFileName) {
	if(pList == NULL)
		return;

	int i, j;
	FILE *pFile;

	pFile = fopen(cpcFileName, "w");

	for(i = 0, j = 0; i < pList->uiNumber; i ++)
		if((*(pList->pData + i))->fFee >= fLowBound && (*(pList->pData + i))->fFee <= fHightBound) {
			printf("%d. Name: %s\n", j, (*(pList->pData + i))->pcName);
			printf("Address: %s\n", (*(pList->pData + i))->pcAddress);
			printf("Fee: %f\n\n", (*(pList->pData + i))->fFee);

			if(pFile != NULL) {
				fprintf(pFile, "%d. Name: %s\n", j, (*(pList->pData + i))->pcName);
				fprintf(pFile, "Address: %s\n", (*(pList->pData + i))->pcAddress);
				fprintf(pFile, "Fee: %f\n\n", (*(pList->pData + i))->fFee);
			}

			j ++;
		}

	printf("Have %d results matched!\n\n", j);

	if(pFile != NULL) {
		fprintf(pFile, "Have %d results matched!\n\n", j);
		fclose(pFile);
	}
}

void JoyList_vStoreToFile(JOY_LIST *pList, const char *cpcFileName) {
	if(pList == NULL)
		return;

	int i;
	FILE *pFile;

	if((pFile = fopen(cpcFileName, "w")) == NULL)
		return;

	for(i = 0; i < pList->uiNumber; i ++) {
		fprintf(pFile, "%d. Name: %s\n", i, (*(pList->pData + i))->pcName);
		fprintf(pFile, "Address: %s\n", (*(pList->pData + i))->pcAddress);
		fprintf(pFile, "Fee: %f\n\n", (*(pList->pData + i))->fFee);
	}	

	fprintf(pFile, "Number of elements is: %d\n\n", pList->uiNumber);

	fclose(pFile);
}
