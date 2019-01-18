/*
 * 稍為研究一下DP的解法
 * 定義DP[i] = {}為一個集合，集合搜集所有以A[i]為結尾的數字
 * 另外len(DP[i]) <= 32且 DP[i] = {{DP[i- 1] | A[i]} , A[i]}
 * 但是這個方法要搭配O(1)的資料儲存法(hashtable)，才能實現O(32*n) = O(n)的時間複雜度
 * 用C刻set有點麻煩，所以本題沒有繼續實做，有空再刻
 */

//version3，一樣會超時，但是只要將兩個掃stack的部分換成hashtable就可以降為O(n)了
int subarrayBitwiseORs(int* A, int ASize) {
    int* stack = (int*)malloc((33 * ASize) * sizeof(int));
    int buff1[33], buff2[33];
    int* preTmp = buff1, *crtTmp = buff2, *tmp;
    int sCnt = 0, pCnt = 0, cCnt, or, flag;
    
    preTmp[pCnt++] = A[0];
    stack[sCnt++] = A[0];
    
    for(int i = 1; i < ASize; ++i){
        cCnt = 0;

        crtTmp[cCnt++] = A[i];
	
	//============================
	//掃stack
        flag = 0;
        for(int k = 0; k < sCnt; ++k){
            if(A[i] == stack[k]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            stack[sCnt++] = A[i];
        }
	//============================
        for(int j = 0; j < pCnt; ++j){
            or = preTmp[j] | A[i];
	
            //===========================
	    //掃crtTmp
            flag = 0;
            for(int k = 0; k < cCnt; ++k){
                if(or == crtTmp[k]){
                    flag = 1;
                    break;
                }
            }
            if(!flag){
                crtTmp[cCnt++] = or;
                
                //掃stack
                flag = 0;
                for(int k = 0; k < sCnt; ++k){
                    if(or == stack[k]){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    stack[sCnt++] = or;
                }
            }    
	    //============================
        }
        tmp = preTmp;
        preTmp = crtTmp;
        crtTmp = tmp;
        pCnt = cCnt;
    }
    return sCnt;
}

/*
 * version2：O(n^3)
 * 依舊time limit exceeded
 * 不過有做一點優化，降為O(n^3)
 * 一列不管有幾個數字，int只有32個bit，
 * or運算只會將0填為1，造成數字越來越大，因此從同一個元素開始的任意子集合，最多只會有31 + 2(全0及全1)種不同數字
 * 因此可以開一個(31*ASize + 2)的buffer，用來存每一個可能出現的新數字
 */

int subarrayBitwiseORs(int* A, int ASize) {
	int or, preNum,cnt = 0, flag;
	int *stack = (int*)malloc(sizeof(int) *(31 * ASize + 2));

	for(int i = 0; i < ASize; ++i){
		or = 0;
		for(int j = i; j < ASize; ++j){
			or |= A[j];
			//第一筆，或是該筆跟前筆不同才需要檢查是否為新數字
			if(j == i || preNum != or){
				flag = 0;
				for(int k = 0; k < cnt; ++k){
					if(stack[k] == or){
						flag = 1;
						break;
					}
				}
				if(!flag){
					stack[cnt++] = or;
				}
			}
			preNum = or;
			//已經被1填滿的數字，沒有再往下曾加集合的必要
			if(or == 0xffffffff){
				break;
			}
		}    
	}
	return cnt;
}



/*
 * version1：O(n^4)
 * 果不其然time limit exceeded
 * 老實說到目前為止還是看不太出來是dp問題
 * 不過還是可以做一點優化，降為O(n^3)
 * 一列不管有幾個數字，int只有32個bit，
 * or運算只會將0填為1，造成數字越來越大，因此每一列了不起只會有31 + 2(全0及全1)種不同數字
 * 因此可以開一個(31*ASize + 2)的buffer，用來存每一個新的數字
 */
int subarrayBitwiseORs(int* A, int ASize) {
    int or, cnt = 0, flag;
    int **dp = (int**)malloc(sizeof(int*) * ASize);
    for(int i = 0; i < ASize; ++i){
        dp[i] = (int*)malloc(sizeof(int) * ASize);
    }
    for(int i = 0; i < ASize; ++i){
        or = 0;
        for(int j = i; j < ASize; ++j){
            or |= A[j];
            dp[i][j] = or;
            if(j == i || or != dp[i][j - 1]){
                flag = 0;
                for(int k = 0; k < i; ++k){
                    for(int q = k; q < ASize; ++q){
                        if(or == dp[k][q]){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1){
                        break;
                    }
                }
                if(flag == 0){
                    ++cnt;
                }
            }
        }    
    }
    return cnt;
}
