/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* returnSize) {
    *returnSize = num + 1;
    int* res = (int*)malloc(sizeof(int) * (*returnSize));
    
    res[0] = 0;
    for(int i = 1; i < (*returnSize); ++i){
        res[i] = res[i >> 1] + (i & 1);
    }
    return res;
}

/*
int* countBits(int num, int* returnSize) {
    *returnSize = num + 1;
    int* res = (int*)malloc(sizeof(int) * (*returnSize));
    int sum, x;
    
    for(int i = 0; i < (*returnSize); ++i){
        x = i;
        sum = 0;
        while(x){
            ++sum;
            x &= (x - 1);
        }
        res[i] = sum;
    }
    return res;
}
