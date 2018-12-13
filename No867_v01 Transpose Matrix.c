/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


int** transpose(int** A, int ARowSize, int *AColSizes, int** columnSizes, int* returnSize) {
    int bRow = AColSizes[0], bCol = ARowSize;
    
    //配置記憶體
    int** B = (int**)malloc(sizeof(int*) * bRow);
    *columnSizes = (int*)malloc(sizeof(int) * bRow);    
    
    //1.填引數回傳值
    //2.配B[row i]記憶體
    //3.for 填matrix
    for(int i = 0; i < bRow; ++i){
        columnSizes[0][i] = bCol;
        B[i] = (int*)malloc(sizeof(int) * bCol);
        for(int j = 0; j < bCol; ++j){
            B[i][j] = A[j][i];
        }
    }
    
    return B;
}

/*

int** transpose(int** A, int ARowSize, int *AColSizes, int** columnSizes, int* returnSize) {
    int bRow = *AColSizes, bCol = ARowSize;
    
    int** B =  (int**)malloc(sizeof(int*) * bRow);
    *columnSizes = (int*)malloc(sizeof(int) * bRow);
    
    for(int i = 0; i < bRow; ++i){
        B[i] = (int*)malloc(sizeof(int) * bCol);
        columnSizes[0][i] = bCol;
    }
    *returnSize = bRow;
    
    for(int i = 0; i < bCol; ++i){
        for(int j = 0; j < bRow; ++j){
            B[j][i] = A[i][j];
        }
    }
    
    return B;
}
*/

