
/**
 * version2
 * 將使用的buffer進一步優化
 * 額外省去複製部分資料和交換的時間
 */
int change(int amount, int* coins, int coinsSize) {
    if(amount == 0){
        return 1;
    }
    
    int *crtCnt, crtCoin;
    crtCnt = (int*)calloc((amount + 1), sizeof(int));
    
    crtCnt[0] = 1;
    for(int i = 0; i < coinsSize; ++i){
        crtCoin = coins[i];
        for(int j = crtCoin; j <= amount; ++j){
            crtCnt[j] += crtCnt[j - crtCoin];
        }
    }
    return crtCnt[amount];
}

/**
 * version1
 * 硬幣的路徑問題
 * 前一題問的是最少硬幣數需要額外比較硬幣數量大小，初始值也要小心
 * 本題問全部可行路徑比較單純
 */
int change(int amount, int* coins, int coinsSize) {
    if(amount == 0){
        return 1;
    }
    
    int *preCnt, *crtCnt, *tmp, crtCoin, minNum = INT_MAX;
    
    preCnt = (int*)calloc((amount + 1), sizeof(int));
    crtCnt = (int*)calloc((amount + 1), sizeof(int));
    
    preCnt[0] = 1;
    for(int i = 0; i < coinsSize; ++i){
        crtCoin = coins[i];
        for(int j = 0; j < crtCoin && j <= amount; ++j){
            crtCnt[j] = preCnt[j];
        }
        
        for(int j = crtCoin; j <= amount; ++j){
            crtCnt[j] = crtCnt[j - crtCoin] + preCnt[j];
        }
        tmp = preCnt;
        preCnt = crtCnt;
        crtCnt = tmp;
    }
    return preCnt[amount];
}
