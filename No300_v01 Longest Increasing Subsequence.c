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
