int projectionArea(int** grid, int gridRowSize, int *gridColSizes) {
    int sum = 0;
    int xzHist[50] = {0}, yzHist[50] = {0};
    
    for(int i = 0; i < gridRowSize; ++i){
        for(int j = 0; j < gridRowSize; ++j){
            if(grid[i][j] > 0){
                ++sum;
            }
            if(grid[i][j] > yzHist[j]){
                yzHist[j] = grid[i][j];
            }
            if(grid[i][j] > xzHist[i]){
                xzHist[i] = grid[i][j];
            }
        }    
    }
    for(int i = 0; i < gridRowSize; ++i){
        sum += xzHist[i] + yzHist[i];
    }
    return sum;
    
}
