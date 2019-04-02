/**
 * 如題
 * 給兩個已排序的陣列
 * 找到所有數字的中位數
 */


/**
 * version1, 16ms, 95%
 * 沒有依照題目要求寫成O(log(m+n))
 * O(m+n)，沒什麼特別的作法
 * 就是將數字merge到中位數字
 * 小心median的算法
 */
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total = nums1Size + nums2Size;
    int median = (total >> 1) + 1;
    int* arr = (int*)malloc(sizeof(int) * median);
    int i = 0, j = 0, k = 0;

    while(i < nums1Size && j < nums2Size){
        if(nums1[i] < nums2[j]){
            arr[k++] = nums1[i++];
        }else{
            arr[k++] = nums2[j++];
        }
        if(k == median){
            break;
        }
    }
    while(k < median && i < nums1Size){
        arr[k++] = nums1[i++];
    }
    while(k < median && j < nums2Size){
        arr[k++] = nums2[j++];
    }
    
    if(total & 1){
        return arr[median - 1];
    }
    return (arr[median - 1] + arr[median - 2]) * 0.5;
}
