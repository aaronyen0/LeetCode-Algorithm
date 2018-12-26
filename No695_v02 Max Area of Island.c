int DFS(int** grid, int i, int j, int sum, int gridRowSize, int gridColSize){
    
    if(grid[i][j] != 1){
        return sum;
    }
    
    grid[i][j] = 2;
    ++sum;
    
    if(i > 0){
        sum = DFS(grid, i - 1, j, sum, gridRowSize, gridColSize);
    }
    if(i + 1 < gridRowSize){
        sum = DFS(grid, i + 1, j, sum, gridRowSize, gridColSize);
    }
    if(j > 0){
        sum = DFS(grid, i, j - 1, sum, gridRowSize, gridColSize);
    }
    if(j + 1 < gridColSize){
        sum = DFS(grid, i, j + 1, sum, gridRowSize, gridColSize);
    }
    return sum;
}

int maxAreaOfIsland(int** grid, int gridRowSize, int gridColSize) {
    int maxArea = 0, tmp;
    for(int i = 0; i < gridRowSize; ++i){
        for(int j = 0; j < gridColSize; ++j){
            if(grid[i][j] == 1){
                
                tmp = DFS(grid, i, j, 0, gridRowSize, gridColSize);
                if(tmp > maxArea){
                    maxArea = tmp;
                }
                
            }
        }   
    }
    return maxArea;
}


/*8ms beats 100%，前一個版本傳太多參數了
int gRow;
int gCol;

int DFS2(int** grid, int i, int j, int sum){
    if((i >= 0 && i < gRow) && (j >= 0 && j < gCol) && grid[i][j] == 1){
        grid[i][j] = 2;
        sum = DFS2(grid, i - 1, j, sum);
        sum = DFS2(grid, i + 1, j, sum);
        sum = DFS2(grid, i, j - 1, sum);
        sum = DFS2(grid, i, j + 1, sum);
        return ++sum;
    }
    return sum;
}

int maxAreaOfIsland(int** grid, int gridRowSize, int gridColSize) {
    int maxArea = 0, tmp;
    gRow = gridRowSize;
    gCol = gridColSize;
    for(int i = 0; i < gridRowSize; ++i){
        for(int j = 0; j < gridColSize; ++j){
            if(grid[i][j] == 1){
                
                //tmp = DFS(grid, i, j, 0, gridRowSize, gridColSize);
                tmp = DFS2(grid, i, j, 0);
                if(tmp > maxArea){
                    maxArea = tmp;
                }
                
            }
        }   
    }
    return maxArea;
}
