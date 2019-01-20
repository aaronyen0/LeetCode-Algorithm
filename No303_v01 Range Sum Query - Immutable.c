typedef struct {
    int val;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* array = (NumArray*)malloc(sizeof(NumArray) * numsSize);
    int sum = 0;
    for(int i = 0; i < numsSize; ++i){
        sum += nums[i];
        array[i].val = sum;
    }
    return array;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    if(i > 0){
        return obj[j].val - obj[i - 1].val;
    }
    return obj[j].val;
}

void numArrayFree(NumArray* obj) {
    free(obj);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * struct NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, i, j);
 * numArrayFree(obj);
 */
