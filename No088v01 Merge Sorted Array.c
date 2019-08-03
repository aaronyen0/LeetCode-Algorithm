
/**
 * 將兩個已排序陣列nums1[], nums2[]
 * 合併到nums1中
 * 另外假設nums1[]已經事先把記憶體配置好了
 */
 
/**
 * version1, 4ms, 82%
 * merge sort的後半段
 * 用另一個buffer去接merge的結果
 * 最後再複製回來
 */
 
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    int i = 0, j = 0, offset = 0;
    int *buffer = (int*)malloc(sizeof(int) * (m + n));
    while(i < m && j < n){
        if(nums1[i] < nums2[j]){
            buffer[offset++] = nums1[i++];
        }else{
            buffer[offset++] = nums2[j++];
        }
    }
    while(i < m){
        buffer[offset++] = nums1[i++];
    }
    while(j < n){
        buffer[offset++] = nums2[j++];
    }
    memcpy(nums1, buffer, sizeof(int) * (m + n));
}

