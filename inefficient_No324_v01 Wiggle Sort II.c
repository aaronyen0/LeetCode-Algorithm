void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(int* arr, int left, int right){
    if(left >= right){
        return;
    }
    
    int pivot = arr[right];
    int i = left, j = right - 1;
    
    while(i < j){
        while(arr[i] < pivot && i < j){
            ++i;
        }
        while(arr[j] >= pivot && i < j){
            --j;
        }
        swap(&arr[i], &arr[j]);
    }
    
    if(arr[i] >= pivot){
        swap(&arr[i], &arr[right]);
    }else{
        ++i;
    }
    
    if(i){
        quicksort(arr, left, i - 1);
    }
    quicksort(arr, i + 1, right);
}

void quicksort2(int* arr, int left, int right){
    if(left >= right){
        return;
    }
    
    int pivot = arr[left];
    int i = left + 1, j = right;
    
    while(i < j){
        while(arr[i] < pivot && i < j){
            ++i;
        }
        while(arr[j] >= pivot && i < j){
            --j;
        }
        swap(&arr[i], &arr[j]);
    }
    
    if(arr[i] >= pivot){
        swap(&arr[--i], &arr[left]);
    }else{
        swap(&arr[i], &arr[left]);
    }
    
    if(i){
        quicksort2(arr, left, i - 1);
    }
    quicksort2(arr, i + 1, right);
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

void wiggleSort(int* nums, int numsSize) {
    int idx, tmp, k;
    int n1 = (numsSize + 1) / 2;
    int n2 = numsSize/2;
    
    int* minArr = (int*)malloc(sizeof(int) * n1);
    int* maxArr = (int*)malloc(sizeof(int) * n2);
    
    //sort
    quicksort3(nums, 0, numsSize - 1);
    
    
    
    for(int i = 0; i < n1; ++i){
        minArr[i] = nums[i];
    }
    for(int i = 0; i < n2; ++i){
        maxArr[i] = nums[n1 + i];
    }
    
    k = 2 * (n1 - 1);
    for(int i = 0; i < n1; ++i){
        nums[k] = minArr[i];
        k -= 2;
    }
    
    k = 2 * n2 - 1;
    for(int i = 0; i < n2; ++i){
        nums[k] = maxArr[i];
        k -= 2;
    }
    
}
