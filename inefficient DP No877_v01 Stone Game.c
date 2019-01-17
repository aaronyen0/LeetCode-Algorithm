/*
 * 給予好幾堆石頭排成一列(偶數堆)
 * 每堆石頭有不同的石頭量
 * 若兩個人只能從剩餘石頭堆的最左或最右端選取石頭
 * 若兩邊都是夠smart的
 * 回傳首先選擇的人是否會獲勝？
 */
 
/*
 * version1, beat 54%
 * 這題是標準的賽局問題
 * 也有點像是數數字問題(輪流依序數1~3個數字，數到某個特定數字的人輸或贏)
 * 本來第一版想以暴力法創造每種選擇情境，但是想想這樣根本不是「聰明」的選法
 * 後來開始便以如何為聰明構思
 * 大至上的想法就是，在今天這個情境下
 * 選左邊是否最有益，或選右邊才是最有益
 * 選了之後對另一個人來說也會遇到一模一樣的問題
 *
 * 因此定義一個dp[][]
 * dp[i][j]代表從子陣列piles[i:j]選擇的情境，先手的報酬
 * 而這個報酬取決於選某邊之後，其餘部分被優先選的剩餘價值
 * 另外明顯的當陣列長度為1時，dp[i][i] = piles[i]
 * 因此邊界有解，其他解也隨之出來
 * 
 * 下階段可行的一種優化就是減少dp的size，可以只用O(n)
 */
 
int Min2(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

bool stoneGame(int* piles, int pilesSize) {
    int baseSum = piles[0], tmpSum;
    int **dp = (int**)malloc(sizeof(int*) * pilesSize);
    for(int i = 0; i < pilesSize; ++i){
        dp[i] = (int*)malloc(sizeof(int) * pilesSize);
    }
    for(int i = 0; i < pilesSize; ++i){
        dp[i][i] = piles[i];
    }
    
    for(int n = 1; n < pilesSize; ++n){
        baseSum += piles[n];
        tmpSum = baseSum;
        for(int i = 0, j = n; i < pilesSize - n; ++i, ++j){
            dp[i][j] = tmpSum - Min2(dp[i][j - 1], dp[i + 1][j]);
            tmpSum = tmpSum - piles[i] + piles[i + n + 1];
        }
    }
    if(2 * dp[0][pilesSize - 1] > baseSum){
        return true;
    }
    return false;
}
