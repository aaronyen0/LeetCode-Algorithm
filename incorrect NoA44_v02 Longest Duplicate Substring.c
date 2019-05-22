

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
