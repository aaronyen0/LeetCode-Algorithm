/**
 * version2
 * 這個解法有點像是爬樓梯問題，可以從任意樓梯爬到這個位置
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
