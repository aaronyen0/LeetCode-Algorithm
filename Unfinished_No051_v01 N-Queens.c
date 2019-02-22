/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * N皇后，輸出所有滿足N皇后的字串陣列，如下圖
 *  "..Q."
 *  "Q..."
 *  "...Q"
 *  ".Q.."
 */

/**
 * version1, 12ms, beats 17%
 * 還沒看大家都怎麼做
 * 不過個人覺得order已經降很低了
 * 另外Set, Reset的部分其實可以不用去刷新board
 * 要儲存時把stack拿出來抄就好了
 */

void PrintBoard(int size, char** preBoard);

char** GenBoard(int size){
    char** board = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < size; ++i){
        board[i] = (char*)malloc(sizeof(char) * (size + 1));
    }
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            board[i][j] = '.';
        }
        board[i][size] = 0;
    }
    return board;
}

char** CopyBoard(int size, char** preBoard){
    char** board = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < size; ++i){
        board[i] = (char*)malloc(sizeof(char) * (size + 1));
    }
    for(int i = 0; i < size; ++i){
        for(int j = 0; j <= size; ++j){
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

void SetIJ(int i, int j, int* col, int* lSlope, int* rSlope, int rShift, char** board){
    col[j] = 1;
    lSlope[i + j] = 1;
    rSlope[j - i + rShift] = 1;
    board[i][j] = 'Q';
}

void ResetIJ(int i, int j, int* col, int* lSlope, int* rSlope, int rShift, char** board){
    col[j] = 0;
    lSlope[i + j] = 0;
    rSlope[j - i + rShift] = 0;
    board[i][j] = '.';
}


char*** solveNQueens(int n, int* returnSize) {
    int buffSize = 2 * n - 1;
    int rShift = n - 1;
    int* col = (int*)calloc(n, sizeof(int));
    int* lSlope = (int*)calloc(buffSize, sizeof(int));
    int* rSlope = (int*)calloc(buffSize, sizeof(int));
    int offset = 0;
    char*** res = (char***)malloc(sizeof(char**) * 1000);
    char** board = GenBoard(n);
    
    int* stack = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i){
        stack[i] = -1;
    }
    
    int row = 0, j;
    while(row >= 0){
        j = stack[row];
        //printf("row = %d, j = %d\n", row, j);
        if(j != -1){
            ResetIJ(row, j, col, lSlope, rSlope, rShift, board);
        }
        ++j;
        while(j < n && CheckIJ(row, j, col, lSlope, rSlope, rShift) == 0){
            ++j;
        }
        if(j == n){
            stack[row] = -1;
            --row;
        }else if(row == rShift){
            SetIJ(row, j, col, lSlope, rSlope, rShift, board);
            res[offset++] = CopyBoard(n, board);
            //PrintBoard(n, res[offset - 1]);
            ResetIJ(row, j, col, lSlope, rSlope, rShift, board);
            stack[row] = -1;
            --row;
        }else{
            SetIJ(row, j, col, lSlope, rSlope, rShift, board);
            stack[row] = j;
            ++row;
        }
    }
    
    //printf("offset = %d\n", offset);
    
    free(col);
    free(lSlope);
    free(rSlope);
    free(board);
    free(stack);
    
    *returnSize = offset;
    /*
    for(int i = 0; i < offset; ++i){
        PrintBoard(n, res[i]);
    }
    */
    return res;
}


void PrintBoard(int size, char** preBoard){

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            printf("%c ", preBoard[i][j]);
        }
        printf("\n");
    }
}











