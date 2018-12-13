/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParityII(int* A, int ASize, int* returnSize) {
    int* ans = malloc(sizeof(int) * ASize);
    int i = 0, j = 1, tmp;
    
    while(1){
        while(i < ASize && (A[i] & 1) == 0){
            ans[i] = A[i];
            i += 2;
        }
        
        while(j < ASize && (A[j] & 1) == 1){
            ans[j] = A[j];
            j += 2;
        }
        
        if(i >= ASize || j >= ASize){
            break;
        }
        
        ans[i] = A[j];
        ans[j] = A[i];
        i += 2;
        j += 2;
    }
    *returnSize = ASize;
    return ans;
}
