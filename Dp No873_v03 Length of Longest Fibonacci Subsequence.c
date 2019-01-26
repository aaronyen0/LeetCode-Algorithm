/**
 * version3, 108ms beats 81% (把BinarySearch改為hashtable應該就能100%了，暫不實作)
 * 這是參考別人寫法的，定義DP[j][k]如下
 * 當費氏數列的最後一個數字為A[k]且倒數第二個數字為A[j]時
 * 該費氏數列的總長度為多少 Fibb = { ..., A[j], A[k] }
 * 因為費氏數量中任兩相鄰數字確定時，就能造出整個數列
 * 所以可以得到再前一個數字 A[i] = A[k] - A[j]
 * 且A[i][j]儲存 Fibb = { ..., A[i], A[j] }的長度
 */

int lenLongestFibSubseq(int* A, int ASize) {
    int maxLen = 2, ai, rv;
    
    int** dp = (int**)malloc(sizeof(int*) * ASize);
    for(int i = 0; i < ASize; ++i){
        dp[i] = (int*)malloc(sizeof(int) * ASize);
    }
    
    for(int k = 1; k < ASize; ++k){
        for(int j = k - 1; j >= 0; --j ){
            ai = A[k] - A[j];
            if(ai >= A[j]){
                while(j >= 0){
                    dp[j--][k] = 2;
                }
            }else{
                rv = BinarySearch(A, 0, j, ai);
                if(rv == -1){
                    dp[j][k] = 2;
                }else{
                    dp[j][k] = dp[rv][j] + 1;
                }
                if(dp[j][k] > maxLen){
                    maxLen = dp[j][k];
                }
            }
        }
    }
    
    
    
    if(maxLen > 2){
        return maxLen;
    }
    return 0;
}


/**
 * version2, 112ms beats 35%
 * 還是想不到DP版本
 * 不過費氏數列只要前兩筆資料確定
 * 後面全部都是定值
 * 因此問題可以化成：抓出前兩筆後(A[i], A[j])，照數列規則一直往後搜索資料
 * 又題目表示數列嚴格遞增，因此可採用Binary Search搜索剩餘資料
 * 當然如果有hashtable的話可以進一步將搜索效率降為O(1)
 * O(n^2  logn)
 */

int BinarySearch(int* array, int left, int right, int num);

int lenLongestFibSubseq(int* A, int ASize) {
    int maxLen = 0, rv, cnt = 0;
    int pre1, pre2;
    for(int i = 0; i < ASize - 2; ++i){
        for(int j = i + 1; j < ASize - 1; ++j){
            cnt = 0;
            pre1 = A[i];
            pre2 = A[j];
            
            rv = BinarySearch(A, j + 1, ASize - 1, pre1 + pre2);
            while(rv != -1){
                pre1 = pre2;
                pre2 = A[rv];
                ++cnt;
                rv = BinarySearch(A, rv + 1, ASize - 1, pre1 + pre2);
            }
            
            if(cnt > maxLen){
                maxLen = cnt;
            }
        }
    }
    
    
    if(maxLen){
        return maxLen + 2;
    }
    return 0;
}

int BinarySearch(int* array, int left, int right, int num){
    int middle;
	while (left <= right){
                middle = (right + left) >> 1;

                if (array[middle] == num){
                        return middle;
	        }
		
                if (array[middle] > num){
			right = middle - 1;
		}else{
			left = middle + 1;
		}
	}
	return -1;
}


/**
 * version1, DFS 超時
 */
void CheckFibSequence(int* A, int ASize, int idx, int cnt, int pre1, int pre2, int *maxLen){
    for(int i = idx; i < ASize; ++i){
        if(cnt < 2){
            //不選
            CheckFibSequence(A, ASize, i + 1, cnt, pre1, pre2, maxLen);
            //選
            if(cnt == 0){
                CheckFibSequence(A, ASize, i + 1, 1, A[i], pre2, maxLen);
            }else{
                CheckFibSequence(A, ASize, i + 1, 2, pre1, A[i], maxLen);
            }
        }else if(A[i] == pre1 + pre2){
            if(cnt + 1 > *maxLen){
                *maxLen = cnt + 1;
            }
            CheckFibSequence(A, ASize, i + 1, cnt + 1, pre2, A[i], maxLen);
        }
    }
}

int lenLongestFibSubseq(int* A, int ASize) {
    int maxLen = 0;
    CheckFibSequence(A, ASize, 0, 0, 0, 0, &maxLen);
    
    return maxLen;
}
