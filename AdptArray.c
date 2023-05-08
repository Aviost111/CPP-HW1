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
    if (!arr) {
        return NULL;
    }
    arr->ArrSize = 0;
    arr->pEArr = NULL;
    arr->delFunc = del;
    arr->copyFunc = copy;
    arr->printFunc = print;

    return arr;
}

void DeleteAdptArray(PAdptArray arr) {
    //if null return
    if (!arr) {
        return;
    }
    //delete the content if its not null
    for (int i = 0; i < arr->ArrSize; i++) {
        if (arr->pEArr[i]) {
            arr->delFunc(arr->pEArr[i]);
        }
    }
    //delete the array and then the struct
    free(arr->pEArr);
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement elem) {
    PElement *newArr=NULL;
    if (!arr) {
        return FAIL;
    }
    //if array is too small we need to make it bigger
    if (arr->ArrSize <= index) {
        //if it doesn't exist yet create it
        if (!arr->pEArr) {
            arr->pEArr = (PElement*)calloc((index + 1), sizeof(PElement));
            if(!arr->pEArr){
                return FAIL;
            }
            //else just make it bigger
        } else {
            newArr = (PElement*)calloc((index + 1), sizeof(PElement));
            if(!newArr) {
                return FAIL;
            }
            memcpy(newArr, arr->pEArr, (arr->ArrSize) * sizeof(PElement));
            free(arr->pEArr);
            arr->pEArr = newArr;
        }
        //add the element
        arr->pEArr[index] = arr->copyFunc(elem);
        arr->ArrSize = index + 1;
        return SUCCESS;
    } else {
        //if it's not null delete it
        if(arr->pEArr[index]) {
            arr->delFunc(arr->pEArr[index]);
        }
        //add it
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
        if(arr->pEArr[i]!=NULL){
            arr->printFunc(arr->pEArr[i]);
        }
    }
}
