int projectionArea(int** grid, int gridRowSize, int *gridColSizes) {
    int sum = 0;
    int xBuffer[50] = {0}, yBuffer[50] = {0};
    
    for(int i = 0; i < gridRowSize; ++i){
        for(int j = 0; j < gridRowSize; ++j){
            if(grid[i][j] > 0){
                ++sum;
            }
            if(grid[i][j] > yBuffer[j]){
                yBuffer[j] = grid[i][j];
            }
            if(grid[i][j] > xBuffer[i]){
                xBuffer[i] = grid[i][j];
            }
        }    
    }
    for(int i = 0; i < gridRowSize; ++i){
        sum += xBuffer[i] + yBuffer[i];
    }
    return sum;
    
}
