/**
 * 找出最長子陣列的個數
 * 因為有寫過最長子陣列題目，知道可以用dp抓出最長子陣列
 * 本題還要額外紀錄個數，所以應該會有另一個dp用來紀錄每個點的最長子陣列的個數
 */
 
/**
 * version3, 12ms, beats 100%
 * 看一下別人的寫法，幾乎跟前幾版一模一樣，甚至我的maxLen[i] = 0還比設1寫得更好
 * 這版效能主要差在 cv = nums[i]
 * 並把nums[i] > nums[j]改成 cv > nums[j]
 * 感覺是優化在硬體上，CPU運算的時候有些數字會一直暫存著或是留在cache1之類的
 * 可能要看組語才知道為什麼差這麼多
 */

int findNumberOfLIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    
    int resMax = 1, resCnt = 0, cv;
    int *maxLen = (int*)malloc(sizeof(int) * numsSize);
    int *maxCnt = (int*)malloc(sizeof(int) * numsSize);
    
    for(int i = 0; i < numsSize; ++i){
        maxLen[i] = 0;
        maxCnt[i] = 1;
        cv = nums[i];

        for(int j = 0; j < i; ++j){
            if(cv > nums[j]){
                if(maxLen[i] < maxLen[j]){
                    maxLen[i] = maxLen[j];
                    maxCnt[i] = maxCnt[j];
                }else if(maxLen[i] == maxLen[j]){
                    maxCnt[i] += maxCnt[j];
                }
            }
        }
        ++maxLen[i];
        
        if(resMax < maxLen[i]){
            resMax = maxLen[i];
            resCnt = maxCnt[i];
        }else if(resMax == maxLen[i]){
            resCnt += maxCnt[i];
        }
    }
    free(maxLen);
    free(maxCnt);
    return resCnt;
}

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
    
    //把紀錄拉出來算好像沒比較快
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
 * 大體上用了兩個陣列分別存該點最大長度及該點最大長度的數量
 */

int findNumberOfLIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    
    int tmpLen, tmpCnt, resMax = 1, resCnt = 1;
    int *maxLen = (int*)malloc(sizeof(int) * numsSize); //maxLen用來紀錄結尾為nums[i]，最長子陣列的長度
    int *maxCnt = (int*)malloc(sizeof(int) * numsSize); //maxCnt用來紀錄結尾為nums[i]，最長子陣列的個數
    maxLen[0] = 1;
    maxCnt[0] = 1;
    
    for(int i = 1; i < numsSize; ++i){
        tmpLen = 0; //用來更新該輪最長子陣列的長度
        tmpCnt = 1; //用來記錄該輪最長子陣列的個數
        
        //printf("i = %d, nums[%d] = %d\n", i, i , nums[i]);
        for(int j = 0; j < i; ++j){
            if(nums[i] > nums[j]){ //若數字是遞增，才需要進一步判斷
                
                //若發現新的子陣列長度比目前記錄長度的來的大，不但要更新長度，也要更新數量
                if(tmpLen < maxLen[j]){ 
                    tmpLen = maxLen[j];
                    tmpCnt = maxCnt[j];
                
                 //若發現有長度一致的最長子陣列，也要將數量加總(代表有好幾段不同路線都可以達到最長長度)
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
