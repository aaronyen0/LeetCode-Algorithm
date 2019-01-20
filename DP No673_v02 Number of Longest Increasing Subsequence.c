/**
 * 找出最長子陣列的個數
 * 因為有遇過最腸子陣列題目，知道可以用dp抓出最長子陣列
 * 不過本題還要額外紀錄個數，所以應該會有另一個dp用來每個點的個數
 */
 
 
/**
 * version2, 16ms, beats 83%
 * 嘗試把迴圈搬出來，不過速度完全沒變
 */
int findNumberOfLIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    
    int tmpLen, tmpCnt, resMax = 1, resCnt = 0;
    int *maxLen = (int*)malloc(sizeof(int) * numsSize);
    int *maxCnt = (int*)malloc(sizeof(int) * numsSize);
    maxLen[0] = 1;
    maxCnt[0] = 1;
    
    for(int i = 1; i < numsSize; ++i){
        tmpLen = 0;
        tmpCnt = 1;
        
        for(int j = 0; j < i; ++j){
            if(nums[i] > nums[j]){
                if(tmpLen < maxLen[j]){
                    tmpLen = maxLen[j];
                    tmpCnt = maxCnt[j];
                }else if(tmpLen == maxLen[j]){
                    tmpCnt += maxCnt[j];
                }
            }
        }
        maxLen[i] = tmpLen + 1;
        maxCnt[i] = tmpCnt;
        
        if(resMax < maxLen[i]){
            resMax = maxLen[i];
        }
    }
    
    for(int i = 0; i < numsSize; ++i){
        if(maxLen[i] == resMax){
            resCnt += maxCnt[i];
        }
    }

    return resCnt;
}


/**
 * version1, 16ms beats 83%
 * 明明看到題目大概就知道怎麼寫，但這版還是寫很久，中間小bug一堆
 * 
int findNumberOfLIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    
    int tmpLen, tmpCnt, resMax = 1, resCnt = 1;
    int *maxLen = (int*)malloc(sizeof(int) * numsSize);
    int *maxCnt = (int*)malloc(sizeof(int) * numsSize);
    maxLen[0] = 1;
    maxCnt[0] = 1;
    
    for(int i = 1; i < numsSize; ++i){
        tmpLen = 0;
        tmpCnt = 1;
        
        //printf("i = %d, nums[%d] = %d\n", i, i , nums[i]);
        for(int j = 0; j < i; ++j){
            if(nums[i] > nums[j]){
                if(tmpLen < maxLen[j]){
                    tmpLen = maxLen[j];
                    tmpCnt = maxCnt[j];
                }else if(tmpLen == maxLen[j]){
                    tmpCnt += maxCnt[j];
                }
            }
            //printf("   j = %d, tmpLen = %d, tmpCnt = %d\n", j, tmpLen, tmpCnt);
        }
        maxLen[i] = tmpLen + 1;
        maxCnt[i] = tmpCnt;
        
        if(resMax < maxLen[i]){
            resMax = maxLen[i];
            resCnt = maxCnt[i];
        }else if(resMax == maxLen[i]){
            resCnt += maxCnt[i];
        }
    }
    
    //PrintArr(maxLen, numsSize);//test
    //PrintArr(maxCnt, numsSize);//test
    return resCnt;
}

void PrintArr(int *arr, int size){
    for(int i = 0; i < size; ++i){
        printf("%d, ", arr[i]);
    }
    printf("\n");
}
