

/**
 * version2 28ms, beats 86%
 * 寫過sum3後再回來看這題的，發現我一直都有點太依賴hashtable
 * 雖然這題用hashtable能達100%，但它的限制也很明顯
 * 以後要盡量想非hashtable的方法
 */
void quicksort3(int *data, int *index, int left, int right);

int* twoSum(int* nums, int numsSize, int target) {    
    int j, k;
    int *res = (int*)malloc(2 * sizeof(int));
    int* index = (int*)malloc(numsSize * sizeof(int));
    for(int i = 0; i < numsSize; ++i){
        index[i] = i;
    }
    quicksort3(nums, index, 0, numsSize - 1);
    
    j = 0, k = numsSize - 1;
    while(j < k){
        if(nums[j] + nums[k] < target){
            ++j;
            continue;
        }
        if(nums[j] + nums[k] > target){
            --k;
            continue;
        }
        res[0] = index[j];
        res[1] = index[k];
        break;
    }
    return res;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort3(int *data, int *index, int left, int right)
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
        swap(&index[i], &index[j]);
    }

    swap(&data[left], &data[j]);
    swap(&index[left], &index[j]);

    quicksort3(data, index, left, j - 1);
    quicksort3(data, index, j + 1, right);
}

//version1
int* twoSum(int* nums, int numsSize, int target) {
    int* res = (int*)malloc(sizeof(int) * 2);
    for(int i = 0; i < numsSize; ++i){
        for(int j = i + 1; j < numsSize; ++j){
            if(nums[i] + nums[j] == target){//應該要改成檢查nums[j] == dis，其中dis = target - nums[i]才不會一直重算這一步
                res[0] = i;
                res[1] = j;
                return res;
            }
        }    
    }
    return NULL;
}

//這是別人的寫法
//我也有一版跟這個很像，不過這個寫法顯然更精闢
//重點在這段 map[nums[i]-min] = ++i
//讓儲存的index至少從1開始，因此配記憶體時就能用calloc初始化為0
//我的寫法是 map[nums[i]-min] = i 因為i可以是0，所以配完記憶體還加一個迴圈將陣列初始化為-1
//另外明明配置記憶體一樣大，但是「我用malloc + for迴圈初始化」會遇到Memory Limit Exceeded的錯誤 (在min, max級距很大時)

int* twoSum2(int* nums, int numsSize, int target) {
    int i, max, min;
    max = min = nums[0];
    for(i = 0; i < numsSize; i++) {
        if(nums[i] > max) max = nums[i];
        if(nums[i] < min) min = nums[i];
    }
    
    int *map   = (int*)calloc((max-min+1), sizeof(int));
    int *reval = (int*)malloc(sizeof(int)*2);
    
    for(i = 0; i < numsSize; map[nums[i]-min] = ++i) {
        int lookfornum = target - nums[i];
        if(lookfornum < min || lookfornum > max) continue;
        int dis = lookfornum - min;
        if (map[dis]) {         
            reval[0] = i;
            reval[1] = map[dis] -1;
            break;
        }
    }
    
    return reval;
}
