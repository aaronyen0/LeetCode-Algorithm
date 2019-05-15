/**
 * 給一個整數陣列
 * 陣列中所有的元素都大於0
 * 假設這個陣列長度代表一個凸包(convex)多邊形邊頂點的數量
 * 而陣列中對應的數字，則依序(順時針方向)代表每個頂點的數字
 * 將多邊形切成三角型的組合
 * 假設其中一個三角形的三個頂點數字分別為 x, y ,z
 * 則將之相乘起來 x*y*z 
 * 試問如何切割多邊形，才能讓所有三角形的乘機和最小
 */

/**
 * version2, 0ms, beats 100%
 * 這個寫法是參考別人的，
 * 前半段幾乎跟version1一樣
 * 但是顯然version1的寫法有太多重複運算的部分
 * 當然這也跟我對dp的定義有關
 * 同樣定義dp[i][j]是從i出發遶順時針到j的多邊形的最小數字
 * 但是我前面的dp[i][j]，都假定i和j是不相鄰的
 * 因此假設n = 5，至多到dp[0][3]，
 * 但是本例的dp[0][4]是可行的，
 * 而這裡從0出發到4的多邊形就是整個最大的多邊形
 * 因此dp[0][4]本身就是解
 * 另外version1對角線上下每一格我都有運算
 * 看version2後發現其實都是多算了
 * 雖然都是O(n^3)，但整體運算量差距還是頗大
 */


int minScoreTriangulation(int* A, int ASize){
    if(ASize == 3){
        return A[0] * A[1] * A[2];
    }
    
    int j, tmpLine, tmpMin, crtVal;
    int** dp = (int**)malloc(sizeof(int*) * ASize);
    for(int i = 0; i < ASize; ++i){
        dp[i] = (int*)calloc(ASize + 1, sizeof(int));
    }
    
    for(int step = 2; step < ASize; ++step){
        for(int i = 0; i + step < ASize; ++i){
            j = i + step;
            //printf("%d, %d\n",i , j);
            tmpMin = INT_MAX;
            tmpLine = A[i] * A[j];
            for(int k = i + 1; k < j; ++k){
                crtVal = tmpLine * A[k] + dp[i][k] + dp[k][j];
                if(crtVal < tmpMin){
                    tmpMin = crtVal;
                }
            }
            dp[i][j] = tmpMin;
        }
    }
    
    return dp[0][ASize - 1];
}

/**
 * version1, 8ms, beats 35%
 * 首先我事先就知道這題是dp問題
 * 不過寫之前沒有去看別人怎麼做的
 * 假設陣列長度為n，我定義dp為一個n*n矩陣
 * dp[i][j]代表從i點順時針出發，到j點的多邊形，最小的三角形乘積數字和為
 * dp[j][i]代表從j點順時針出發，到i點的多邊形，最小的三角形乘積數字和為
 * 因此dp[i][j] + dp[j][i]則表示，將多邊形依照i-j的連線切成兩塊，兩塊各自的最小乘機和再相加
 * 因此當遍歷所有的dp[i][j] + dp[j][i]組合，數字最小的就是答案，
 * 這邊的i j至少中間還隔一個數字，也就是兩塊各自能組成三角型
 * 至於dp[i][j]在塞值的過程則是靠近對角線的先算
 * dp[0][0 + 2], dp[1][1 + 2], dp[2][2 + 2], dp[3][3 + 2], dp[4][4 + 2], ... 
 * (如果 j >= ASize 則 j -= ASize，如上例本來要dp[5][7]，若7就是ASize則填至dp[5][0]
 * 接著換dp[0][0 + 3], dp[1][1 + 3], dp[2][2 + 3], dp[3][3 + 3], dp[4][4 + 3 - 7], ...
 * 在塞的過程中，舉例來說dp[0][3]可以拆解成dp[0][1] + dp[1][3], dp[0][2] + dp[2][3]兩種去比大小，
 * 就能找出dp[0][3]的最小可能值
 */

int minScoreTriangulation(int* A, int ASize){
    if(ASize == 3){
        return A[0] * A[1] * A[2];
    }
    
    int j, k, tmpLine, tmpMin, crtVal;
    int** dp = (int**)malloc(sizeof(int*) * ASize);
    for(int i = 0; i < ASize; ++i){
        dp[i] = (int*)calloc(ASize, sizeof(int));
    }
    
    for(int step = 2; step < ASize - 1; ++step){
        for(int i = 0; i < ASize; ++i){
            j = i + step;
            if(j >= ASize){
                j -= ASize;
            }
            
                
            tmpMin = INT_MAX;
            tmpLine = A[i] * A[j];
            
            k = i + 1;
            if(k >= ASize){
                k -= ASize;
            }
            while(k != j){
                crtVal = tmpLine * A[k] + dp[i][k] + dp[k][j];
                //printf("---- k = %d, crtVal = %d\n", k, crtVal);
                if(crtVal < tmpMin){
                    tmpMin = crtVal;
                }
                
                if(++k >= ASize){
                    k -= ASize;
                }   
            }
            dp[i][j] = tmpMin;
            //printf("i = %d, j = %d, tmpMin = %d\n", i , j, tmpMin);
        }
    }
    
    
    tmpMin = INT_MAX;
    for(int j = 2; j < ASize - 1; ++j){
        crtVal = dp[0][j] + dp[j][0];
        if(crtVal < tmpMin){
            tmpMin = crtVal;
        }
    }
    for(int i = 1; i < ASize; ++i){
        for(int j = i + 2; j < ASize; ++j){
            crtVal = dp[i][j] + dp[j][i];
            //printf("i = %d, j = %d, %d + %d = %d\n", i , j, dp[i][j], dp[j][i], crtVal);
            if(crtVal < tmpMin){
                tmpMin = crtVal;
            }
        }
    }
    
    return tmpMin;
    
}
