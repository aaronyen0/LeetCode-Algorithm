/**
 * 找出所有非空連續子集剛好能被K整除的個數
 */
 
/**
 * version4, 16ms, beats 100%
 * O(n + K)
 * 看了別人的解
 * 在這之前我已經發現連加之後，任兩兩被K整除的index間，都有子陣列也被K整除
 * 沒有注意到，任兩兩 mod(A[i,j], K) = q = mod(A[i,m], K)之間
 * 也會有子陣列 A[j+1, m]能被K整除
 * 所以只要從頭連加一次，紀錄mod[0], ... , mod[K-1]的數量
 * 就能得到所有同餘子陣列的數量
 * 要注意邊界mod[0]數量要多1就好
 * 這題真的很漂亮的詮釋了Order的影響力
 */

int subarraysDivByK(int* A, int ASize, int K) {
    int sum = 0, parallel, cnt = 0;
    int *mod = (int*)calloc(K, sizeof(int));
    mod[0] = 1;
    
    for(int i = 0; i < ASize; ++i){
        sum += A[i];
        mod[(sum % K + K) % K]++;
    }
    for(int i = 0; i < K; ++i){
        cnt += (mod[i] * (mod[i] - 1)) >> 1;
    }
    
    return cnt;
}


/**
 * version3, 356ms, beats 0%
 * 基本上同version2
 * 把取餘數的部分替換掉，快了兩倍多
 * 雖然依舊0%
 */
 
 int subarraysDivByK(int* A, int ASize, int K) {
    int sum = 0, parallel, cnt = 0;
    int *table = (int*)calloc(ASize + 1, sizeof(int));
    
    sum = 0;
    parallel = 1;
    for(int i = 0; i < ASize; ++i){
        A[i] = A[i] % K;
        if(A[i] < 0){
            A[i] += K;
        }
        
        sum += A[i];
        if(sum == 0){
            cnt += parallel;
            ++parallel;
            table[i + 1] = 1;
        }else if(sum == K){
            cnt += parallel;
            ++parallel;
            table[i + 1] = 1;
            sum = 0;
        }else if(sum > K){
            sum -= K;
        }
    }
    //printf("i = 0, cnt = %d\n", cnt);
    
    for(int i = 1; i < ASize; ++i){
        if(table[i]){
            continue;
        }
        sum = 0;
        parallel = 1;
        for(int j = i; j < ASize; ++j){
            sum += A[j];
            if(sum == 0){
                cnt += parallel;
                ++parallel;
                table[j + 1] = 1;
            }else if(sum == K){
                cnt += parallel;
                ++parallel;
                table[j + 1] = 1;
                sum = 0;
            }else if(sum > K){
                sum -= K;
            }
        }
        //printf("i = %d, cnt = %d\n", i ,cnt);
    }
    
    return cnt;
}
 
/**
 * version2, 932ms, beats 0%
 * { (A[0] A[1] A[2])  (A[3] A[4] ...) {...} {...}}
 * 假設 (A[0] A[1] A[2]) 是可以被K整除的
 * 因此從A[3]開始又是一個新的檢查
 * 若未來有 (A[0] ~ A[k]) 被整除，代表 A[3] ~ A[k] 也會被整除
 * 因此 cnt += parallel 代表+多少等價得起始點
 * 並用table[3] = 1代表已經在第0列檢查完時，便同步把第3列也檢查完了
 * 不過還是跑很慢
 */
 
int subarraysDivByK(int* A, int ASize, int K) {
    int sum = 0, parallel, cnt = 0;
    int *table = (int*)calloc(ASize + 1, sizeof(int));
    
    sum = 0;
    parallel = 1;
    for(int i = 0; i < ASize; ++i){
        sum += A[i];
        if(sum % K == 0){
            cnt += parallel;
            ++parallel;
            table[i + 1] = 1;
        }
    }
    
    for(int i = 1; i < ASize; ++i){
        if(table[i]){
            continue;
        }
        sum = 0;
        parallel = 1;
        for(int j = i; j < ASize; ++j){
            sum += A[j];
            if(sum % K == 0){
                cnt += parallel;
                ++parallel;
                table[j + 1] = 1;
            }
        }
    }
    
    return cnt;
}


/**
 * version1, 7452ms, beats 0%
 * 另A[i] += A[i - 1];
 * 因此 sum[i:j] = A[j] - A[i - 1];
 * order為O(n^2)
 * 看這時間，如果沒有這步優化的話就time limit exceeded了
 * 後來想到因為每一子陣列都要計算，所以A[i] += A[i - 1]基本上是沒有達到省時效果的
 */
int subarraysDivByK(int* A, int ASize, int K) {
    int sum, cnt;
    for(int i = 1; i < ASize; ++i){
        A[i] += A[i - 1];
    }
    
    for(int i = 0; i < ASize; ++i){
        if(A[i] % K == 0){
            ++cnt;
        }
    }
    
    for(int i = 1; i < ASize; ++i){
        for(int j = i; j < ASize; ++j){
            if((A[j] - A[i - 1]) % K == 0){
                ++cnt;
            }
        }
    }
    
    return cnt;
    
}
