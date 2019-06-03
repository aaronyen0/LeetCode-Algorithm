/**
 * 給一個整數陣列
 * 將陣列重排讓相鄰兩個數字不相同
 */
 
/**
 * version2, 172ms, beats 100%
 * 將整數從個數多排到個數少
 * 然後逐一塞到res(有空一格塞，塞到底就回去填空)
 * 雙重couting sort搞得很混亂
 */
 
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize){
    int idx = 0, cnt = 0, offset;
    int count[10001] = {0};
    int doubleCnt[5001] = {0};
    int cntOffset[5001] = {0};
    int number[10001];
    int maxNum = 0;
    int idx1 = 0, idx2 = (barcodesSize + 1) >> 1;
    int *res = (int*)malloc(sizeof(int) * barcodesSize);
    
    //紀錄每個數字出現的次數
    for(int i = 0; i < barcodesSize; ++i){
        count[barcodes[i]]++;
        if(barcodes[i] > maxNum){
            maxNum = barcodes[i];//剪枝用，buffer雖然開很大，不過實際上用不到這麼多
        }
    }
    
    //紀錄每個次數出現的次數
    for(int i = 0; i <= maxNum; ++i){
        if(count[i]){
            doubleCnt[count[i]]++;            
        }
    }
    
    //從次數大的開始更新offset，例如次數4有2個，則次數4會占用4*2格，因此下一個人的offset從+8之後開始
    for(int i = 5000; i >= 0; --i){
        if(doubleCnt[i]){
            cntOffset[i] = cnt;
            cnt += (i * doubleCnt[i]);
        }
    }
    
    //當看到某個次數，就應該能取得他的offset，及這個數字的次數，連續填入number中
    for(int num = 0; num <= maxNum; ++num){
        cnt = count[num];
        if(cnt){
            offset = cntOffset[cnt];
            for(int j = offset; j < offset + cnt; ++j){
                number[j] = num;
            }
            cntOffset[cnt] += cnt;
        }
    }
    
    //最後則是塞res
    for(int i = 0, j = 1; j < barcodesSize; i += 2, j += 2){
        res[i] = number[idx1++];
        res[j] = number[idx2++];
    }
    if(barcodesSize&1){
        res[barcodesSize - 1] = number[idx1];
    }
    
    *returnSize = barcodesSize;
    return res;
}

/**
 * version1, 超時
 * 將整數從個數多排到個數少
 * 然後逐一塞到res(有空一格塞，塞到底就回去填空)
 * 顯染Qsort不適合這題，重複數字太多
 */

void Swap(int* a, int* b);
void QuickSort3(int *data, int *number, int left, int right);
    
    
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize){
    int idx = 0;
    int count[10001] = {0};
    int number[10001];
    int maxNum = 0;
    int *res = (int*)malloc(sizeof(int) * barcodesSize);
    
    for(int i = 0; i < barcodesSize; ++i){
        count[barcodes[i]]++;
    }
    for(int i = 0; i < 10001; ++i){
        number[i] = i;
    }
    
    QuickSort3(count, number, 0, 10000);
    
    for(int i = 0; i < 10001; ++i){
        while(count[i]--){
            res[idx] = number[i];
            idx += 2;
            if(idx >= barcodesSize){
                idx = 1;
            }
        }
    }
    
    *returnSize = barcodesSize;
    return res;
}



void Swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void QuickSort3(int *data, int* number, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right){
            if (data[i] < pivot){
                break;
            }
            ++i;
        }

        while (j > left){
            if (data[j] >= pivot){
                break;
            }
            --j;
        }

        if (i > j) { 
            break; 
        }
        Swap(&data[i], &data[j]);
        Swap(&number[i], &number[j]);
    }

    Swap(&data[left], &data[j]);
    Swap(&number[left], &number[j]);

    QuickSort3(data, number, left, j - 1);
    QuickSort3(data, number, j + 1, right);
}
