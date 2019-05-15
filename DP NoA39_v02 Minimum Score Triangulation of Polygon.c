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
 * version1, 8ms, beats 35%
 * 首先我事先就知道這題是dp問題
 * 不過謝之前沒有去看別人怎麼做的
 * 假設陣列長度為n，我定義dp為一個n*n矩陣
 * dp[i][j]代表從i點順時針出發，到j點的多邊形，最小的三角形乘積數字和為
 * dp[j][i]代表從j點順時針出發，到i點的多邊形，最小的三角形乘積數字和為
 * 因此dp[i][j] + dp[j][i]則表示，將多邊形依照i-j的連線切成兩塊，兩塊各自的最小乘機和再相加
 * 因此當遍歷所有的dp[i][j] + dp[j][i]組合，數字最小的就是答案
 * 至於dp[i][j]在塞值的過程則是靠近對角線的先算
 * dp[0][2], dp[1][3], dp[2][4], dp[3][5], dp[4][6], ...
 * dp[0][3], dp[1][4], dp[2][5], dp[3][6], dp[4][7], ...
 * 舉例來說dp[0][3]可以拆解成dp[0][1] + dp[1][3], dp[0][2] + dp[2][3]去比大小
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
