/**
 * 給一個2dim matrix
 * 每個格子的數字代表一個顏色
 * 給定一個初始的個子點(r0,c0)
 * 請求出跟這個格子點顏色連通的區塊
 * 並將這個區塊的邊界塗成指定的顏色color
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

/** version1, beats 100%
 * 用dfs從起始點往外擴張尋找區塊
 * 用小於0的數字代表同個區塊(假設顏色的代號都>=0)
 * -1:代表非邊界的區塊
 * -2:代表邊界的區塊
 * 最後再從掃一次圖將-1,-2區塊填為指定的顏色
 */

void dfs(int** grid, int rowSize, int colSize, int r, int c, int ccColor, int bColor);
int** colorBorder(int** grid, int gridSize, int* gridColSize, int r0, int c0, int color, int* returnSize, int** returnColumnSizes){
    int ccColor = grid[r0][c0];
    int colSize = gridColSize[0];
    
    int** resGrid = (int**)malloc(sizeof(int*) * gridSize);
    for(int i = 0; i < gridSize; ++i){
        resGrid[i] = (int*)malloc(sizeof(int) * colSize);
        memcpy(resGrid[i], grid[i], colSize * sizeof(int));
    }
    *returnSize = gridSize;
    *returnColumnSizes = (int*)malloc(sizeof(int) * gridSize);
    memcpy(returnColumnSizes[0], gridColSize, sizeof(int) * gridSize);
    if(color == ccColor){
        return resGrid;
    }
    dfs(resGrid, gridSize, colSize, r0, c0, ccColor, color);
    
    for(int i = 0; i < gridSize; ++i){
        for(int j = 0; j < colSize; ++j){
            if(resGrid[i][j] == -1){
                resGrid[i][j] = ccColor;
            }else if(resGrid[i][j] == -2){
                resGrid[i][j] = color;
            }
        }    
    }
    return resGrid;
}

void dfs(int** grid, int rowSize, int colSize, int r, int c, int ccColor, int bColor){
    //printf("%d, %d, color = %d\n", r, c, grid[r][c]);
    int flag = 0;
    grid[r][c] = -1;
    if(r > 0){
        if(grid[r - 1][c] == ccColor){
            dfs(grid, rowSize, colSize, r - 1, c, ccColor, bColor);
        }else if(grid[r - 1][c] >= 0){
            grid[r][c] = -2;
        }
    }else{
        grid[r][c] = -2;
    }
    
    if(r < rowSize - 1){
        if(grid[r + 1][c] == ccColor){
            dfs(grid, rowSize, colSize, r + 1, c, ccColor, bColor);
        }else if(grid[r + 1][c] >= 0){
            grid[r][c] = -2;
        }
    }else{
        grid[r][c] = -2;
    }
    
    if(c > 0){
        if(grid[r][c - 1] == ccColor){
            dfs(grid, rowSize, colSize, r, c - 1, ccColor, bColor);
        }else if(grid[r][c - 1] >= 0){
            grid[r][c] = -2;
        }
    }else{
        grid[r][c] = -2;
    }
    
    if(c < colSize - 1){
        if(grid[r][c + 1] == ccColor){
            dfs(grid, rowSize, colSize, r, c + 1, ccColor, bColor);
        }else if(grid[r][c + 1] >= 0){
            grid[r][c] = -2;
        }
    }else{
        grid[r][c] = -2;
    }
}
