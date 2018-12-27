/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int* res = (int*)malloc(sizeof(int) * numsSize);
    res[0] = 1;
    int crt;
    
    for(int i = 1; i < numsSize; ++i){
        res[i] = res[i - 1] * nums[i - 1];
    }
    
    crt = 1;
    for(int i = numsSize - 2; i >= 0; --i){
        crt *= nums[i + 1];
        res[i] *= crt;
    }
    *returnSize = numsSize;
    return res;
}
