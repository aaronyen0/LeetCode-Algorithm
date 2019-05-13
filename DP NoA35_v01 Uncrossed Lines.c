/**
 * version1, beats 100%
 * 給兩個整數陣列，分成兩排
 * 將同數字的格子一對一連起來
 * 但是連起來的線不能交錯
 */

/**
 * version1, beats 100%
 * 其實這題等價於Longest Common Sunsequence(LCS)
 * 通常的解法是一個DP問題
 * 有點像是knapsack問題
 * 但要多buffer左上方的數字
 * 雖然version1就100%，但是我事先就作弊知道是LCS問題
 * 憑空想其實相當困難，有空絕對要回來重看這題
 */


int maxUncrossedLines(int* A, int ASize, int* B, int BSize){
    int buff[500 + 1] = {0};
    int maxLen = 0;
    int tmpLT, tmp;
    
    for(int j = 0; j < BSize; ++j){
        tmpLT = buff[0];
        for(int i = 0; i < ASize; ++i){
            tmp = buff[i + 1];
            if(B[j] == A[i]){
                buff[i + 1] = tmpLT + 1;
                if(buff[i + 1] > maxLen){
                    maxLen = buff[i + 1];
                }
            }else{
                if(buff[i] > buff[i + 1]){
                    buff[i + 1] = buff[i];
                }
            }
            tmpLT = tmp;
        }    
    }
    return maxLen;
}
