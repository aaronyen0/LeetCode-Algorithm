/**
 * 任三個數字相加
 * 離target最近的數字和為多少
 */


/**
 * version1, 4ms, beats 100%
 * 核心寫法和第15題 3Sum一樣，都是去逼近指定的數字
 * 給定一個排序好的數字
 * 再給兩個index分別在陣列最左端(j)和最右端(k)
 * 若nums[j] + nums[k] > remain，則k--
 * 若nums[j] + nums[k] < remain，則j++
 */


void swap(int* a, int* b);
void quicksort3(int *data, int left, int right);
int BinarySearch(int* arr, int left, int right, int num);
int Abs(int a);


int threeSumClosest(int* nums, int numsSize, int target) {
    int remain, j, k, delta, minDelta = INT_MAX, res;
    
    quicksort3(nums, 0, numsSize - 1);
    for(int i = 0; i < numsSize - 2;){
        
        j = i + 1;
        k = numsSize - 1;
        remain = target - nums[i];
        while(j < k){
            
            delta = nums[j] + nums[k] - remain;
            if(Abs(delta) < minDelta){
                minDelta = Abs(delta);
                res = target + delta;
            }
            
            if(delta > 0){
                --k;
                continue;
            }else if(delta < 0){
                ++j;
                continue;
            }else{
                return target;
            }

        }
        
        do{//同個位置跟上輪選一樣就pass
            ++i;
        }while(nums[i] == nums[i - 1]);
    }
    
    return res;    
}


int Abs(int a){
    if(a < 0){
        return -a;
    }
    return a;
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
