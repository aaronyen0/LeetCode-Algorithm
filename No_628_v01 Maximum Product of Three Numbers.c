//發現數字range有限後就改用counting sort

#define N 2001
#define M 1000
int maximumProduct(int* nums, int numsSize) {
    int max1 = 1, max2 = 1, cnt1 = 2, cnt2 = 3;
    int ht1[N] = {0}, ht2[N] = {0};
    
    for (int i = 0; i < numsSize; ++i) {
        ht1[nums[i] + M]++;
        ht2[nums[i] + M]++;
    }
    
    for (int i = 0; i < N && cnt1 > 0; i++){
        while(ht1[i]-- > 0 && cnt1 > 0){
            max1 *= (i - M);
            --cnt1;
        }
    }
    
    for (int i = N - 1; i >= 0 && cnt2 > 0; --i){
        while(ht2[i]-- > 0 && cnt2 > 0){
            max2 *= (i - M);
            if (cnt2 == 3){
                max1 *= (i - M);
            }
            --cnt2;
        }
    }
    return max1 > max2 ? max1 : max2;
}


//最開始沒發現數字有範圍，所以很蠢的用了quicksort
/*
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(int *data, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right){
            if (data[i] > pivot){
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

    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}

int maximumProduct(int* nums, int numsSize) {
    int a, b;
    quicksort(nums, 0, numsSize - 1);
    a = nums[0] * nums[1] * nums[numsSize - 1];
    b = nums[numsSize - 1] * nums[numsSize - 2] * nums[numsSize - 3];
    if(a < b){
        return b;
    }
    return a;
}
