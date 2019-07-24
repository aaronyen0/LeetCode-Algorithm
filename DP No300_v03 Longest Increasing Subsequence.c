/**
 * version3, 0ms, 100%
 * O(n*log(n))
 * 今天發現這題其實很有難度，這是看別人寫的
 * 給一個buffer
 * buffer用來儲存一個遞增數列
 * 而且隨著迴圈推進
 * 會把新的數字丟到數列中，替換掉比較大的數字或是插入在數列最尾端(看數字大小決定)
 * 因此在遞增數列看到的每個數字
 * 就是以該數字為終點的最長遞增數列長度
 *
 * ex: [9, 8, 7, 1, 4, 3, 6, 2, 0]
 * 9: [9]
 * 8: [8]
 * 7: [7]
 * 1: [1]
 * 4: [1, 4]
 * 3: [1, 3]
 * 6: [1, 3, 6]
 * 2: [1, 2, 6]
 * 0: [0, 2, 6]
 */
int search(int *dp, int r, int val) {
    int m, l = 0;
    while (l < r) {
        m = (l + r) / 2;
        if (val > dp[m]){ //只要比val來的小就會往右移，因此會停在比val還要大或是相等的地方
            l = m + 1;
        }else{
            r = m;
        }
    }
    return l;
}

int lengthOfLIS(int* nums, int numsSize){
    if (numsSize < 2){
        return numsSize;
    }
    
    int dp[numsSize];
    dp[0] = nums[0];
    
    int i, j, len = 1;
    for (i = 1; i < numsSize; i++) {
        dp[len] = nums[i];
        j = search(dp, len, nums[i]);
        
        if(j < len){
            dp[j] = dp[len];
        }else{
            len++;
        }
    }
    return len;
}

/**
 * version2
 * 這個解法有點像是爬樓梯問題，可以從任意樓梯爬到當前這個位置
 * 找出從誰爬到這邊才是最有利的
 * dp[i]代表爬到第i階最大的可能性是
 */

int lengthOfLIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    int *dp = (int*)malloc(sizeof(int) * numsSize); //counter
    for(int i = 0; i < numsSize; ++i){
        dp[i] = 1;
    }

    int maxSize = 1;
    
    for(int i = 1; i < numsSize; ++i){
        for(int j = i; j >= 0; --j){
            if(nums[i] > nums[j] && dp[i] <= dp[j]){
                dp[i] = dp[j] + 1;
                if(dp[i] > maxSize){
                    maxSize = dp[i];
                }
            }
        }
    }
    return maxSize;
}


//這些解法都是組合遞迴，跟用dp的解法比起來雖然都是O(n^2)，但遞迴成本太大，所以都會time limit exceeded

void Choose(int* nums, int numsSize, int idx, int preNum, int sNum, int flag, int* maxLen);
void Choose2(int idx, int preNum, int sNum, int flag);

int *gNum = NULL;
int gNumsSize = 0;
int gMaxLen = 0;

int lengthOfLIS(int* nums, int numsSize) {
    gNum = nums;
    gNumsSize = numsSize;
    gMaxLen = 0;
    //Choose(nums, numsSize, 0, -1, 0, 0,  &maxLen);
    Choose2(0, 0, 0, 0);
    return gMaxLen;
}


void Choose2(int idx, int preNum, int sNum, int flag){
    if(idx >= gNumsSize){
        if(sNum > gMaxLen){
            gMaxLen = sNum;
        }
        return;
    }
    
    if(!flag || gNum[idx] > preNum){
        //不選
        //Choose(nums, numsSize, idx + 1, preNum, sNum, flag, maxLen);
        //選
        Choose2(idx + 1, gNum[idx], sNum + 1, 1);
    }
    Choose2(idx + 1, preNum, sNum, flag);
    
}


/*
int lengthOfLIS(int* nums, int numsSize) {
    int maxLen = 0;
    Choose(nums, numsSize, 0, -1, 0, 0,  &maxLen);
    return maxLen;
}


void Choose(int* nums, int numsSize, int idx, int preNum, int sNum, int flag, int* maxLen){
    if(idx >= numsSize){
        if(sNum > *maxLen){
            *maxLen = sNum;
        }
        return;
    }
    
    if(!flag || nums[idx] > preNum){
        //不選
        //Choose(nums, numsSize, idx + 1, preNum, sNum, flag, maxLen);
        //選
        Choose(nums, numsSize, idx + 1, nums[idx], sNum + 1, 1, maxLen);
    }
    Choose(nums, numsSize, idx + 1, preNum, sNum, flag, maxLen);
    
}
*/
