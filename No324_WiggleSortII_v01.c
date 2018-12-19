void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

void wiggleSort(int* nums, int numsSize) {
    int idx, tmp;
    int n1 = numsSize/2 + (numsSize&1);
    int n2 = numsSize/2;
    
    int* minArr = (int*)malloc(sizeof(int) * n1);
    int* maxArr = (int*)malloc(sizeof(int) * n2);
    
    //sort
    quicksort(nums, 0, numsSize - 1);

    
    for(int i = 0; i < n1; ++i){
        minArr[i] = nums[i];
    }
    for(int i = 0; i < n2; ++i){
        maxArr[i] = nums[n1 + i];
    }
    
    for(int i = 0; i < n1; ++i){
         nums[2 * (n1 - i - 1)] = minArr[i];
    }
    for(int i = 0; i < n2; ++i){
        nums[2 * (n2 - i) - 1] = maxArr[i];
    }
    
}
