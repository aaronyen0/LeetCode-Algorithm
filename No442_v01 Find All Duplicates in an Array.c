/**
 * 概念跟找一個duplication的題目幾乎一模一樣
 * 要特別小心題目寫的數字範圍
 * 常沒仔細看清題目或是聽人說話是我很嚴重的缺點，務必謹記在心！！
 */

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int Abs(int x){
    if(x < 0){
        return -x;
    }
    return x;
}

int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    int *res = (int*)malloc(sizeof(int) * numsSize);
    int offset = 0, tmp;
    for(int i = 0; i < numsSize; ++i){
        tmp = Abs(nums[i]) - 1;
        if(nums[tmp] < 0){
            res[offset++] = tmp + 1;
        }else{
            nums[tmp] = -nums[tmp];
        }
    }
    *returnSize = offset;
    return res;
}
