/**
 * 不知道下次還能不能想到
 * 個人的寫法
 * 1.從左掃到右
 * 2.從右掃到左
 * 再配合buffer和crt，就可以辦到不用除法達到題目要求
 */

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
