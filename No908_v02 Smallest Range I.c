/**
 * 給定一個整數陣列A，以及一個整數K
 * 令B[i] = A[i] + x， K <= x <= K
 * 試問B陣列的最大值及最小值，可行的最短距離為
 */

/**
 * version2, 8ms, 75%
 * 改了一些小細節
 */
int smallestRangeI(int* A, int ASize, int K) {
    int maxNum = A[0], minNum = A[0];
    int delta;
    for(int i = 1; i < ASize; ++i){
        if(maxNum < A[i]){
            maxNum = A[i];
        }
        if(minNum > A[i]){
            minNum = A[i];
        }
    }
    delta = maxNum - minNum - (K << 1);
    return delta > 0 ? delta : 0;
}


/**
 * version1, 8ms, 75%
 * 這題明顯的只要找A的最大值及最小值
 * 然後比較這兩個值經過變換後的最小距離就夠了
 */
int smallestRangeI(int* A, int ASize, int K) {
    int maxNum = A[0], minNum = A[0];
    int delta;
    for(int i = 1; i < ASize; ++i){
        if(maxNum < A[i]){
            maxNum = A[i];
        }
        if(minNum > A[i]){
            minNum = A[i];
        }
    }
    delta =maxNum - minNum - 2 * K;
    if(delta <= 0){
        return 0;
    }
    return delta;
}
