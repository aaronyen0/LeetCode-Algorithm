/**
 * 採地雷
 * 給一個二維陣列，以及一個click point
 * 其中click point必為未曾翻開的格子
 * 定義：
 * 'M': 尚未翻開的地雷
 * 'X': 翻開的地雷
 * 'E': 期他尚未翻開的格子
 * 'B': 翻開且為空白的格子
 * '1'~'8': 翻開並顯示周遭的地雷數
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


/**
 * version1, 44ms, 83%
 * 照採地雷規則寫
 * 沒什麼特殊的結構
 * 在遍歷'E'或計算周遭地雷上
 * 由於要小心邊界問題，用check[8]當作邊界條件
 * 省略了一些冗長的判斷式
 */

void traversal_blanks(char** board, int rowSize, int colSize, int row, int col);

char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes){
    int colSize = boardColSize[0];
    
    char** map = (char**)malloc(sizeof(char*) * boardSize);
    int* resArrSize = (int*)malloc(sizeof(int) * boardSize);
    for(int i = 0; i < boardSize; ++i){
        map[i] = malloc(sizeof(char) * (colSize));
        memcpy(map[i], board[i], sizeof(char) * colSize);
        resArrSize[i] = colSize;
    }
    
    traversal_blanks(map, boardSize, colSize, click[0], click[1]);
    
    *returnSize = boardSize;
    *returnColumnSizes = resArrSize;
    return map;
}


void traversal_blanks(char** board, int rowSize, int colSize, int row, int col){
    /**
     * 1. 檢察是否為地雷
     * 2. 決定周遭八格是否為邊界(check[8])
     * 3. 計算周遭非邊界的地雷數
     * 4. 若地雷數為0，則該格為空白，根據邊界與否往周遭八格的'E'遍歷
     */
     
    if(board[row][col] == 'M'){
        board[row][col] = 'X';
        return;
    }
    
    int mine_cnt = 0;
    int row_add1 = row + 1;
    int row_minus1 = row - 1;
    int col_add1 = col + 1;
    int col_minus1 = col - 1;
    int check[8] = {1,1,1,1,1,1,1,1}; //LU U RU, L R, LD D RD
    
    //pre-check
    if(row == 0){
        check[0] = 0;
        check[1] = 0;
        check[2] = 0;
    }
    if(row_add1 == rowSize){
        check[5] = 0;
        check[6] = 0;
        check[7] = 0;
    }
    if(col == 0){
        check[0] = 0;
        check[3] = 0;
        check[5] = 0;
    }
    if(col_add1 == colSize){
        check[2] = 0;
        check[4] = 0;
        check[7] = 0;
    }
    
    // count mines
    if(check[0] && board[row_minus1][col_minus1] == 'M'){
        mine_cnt++;
    }
    if(check[1] && board[row_minus1][col] == 'M'){
        mine_cnt++;
    }
    if(check[2] && board[row_minus1][col_add1] == 'M'){
        mine_cnt++;
    }
    if(check[3] && board[row][col_minus1] == 'M'){
        mine_cnt++;
    }
    if(check[4] && board[row][col_add1] == 'M'){
        mine_cnt++;
    }
    if(check[5] && board[row_add1][col_minus1] == 'M'){
        mine_cnt++;
    }
    if(check[6] && board[row_add1][col] == 'M'){
        mine_cnt++;
    }
    if(check[7] && board[row_add1][col_add1] == 'M'){
        mine_cnt++;
    }
    
    if(mine_cnt){
        board[row][col] = '0' + mine_cnt;
        return;
    }
    
    // if there is no mine besied, traversal blanks
    board[row][col] = 'B';
    
    if(check[0] && board[row_minus1][col_minus1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_minus1, col_minus1);
    }
    if(check[1] && board[row_minus1][col] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_minus1, col);
    }
    if(check[2] && board[row_minus1][col_add1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_minus1, col_add1);
    }
    if(check[3] && board[row][col_minus1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row, col_minus1);
    }
    if(check[4] && board[row][col_add1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row, col_add1);
    }
    if(check[5] && board[row_add1][col_minus1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_add1, col_minus1);
    }
    if(check[6] && board[row_add1][col] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_add1, col);
    }
    if(check[7] && board[row_add1][col_add1] == 'E'){
        traversal_blanks(board, rowSize, colSize, row_add1, col_add1);
    }
}

