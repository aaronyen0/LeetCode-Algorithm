/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** GenBoard(int size){
    char** board = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < size; ++i){
        board[i] = (char*)malloc(sizeof(char) * size);
    }
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            board[i][j] = '.';
        }    
    }
    return board;
}

char** CopyBoard(int size, char** preBoard){
    char** board = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < size; ++i){
        board[i] = (char*)malloc(sizeof(char) * size);
    }
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            board[i][j] = preBoard[i][j];
        }    
    }
    return board;
}

int CheckIJ(int i, int j, int* col, int* lSlope, int* rSlope, int rShift){
    if(col[j] == 1){
        return 0;
    }
    if(lSlope[i + j] == 1){
        return 0;
    }
    if(rSlope[j - i + rShift] == 1){
        return 0;
    }
    return 1;
}

void SetIJ(int i, int j, int* col, int* lSlope, int* rSlope, int rShift){
    col[j] = 1;
    lSlope[i + j] = 1;
    rSlope[j - i + rShift] = 1;
}

void ResetIJ(int i, int j, int* col, int* lSlope, int* rSlope, int rShift){
    col[j] = 0;
    lSlope[i + j] = 0;
    rSlope[j - i + rShift] = 0;
}


char*** solveNQueens(int n, int* returnSize) {
    int buffSize = 2 * n - 1;
    int rShift = n - 1;
    int* col = (int*)calloc(n, sizeof(int));
    int* lSlope = (int*)calloc(buffSize, sizeof(int));
    int* rSlope = (int*)calloc(buffSize, sizeof(int));
    int offset = 0;
    char*** = (char***)malloc(sizeof(int**) * 100);
    
    int* stack = (int*)calloc(n, sizeof(int));
    
    while(stack[0] < n){
        i = stack[0];
        for()
    }
    
    
    

    
    
    
}
