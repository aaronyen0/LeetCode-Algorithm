/**
 * 這題應該是目前寫過最難的DP題目
 * 給定兩個陣列nums1及nums2
 * 希望從兩個陣列當中不重複的挑出一些值，組成長度為k的最大數字
 * 另外可以從nums1, nums2中交錯挑數字，但從同一邊挑出的數字必須要保持原本的順序
 * 例如 nums1 = {5,1,2, 8}, nums2 = {4}, k = 3
 * res = {5,8,4} ， 5和8皆為nums1選出的數字，5必須放在8前面
 */

/**
 * version1, 4ms beats 100%
 * 很有難度，方法不是我想的，構思來自於下面連結
 * https://www.youtube.com/watch?v=YYduNJfzWaA&t=0s&list=PLLuMmzMTgVK7vEbeHBDD42pqqG36jhuOr&index=50
 * 這題主要在解決兩個問題：
 *
 * 1.從「單一陣列」中保持順序(可跳號)挑選數字，組成一個特定長度的最大數字
 * 例如：{8,9,4,7,4,5} 挑出4個數字，代表最多可以pop兩個數字，令popCnt = 2
 * 演算法：若popCnt還有剩，且新的數字比stack[top]大，則pop
 * 本例 push(8), pop(8) [popCnt = 1] , push(9,4), pop(4) [popCnt = 0] , push(7,4,5)
 * 因此 res = {9,7,4,5}
 *
 * 2.給定兩個陣列，將之合併成最大數字(對同一陣列而言順序不能亂)
 * 寫法類似mergesort的merge
 * 但是數字相等時特別麻煩，要往後檢查看看先走哪一邊效益比較高
 * 具體來說就是，先遇到數字更大的先走，若剩餘可檢查數字都相同則長度更長的先走
 *
 * 有了1和2之後
 * 令k = len1 + len2
 * 對每個len1及len2檢查構築出來的array是否最大
 */
 
 

//for debug
void PrintStack(int* stack, int size, int num);
void PrintMerge(int* merge, int size);

int Min2(int a, int b);
int Max2(int a, int b);
int lexicographical(int* arr1, int len1, int* arr2, int len2);

int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
    int *stack1 = (int*)malloc(sizeof(int) * nums1Size);
    int *stack2 = (int*)malloc(sizeof(int) * nums2Size);
    int *res = (int*)calloc(k, sizeof(int));
    int *buff = (int*)malloc(sizeof(int) * k);
    int len1, len2, popCnt, top1, top2, idx1, idx2, offset, *tmp;
    
    int minLen = Max2(k - nums2Size, 0);
    int maxLen = Min2(k, nums1Size);
    
    //測試每一個 k = len1 + len2 且 0 <= len1 <= nums1Size 且 0 <= len2 <= nums2Size，
    //所以 max(k - nums2Size, 0) <= len1 <= min(nums1Size, k)
    for(len1 = minLen, len2 = k - len1; len1 <= maxLen; ++len1, --len2){
        //從nums1中抓出長度為len1的最大數字
        popCnt = nums1Size - len1;
        top1 = -1;
        for(int i = 0; i < nums1Size; ++i){
            while(top1 > -1 && popCnt > 0 && nums1[i] > stack1[top1]){
                --top1;
                --popCnt;
            }
            stack1[++top1] = nums1[i];
        }
        //PrintStack(stack1, len1, 1);
     
        //從nums2中抓出長度為len2的最大數字
        popCnt = nums2Size - len2;
        top2 = -1;
        for(int i = 0; i < nums2Size; ++i){
            while(top2 > -1 && popCnt > 0 && nums2[i] > stack2[top2]){
                --top2;
                --popCnt;
            }
            stack2[++top2] = nums2[i];
        }
        //PrintStack(stack2, len2, 2);
     
        //將stack1及stack2合併成一個最大數字
        idx1 = 0;
        idx2 = 0;
        offset = 0;
        int i1, i2, flag;
        while(idx1 < len1 && idx2 < len2){
            if(lexicographical(&stack1[idx1], len1 - idx1, &stack2[idx2], len2 - idx2) == 0){
                buff[offset++] = stack1[idx1++];
            }else{
                buff[offset++] = stack2[idx2++];
            }
            //printf("idx1 = %d, idx2 = %d\n", idx1, idx2);
        }
        while(idx1 < len1){
            buff[offset++] = stack1[idx1++];
        }
        while(idx2 < len2){
            buff[offset++] = stack2[idx2++];
        }
        
        //檢查新的數字有沒有比既有的來的大，有的話交換buffer
        for(int i = 0; i < k; ++i){
            if(buff[i] > res[i]){
                tmp = buff;
                buff = res;
                res = tmp;
                break;
            }else if(buff[i] == res[i]){
                continue;
            }else{
                break;
            }
        }
        //PrintMerge(buff, k);
        //PrintMerge(res, k);
        
    }
    free(buff);
    free(stack1);
    free(stack2);
    
    *returnSize = k;
    return res;
}


int Min2(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

int Max2(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

int lexicographical(int* arr1, int len1, int* arr2, int len2){
    int i = 0;
    while(i < len1 && i < len2){
        if(arr1[i] > arr2[i]){
            return 0;
        }else if(arr1[i] < arr2[i]){
            return 1;
        }
        ++i;
    }
    if(len1 > len2){
        return 0;
    }
    return 1;
}


void PrintStack(int* stack, int size, int num){
    printf("stack[%d] ", num);
    for(int i = 0; i < size; ++i){
        printf("%d, ", stack[i]);
    }
    printf("\n");
}

void PrintMerge(int* merge, int size){
    printf("MergeArray ");
    for(int i = 0; i < size; ++i){
        printf("%d, ", merge[i]);
    }
    printf("\n");
}
