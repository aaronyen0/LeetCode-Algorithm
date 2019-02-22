/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
/**
 * 給定一個陣列
 * 回傳所有的排列
 */
 


/**
 * version1, 16ms, beats 14%
 * 標準的排列問題
 */

void permutation(int* nums, int idx, int numsSize, int** ans, int* offset);

int** permute(int* nums, int numsSize, int* returnSize) {
    int size = 1;
    int offset = 0;
    
    for(int i = numsSize; i > 1; --i){
        size *= i;
    }
    
    int** res = (int**)malloc(sizeof(int*) * size);
    for(int i = 0; i < size; ++i){
        res[i] = (int*)malloc(sizeof(int) * numsSize);
    }
    
    permutation(nums, 0, numsSize, res, &offset);
    *returnSize = size;
    return res;
}

void permutation(int* nums, int idx, int numsSize, int** ans, int* offset){
    int tmp;
    if(idx >= numsSize){
        memcpy(ans[*offset], nums, numsSize * sizeof(int));
        (*offset) += 1;
    }else{
        for(int i = idx; i < numsSize; ++i){
            tmp = nums[idx];
            nums[idx] = nums[i];
            nums[i] = tmp;
            
            permutation(nums, idx + 1, numsSize, ans, offset);
            
            tmp = nums[idx];
            nums[idx] = nums[i];
            nums[i] = tmp;
        }
    }
}
