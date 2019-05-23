/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void Swap2(int* val1, int* val2){
    int tmp;
    if(*val2 < *val1){
        tmp = *val2;
        *val2 = *val1;
        *val1 = tmp;
    }
}

void Swap3(int* val1, int* val2, int* val3){
    int tmp;
    if(*val2 < *val1){
        tmp = *val2;
        *val2 = *val1;
        *val1 = tmp;
    }
    if(*val3 < *val1){
        tmp = *val3;
        *val3 = *val1;
        *val1 = tmp;
    }
    if(*val3 < *val2){
        tmp = *val3;
        *val3 = *val2;
        *val2 = tmp;
    }
}

void ChangeBitmap(int* bitmap1, int val1, int* bitmap2, int* val2){
    //printf("1.=== %d, %d ===\n",*bitmap2, val1);
    (*bitmap2) |= val1;
    for(int i = 1;; i <<= 1){
        if( ((*bitmap2) & i) == 0){
            *val2 = i;
            (*bitmap1) |= i;
            //printf("2.=== %d, %d ===\n",*bitmap2, i);
            return;
        }
    }
}

void PinrtArr(int* arr, int len){
    for(int i = 0; i < len; ++i){
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int* gardenNoAdj(int N, int** paths, int pathsSize, int* pathsColSize, int* returnSize){
    int count[10000] = {0};
    int record[10000][3] = {0};
    
    int bitmap[10000] = {0};
    int* res = (int*)calloc(N, sizeof(int));
    int sIdx, eIdx, s, e, tmp;
    
    for(int i = 0; i < pathsSize; ++i){
        if(paths[i][0] < paths[i][1]){
            sIdx = paths[i][0] - 1;
            eIdx = paths[i][1] - 1;
        }else{
            sIdx = paths[i][1] - 1;
            eIdx = paths[i][0] - 1;
        }
        record[sIdx][count[sIdx]++] = eIdx;
    }
    for(int i = 0; i < N; ++i){
        if(count[i] == 2){
            Swap2(&record[i][0], &record[i][1]);
        }else if(count[i] == 3){
            Swap3(&record[i][0], &record[i][1], &record[i][2]);
        }
    }
    
    for(int i = 0; i < N; ++i){
        sIdx = i;
        for(int j = 0; j < count[i]; ++j){
            eIdx = record[i][j];
            
            if(res[sIdx] == 0 && res[eIdx] == 0){
                res[sIdx] = 1;
                res[eIdx] = 2;
                bitmap[sIdx] = 2;
                bitmap[eIdx] = 1;
            }else if(res[sIdx] == 0 && res[eIdx] != 0){
                ChangeBitmap(&bitmap[eIdx], res[eIdx], &bitmap[sIdx], &res[sIdx]);

            }else if(res[sIdx] != 0 && res[eIdx] == 0){
                ChangeBitmap(&bitmap[sIdx], res[sIdx], &bitmap[eIdx], &res[eIdx]);

            }else if(res[sIdx] == res[eIdx]){
                ChangeBitmap(&bitmap[sIdx], res[sIdx], &bitmap[eIdx], &res[eIdx]);
            }else{
                bitmap[eIdx] |= res[sIdx];
            }
        }
    }
    
    for(int i = 0; i < N; ++i){
        if(res[i] == 0){
            res[i] = 1;
        }else if(res[i] == 4){
            res[i] = 3;
        }else if(res[i] == 8){
            res[i] = 4;
        }
    }
    *returnSize = N;
    return res;
}
