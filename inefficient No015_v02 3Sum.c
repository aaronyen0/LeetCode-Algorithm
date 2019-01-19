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
