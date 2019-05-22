/**
 * version3, 平均O(nlogn), worst case O(n^2), 超時
 * 後綴數組改編而來，概念是不斷的往下拆解字串
 */

/*簡易說明
example: banana

step1:拆解成後綴數
banana
anana
nana
ana
na
a

step2:只針對首位字元排序，首位字元只有三種可能，依此分成三組，每組各自進遞迴
## group1:
"anana"
"ana"
"a"

## group2:
"banana"

## group3:
"nana"
"na"

step3:每個字串進一格，這演算法的精神就是，只要你還在同一組，代表截至目前為止前面的字元都相同
## group1:
"nana"
"na"
""

## group2:
"anana"

## group3:
"ana"
"a"

step4:分組進行排序，回到step1
*/

void ClassifyStrArr(char** strArr, char** buff, int l, int r, int crtDepth, int* maxDepth, char** maxPtr);

char * longestDupSubstring(char * S){
    int maxDepth = 0;
    char* maxPtr, *res;
    
    int sLen = strlen(S);
    char** buff1 = (char**)malloc(sizeof(char*) * sLen);
    char** buff2 = (char**)malloc(sizeof(char*) * sLen);
    
    for(int i = 0; i < sLen; ++i){
        buff1[i] = &S[i];
    }
    ClassifyStrArr(buff1, buff2, 0, sLen - 1, 0, &maxDepth, &maxPtr);
    res = (char*)malloc(sizeof(char) * (maxDepth + 1));
    
    //printf("%s, %d\n",maxPtr,maxDepth);
    maxPtr -= maxDepth;
    memcpy(res, maxPtr, maxDepth);
    res[maxDepth] = 0;
    
    return res;

}


void ClassifyStrArr(char** strArr, char** buff, int l, int r, int crtDepth, int* maxDepth, char** maxPtr){
	if(crtDepth > *maxDepth){
		*maxDepth = crtDepth;
		*maxPtr = strArr[l];
	}
	int counting[26] = {0};
	int shift[26] = {0};
	int offsetArr[26] = {0};
	
	int dupNum, offset;
	char* ptr;
	int i;
	
	//printf("======= %d ======\n", crtDepth);
	//TestStrPtr(&strArr[l], r - l + 1);
    
	//計算counting
	i = l;
	while(i <= r){
		if(strArr[i][0] != 0){
			counting[strArr[i][0] - 'a']++;
            ++i;
		}else{
			strArr[i] = strArr[r];
			r--;
		}
	}
	
	//計算每組offset，把沒有兩個以上的排除
	offset = l;
	for(i = 0; i < 26; ++i){
		offsetArr[i] = offset;
		if(counting[i] > 1){
			offset += counting[i];
		}else{
			counting[i] = 0;
		}
	}
	/*
	for(int i = 0; i < 3; ++i){
		printf("count[%d] = %d, offset[%d] = %d\n", i, counting[i], i , offsetArr[i]);
	}
	*/
	//把指標塞到另一個buffer上，下一輪把該buffer當作
	dupNum = 0;
	for(i = l; i <= r; ++i){
		ptr = strArr[i];
		offset = ptr[0] - 'a';
		if(counting[offset] == 0){
			continue;
		}
		buff[offsetArr[offset] + shift[offset]] = (++ptr);//丟進下一層時，記得把指標移到下一格
		shift[offset]++;
		dupNum++;
	}
	
	//看看能不能進下一層遞迴
	if(!dupNum){
		return;
	}
	for(i = 0; i < 26; ++i){
		if(counting[i] > 1){
			ClassifyStrArr(buff, strArr, offsetArr[i], offsetArr[i] + counting[i] - 1, crtDepth + 1, maxDepth, maxPtr);
		}
	}
}

/**
 * version2, O(n^2), 超時
 * 前同事提出的方法
 * 移動字串，求每組overlap的最長的連續子字串
 */

char * longestDupSubstring(char * S){
    int overlapLen = strlen(S);
    char* str2 = S;
    int l, r;
    int maxContLen = 0;
    char* maxPtr;
    char* res;
    while(--overlapLen > 0){
        if(maxContLen >= overlapLen){
            break;
        }
        str2++;
        l = 0;
        r = 0;
        //printf("overlapLen = %d, str = %s\n", overlapLen, str2);
        for(int i = 0; i < overlapLen; ++i){
			  //printf("#### l = %d, r = %d\n", l ,r);
            if(S[i] == str2[i]){
                r++;
            }else{
                if(r - l > maxContLen){
                    maxContLen = r - l;
                    maxPtr = &str2[l];
                }
                l = i + 1;
                r = i + 1;
                if(overlapLen - l <= maxContLen){
                    break;
                }
            }
        }
        if(r - l > maxContLen){
            maxContLen = r - l;
            maxPtr = &str2[l];
        }
    }

    res = (char*)malloc(sizeof(char) * (maxContLen + 1));
    memcpy(res, maxPtr, maxContLen);
    res[maxContLen] = 0;
    return res;

}

/**
 * version1, n*n*log(n), 超時
 * 對suffix排序之後相鄰字串檢查
 */

void Swap(int* a, int* b);
void QuickSort3(char* str, int *data, int left, int right);

void TestSuffixArray(char* str, int* suffixArray, int len){
    for(int i = 0; i < len; ++i){
        printf("%s\n", &str[suffixArray[i]]);
    }
}


char * longestDupSubstring(char * S){
    int len = strlen(S);
    int* suffixArray = (int*)malloc(sizeof(int) * len);
    int maxDupLen = 0, crtLen, maxIdx, startIdx1, startIdx2;
    char* res;
    
    for(int i = 0; i < len; ++i){
        suffixArray[i] = i;
    }
    QuickSort3(S, suffixArray, 0, len - 1);//Create SuffixArray
    //TestSuffixArray(S, suffixArray, len);
    for(int i = 0; i < len - 1; ++i){
        crtLen = 0;
        startIdx1 = suffixArray[i];
        startIdx2 = suffixArray[i + 1];
        while(S[startIdx1 + crtLen] == S[startIdx2 + crtLen]){
            crtLen++;
        }
        if(crtLen > maxDupLen){
            maxDupLen = crtLen;
            maxIdx = suffixArray[i];
        }
    }
    
    res = (char*)malloc(sizeof(char)* (maxDupLen + 1));
    memcpy(res, &S[maxIdx], maxDupLen);
    res[maxDupLen] = 0;
    return res;
}

    

void QuickSort3(char* str, int *data, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;
    
    int strLIdx, strRIdx, strPivotIdx = data[left];

    while (1){
        //printf("%d, %d, %d\n", i, j, pivot);
        while (i <= right){
            strLIdx = data[i];
            //printf("%s\n%s\n", str[strLIdx], str[strPivotIdx]);
            if(strcmp(&str[strLIdx], &str[strPivotIdx]) >= 0){
                break;
            }
            ++i;
        }

        while (j > left){
            strRIdx = data[j];
            //printf("%s\n%s\n", str[strRIdx], str[strPivotIdx]);
            if(strcmp(&str[strRIdx], &str[strPivotIdx]) < 0){
                break;
            }
            --j;
        }

        if (i > j) { 
            break; 
        }
        Swap(&data[i], &data[j]);
    }

    Swap(&data[left], &data[j]);

    QuickSort3(str, data, left, j - 1);
    QuickSort3(str, data, j + 1, right);
}

void Swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
