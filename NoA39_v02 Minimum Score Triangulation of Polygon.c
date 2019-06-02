/**
 * 給一個多邊形
 * 每個頂點有一個正整數
 * 將這個多邊形切割成三角網格
 * 找出一個切割法
 * 使三角形頂點的乘積和最小
 * 例如，一個四邊形切割成兩個三角形X和Y
 * sum = X[0]*X[1]*X[2] + Y[0]*Y[1]*Y[2]
 * 找出一個切法始上式最小
 */
 



/**
 * version1, 8ms, 35%
 * 明顯是一個DP問題
 * 定義DP[i][j], i < j 為從「頂點i順時針到頂點j」的凸包集合可以形成的最小乘積和
 * 因此DP[2][0]的凸包頂點集合為{2,3,4,5,...,n-1,0}所形成的多邊形
 * 大家都知道假設[i]→[j]只有三個點，dp[i][j]必然為這三個點的乘積和
 * 所有三個點的都搜索過後，可以擴展為四個點的凸包、...
 * 這個版本假設一個集合可以拆成兩個集合dp[i][j]+dp[j][i]
 * 也就是選兩個頂點劃一刀，分成兩個凸包集
 * 將每種切法(i,j)都算一次dp[i][j]+dp[j][i]
 * 便能找到最小的dp[i][j]+dp[j][i]
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
