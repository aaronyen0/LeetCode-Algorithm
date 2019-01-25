/**
 * 給定一個二維陣列
 * 每一格的數字，代表進入該點所+-的血量
 * 若從進入左上開始走到右下，在血量恆為正(不死)的情況之下
 * 至少初始血量要多少
 */

/**
 * version2 0ms, beats 100%
 * 稍微優化一下，並更換dp的定義
 * 定義dp[i][j]為進入這一格之前至少要有多少血量才能不死
 * 因此 dp[終點] = max(終點扣的血量 + 1, 1)
 * 其餘和version1很像，注意index位置就好
 */

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int *dungeonColSizes) {
    int colSize = dungeonColSizes[0], m, n;
    int **dp = (int**)malloc(sizeof(int*) * dungeonRowSize);
    for(int i = 0; i < dungeonRowSize; ++i){
        dp[i] = (int*)malloc(sizeof(int) * colSize);
    }
    
    m = dungeonRowSize - 1;
    n = colSize - 1;
    if(dungeon[m][n] < 0){
        dp[m][n] = 1 - dungeon[m][n];
    }else{
        dp[m][n] = 1;
    }
    
    for(int i = dungeonRowSize - 2; i >= 0; --i){
        dp[i][n] = dp[i + 1][n] - dungeon[i][n];
        if(dp[i][n] <= 0){
            dp[i][n] = 1;
        }
    }
    for(int i = colSize - 2; i >= 0; --i){
        dp[m][i] = dp[m][i + 1] - dungeon[m][i];
        if(dp[m][i] <= 0){
            dp[m][i] = 1;
        }
    }
    
    for(int i = dungeonRowSize - 2; i >= 0; --i){
        for(int j = colSize - 2; j >= 0; --j){
            dp[i][j] = Min2(dp[i + 1][j] - dungeon[i][j], dp[i][j + 1] - dungeon[i][j]);
            if(dp[i][j] <= 0){
                dp[i][j] = 1;
            }
        }
    }

    return dp[0][0];
}

/**
 * version1 0ms, beats 100%
 * 這題不像最短路徑問題單純求極大或求極小
 * 麻煩點在需要一直保持在不死的血量
 * 個人定義dp[i][j]為站在該格時，繼續朝最佳路徑走剛好會死掉的血量，且該血量至少為0
 * 另外這題要從終點往回推，才知道進入該格時至少要有多少血
 *
 * 心得：
 * 雖然這題為hard
 * 但這種二維陣列的路徑問題
 * 往往比一維陣列的容易想到解法
 * 感覺是國高中在排列組合時就常遇到路徑問題
 * 反而訓練有素
 * 以後應該優先找單一陣列的DP問題
 */

int Min2(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int *dungeonColSizes) {
    int colSize = dungeonColSizes[0], m, n;
    int **dp = (int**)malloc(sizeof(int*) * dungeonRowSize);
    for(int i = 0; i < dungeonRowSize; ++i){
        dp[i] = (int*)malloc(sizeof(int) * colSize);
    }
    
    m = dungeonRowSize - 1;
    n = colSize - 1;
    dp[m][n] = 0;
    
    //dp[i][n]為下一格至少要有的血量dp[i + 1][n]，扣除該格增減的血量dungeon[i + 1][n]，而且要非負
    for(int i = dungeonRowSize - 2; i >= 0; --i){
        dp[i][n] = dp[i + 1][n] - dungeon[i + 1][n];
        if(dp[i][n] < 0){
            dp[i][n] = 0;
        }
    }
    for(int i = colSize - 2; i >= 0; --i){
        dp[m][i] = dp[m][i + 1] - dungeon[m][i + 1];
        if(dp[m][i] < 0){
            dp[m][i] = 0;
        }
    }
    
    for(int i = dungeonRowSize - 2; i >= 0; --i){
        for(int j = colSize - 2; j >= 0; --j){
            dp[i][j] = Min2(dp[i + 1][j] - dungeon[i + 1][j], dp[i][j + 1] - dungeon[i][j + 1]);
            if(dp[i][j] < 0){
                dp[i][j] = 0;
            }
        }
    }
    /*
    for(int i = 0; i < dungeonRowSize; ++i){
        for(int j = 0; j < colSize; ++j){
            printf("%2d ", dp[i][j]);
        }
        printf("\n");
    }
    */
    
    
    if(dp[0][0] - dungeon[0][0] < 0){
       return 1; 
    }
    return dp[0][0] - dungeon[0][0] + 1;
}
