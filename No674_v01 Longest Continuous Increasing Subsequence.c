int findLengthOfLCIS(int* nums, int numsSize) {
    if(numsSize == 0){
        return 0;
    }
    int maxLen = 0, crt = 1;
    
    for(int i = 1; i < numsSize; ++i){
        if(nums[i] > nums[i - 1]){
            crt += 1;
        }else{
            if(crt > maxLen){
                maxLen = crt;
            }
            crt = 1;
        }
    }
    if(crt > maxLen){
        return crt;
    }
    return maxLen;
}
