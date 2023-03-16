#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    int ArrSize;
    PElement *pEArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print) {
    PAdptArray arr = (PAdptArray) malloc(sizeof(AdptArray));
    if (!arr)
        return NULL;
    arr->ArrSize = 0;
    arr->pEArr = NULL;
    arr->delFunc = del;
    arr->copyFunc = copy;
    arr->printFunc = print;

    return arr;
}

void DeleteAdptArray(PAdptArray arr) {
    if (!arr) {
        return;
    }
    for (int i = 0; i < arr->ArrSize; i++) {
        if (arr->pEArr[i]) {
            arr->delFunc(arr->pEArr[i]);
        }
    }
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement elem) {
    PElement *newArr;
    if (!arr) {
        return FAIL;
    }
    if (arr->ArrSize <= index) {
        if (!arr->pEArr) {
            arr->pEArr = (PElement *) malloc(sizeof(PElement) * (index + 1));
        } else {
            newArr = realloc(arr->pEArr, sizeof(PElement) * (index + 1));
            if (!newArr) {
                return FAIL;
            }
        }
        for (int i = arr->ArrSize; i < index + 1; ++i) {
            arr->pEArr[i] = NULL;

        }
        arr->pEArr[index] = arr->copyFunc(elem);
        arr->ArrSize = index + 1;
        return SUCCESS;
    } else {
        arr->delFunc(arr->pEArr[index]);
        arr->pEArr[index] = arr->copyFunc(elem);
        return SUCCESS;
    }
}

PElement GetAdptArrayAt(PAdptArray arr, int index){
    if(!arr){
        return NULL;
    }
    if(arr->ArrSize<=index){
        return NULL;
    }
    if(!arr->pEArr[index]){
        return NULL;
    }
    return arr->copyFunc(arr->pEArr[index]);
}

int GetAdptArraySize(PAdptArray arr){
    if(!arr){
        return 0;
    }
    return arr->ArrSize;
}
void PrintDB(PAdptArray arr){
    if(!arr){
        return;
    }
    if(arr->ArrSize==0){
        return;
    }
    for (int i = 0; i <arr->ArrSize ; i++) {
        if(arr->pEArr[i]){
            arr->printFunc(arr->pEArr[i]);
        }
    }
}
