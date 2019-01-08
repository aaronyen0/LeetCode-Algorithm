/**
 *硬幣問題
 *是一個稍微麻煩一點的Knapsack問題
 *主要麻煩在背包問題是不等式，只要小於等於的case都可以放在同一格
 *硬幣問題是等式必須剛好相等，所以要額外一些非0判斷
 *
 *核心觀念為不斷紀錄當前集合中，各種可行價格的最小的硬幣和
 *要小心幾個狀況：
 *1.coins[i] > amount
 *2.amount == 0
 */

/**
 *version2
 *16ms, beat 70%
 *這版亮點在直接交換preCnt和crtCnt，毋須多花功夫做誰是下輪的crCnt判斷
 *
 *可能判斷式還是太多，也不知道還有哪裡可以省略，要參考一下別人的
 */
int coinChange(int* coins, int coinsSize, int amount) {
    if(amount == 0){
        return 0;
    }
    
    int *preCnt, *crtCnt, *tmp, crtCoin, minNum = INT_MAX;
    
    preCnt = (int*)calloc((amount + 1), sizeof(int));
    crtCnt = (int*)calloc((amount + 1), sizeof(int));
    
    for(int i = 0; i < coinsSize; ++i){
        crtCoin = coins[i];
        for(int j = 0; j < crtCoin && j <= amount; ++j){
            crtCnt[j] = preCnt[j];
        }
        if(crtCoin <= amount){
            crtCnt[crtCoin] = 1;
            for(int j = crtCoin + 1; j <= amount; ++j){
                if(crtCnt[j - crtCoin] && preCnt[j]){
                    crtCnt[j] = Min2(crtCnt[j - crtCoin] + 1, preCnt[j]);
                }else if(crtCnt[j - crtCoin]){
                    crtCnt[j] = crtCnt[j - crtCoin] + 1;
                }else{
                    crtCnt[j] = preCnt[j];
                }
            }
            if(crtCnt[amount] && crtCnt[amount] < minNum){
                minNum = crtCnt[amount];
            }
            tmp = preCnt;
            preCnt = crtCnt;
            crtCnt = tmp;
        }
    }
    if(minNum == INT_MAX){
        return -1;
    }
    return minNum;
}


/**
 *version01
 *32ms, beat 17%
 *二維陣列count[i][j]用來記錄：使用前i種硬幣下，實現價格j，用的最少硬幣數為
 *最近突然開竅，發現Knapsack問題根本也是路徑問題，只是沒有路徑問題直覺
 *
 *假設i從上而下增加硬幣，j從左而右增加金額
 *滿足count[i][j]的可能路徑只有來自count[i][j - coins[i]]或是count[i - 1][j]
 *只要選擇小的
 *其實紀錄count的buffer可以只需要兩行(前一輪+當前一輪，能否一行我還在想)
 *這一版本為了概念清楚所才開成 N * M 的二維陣列
 */
int coinChange(int* coins, int coinsSize, int amount) {
    if(amount == 0){
        return 0;
    }
    
    int minNum = INT_MAX, crtCoin;
    int **count = (int**)malloc(sizeof(int*) * (coinsSize + 1));
    for(int i = 0; i <= coinsSize; ++i){
        count[i] = (int*)calloc((amount + 1), sizeof(int));
    }

    
    for(int i = 1; i <= coinsSize; ++i){
        crtCoin = coins[i - 1];
        if(crtCoin > amount){
            for(int j = 0; j <= amount; ++j){
                count[i][j] = count[i - 1][j];
            }
        }else{
            if(count[i][crtCoin] != 1){
                count[i][crtCoin] = 1;        
            }

            for(int j = 0; j < crtCoin; ++j){
                count[i][j] = count[i - 1][j];
            }
            
            for(int j = crtCoin + 1; j <= amount; ++j){
                if(count[i][j - crtCoin] && count[i - 1][j]){
                    count[i][j] = Min2(count[i][j - crtCoin] + 1, count[i - 1][j]);
                }else if(count[i][j - crtCoin]){
                    count[i][j] = count[i][j - crtCoin] + 1;
                }else if(count[i - 1][j]){
                    count[i][j] = count[i - 1][j];
                }
            }
        }
    }
    
    
    for(int i = 0; i <= coinsSize; ++i){
        if(count[i][amount] != 0 && count[i][amount] < minNum){
            minNum = count[i][amount];
        }
    }
    
    if(minNum == INT_MAX){
        return -1;
    }
    return minNum;                                  
}


int Min2(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}
