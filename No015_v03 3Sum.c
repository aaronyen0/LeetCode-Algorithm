/**
  * version3, 48ms beats 100%
  * 參考一下多數的寫法
  * 基本思想跟前一版本很像
  * 不過在第一個數字固定後，後面兩個數字的配對上有些巧思
  * 給定一串數字 a <= b <= c <= d <= e，判斷是否有任兩個數字的和為某定值num
  * 可以從兩側出發：
  * 若 a + e > num 則右邊退一格，改測試 a + d ，...
  * 若 a + e < num 則左邊進一格，改測試 b + e ，...
  * 我一開始也有略想過這個辦法，但是卡在若今天 a + d = num，有沒有可能b + e = num
  * 
  * 簡易證明：
  * 1.若 a + d = num 則 a + e >= num
  * 2.若 b + e = num 則 a + e <= num
  * 若1、2式同時成立，必然有 a + e = num，也隱含了 d = e 且 a = b
  * 在流程中，理所當然a + e會比其他任兩種情境先被檢查，同時題目又有要求不重複集合
  * 因此縱使1、2式同時成立，在此之前就已經有一樣的集合被蒐集過(a,e)，無法再重複加入
  *
  * 另外有上述的想法後，res的returnSize也可以更進一步估計
  * 當第一個數字(假設為第x個, x = 1~n)被選擇後，要從剩下更大數字集合(n - x)中挑兩個不重複數字且等於某定值至多有(n- x)/2種可能
  * summation(x=1~n, (n-x)/2) = n*(n-1)/4
  * 當然這樣還是有點高估的
  */

int** threeSum(int* nums, int numsSize, int* returnSize) {
    int **res = (int**)malloc(sizeof(int*) * numsSize * numsSize >> 2);
    int resOffset = 0, j, k;
    
    quicksort3(nums, 0, numsSize - 1);
    for(int i = 0; i < numsSize - 2 && nums[i] <= 0;){
        j = i + 1;
        k = numsSize - 1;
        while(j < k){
            //printf("i = %d, j = %d, j = %d\n", i, j, k);
            if(nums[i] + nums[j] + nums[k] > 0){
                --k;
                continue;
            }
            if(nums[i] + nums[j] + nums[k] < 0){
                ++j;
                continue;
            }
            res[resOffset] = (int*)malloc(3 * sizeof(int));
            res[resOffset][0] = nums[i];
            res[resOffset][1] = nums[j];
            res[resOffset][2] = nums[k];
            resOffset++;

            do{//同個位置跟上輪選一樣就pass
                ++j;
            }while(j < k && nums[j] == nums[j - 1]);
            do{//同個位置跟上輪選一樣就pass
                --k;
            }while(j < k && nums[k] == nums[k + 1]);
        }
        
        do{//同個位置跟上輪選一樣就pass
            ++i;
        }while(nums[i] == nums[i - 1]);
    }
    *returnSize = resOffset;
    return res;
}


/**
  * version2, 96ms beats 41%
  * 為version1再剪枝
  * 增加右邊界last判斷及break，兩個概念差不多，都是因為數列已排序，所以怎麼挑都必然越來越大
  */
  
void swap(int* a, int* b);
void quicksort3(int *data, int left, int right);
int BinarySearch(int* arr, int left, int right, int num);

int** threeSum(int* nums, int numsSize, int* returnSize) {
    int **res = (int**)malloc(sizeof(int*) * numsSize * numsSize >> 1); //不重複組合的最大可能集合到底怎麼算要再想想
    int resOffset = 0, sum, rv, last;
    
    quicksort3(nums, 0, numsSize - 1);
    for(int i = 0; i < numsSize - 2 && nums[i] <= 0; ++i){
        if(i > 0 && nums[i] == nums[i - 1]){//同個位置跟上輪選一樣就pass
            continue;
        }
        
        last = numsSize - 1;
        for(int j = i + 1; j < numsSize - 1; ++j){
            if(j > i + 1 && nums[j] == nums[j - 1]){//同個位置跟上輪選一樣就pass
                continue;
            }
            sum = -(nums[i] + nums[j]);
            
            if(nums[j + 1] > sum){//若剩下的陣列數字都大過sum也不用找了
                break;
            }
            rv = BinarySearch(nums, j + 1, last, sum);
            if(rv != -1){
                res[resOffset] = (int*)malloc(3 * sizeof(int));
                res[resOffset][0] = nums[i];
                res[resOffset][1] = nums[j];
                res[resOffset][2] = nums[rv];
                resOffset++;
                last = rv - 1; //下一次sum的數字必然更大，所以若這輪能找到數字，下輪搜尋的右邊界必然是往內縮的
            }
        }
    }
    *returnSize = resOffset;
    return res;
}

int BinarySearch(int* arr, int left, int right, int num){
	int mid;
	while (left <= right){
		mid = (right + left) >> 1;
		if (arr[mid] == num){
			return mid;
		}
		 
		if (arr[mid] > num){
			right = mid - 1;
		}else{
			left = mid + 1;
		}
	}
	return -1;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort3(int *data, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right){
            if (data[i] >= pivot){
                break;
            }
            ++i;
        }

        while (j > left){
            if (data[j] < pivot){
                break;
            }
            --j;
        }

        if (i > j) { 
            break; 
        }
        swap(&data[i], &data[j]);
    }

    swap(&data[left], &data[j]);

    quicksort3(data, left, j - 1);
    quicksort3(data, j + 1, right);
}
