int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {   
    int** map = (int**)malloc(sizeof(int*) * obstacleGridRowSize);
    for(int i = 0; i < obstacleGridRowSize; ++i){
        map[i] = (int*)malloc(sizeof(int) * obstacleGridColSize);
    }
    
    //更新第一列
    for(int i = 0; i < obstacleGridColSize; ++i){
        if(obstacleGrid[0][i] == 1){
            while(i < obstacleGridColSize){
                map[0][i++] = 0;    
            }
            break;
        }
        map[0][i] = 1;
    }
    
    //更新第一行
    for(int i = 0; i < obstacleGridRowSize; ++i){
        if(obstacleGrid[i][0] == 1){
            while(i < obstacleGridRowSize){
                map[i++][0] = 0;    
            }
            break;
        }
        map[i][0] = 1;
    }
    
    //逐步更新第其他部分
    for(int i = 1; i < obstacleGridRowSize; ++i){
        for(int j = 1; j < obstacleGridColSize; ++j){
            if(obstacleGrid[i][j] == 1){
                map[i][j] = 0;
            }else{
                map[i][j] = map[i - 1][j] + map[i][j - 1];
            }
        }
    }
    return map[obstacleGridRowSize-1][obstacleGridColSize-1];
}
