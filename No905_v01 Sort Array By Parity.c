/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* A, int ASize, int* returnSize) {
    int i = 0, j = ASize - 1;
    int* ans = malloc(sizeof(int) * ASize);
    *returnSize = ASize;
    
    while(i <= j){
        while(i < j && !(A[i] & 1)){
            ans[i] = A[i++];
        }
        while(i < j && (A[j] & 1)){
            ans[j] = A[j--];
        }
        ans[i] = A[j];
        ans[j] = A[i];
        --j;
        ++i;
    }
    return ans;
}
