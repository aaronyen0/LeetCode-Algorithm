/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int** reconstructQueue(int** people, int peopleRowSize, int peopleColSize, int* returnSize) {
    int h, k, idx, j;
    int* arr = people[0];
    int* arr2 = people[1];
    
    int* cnt = (int*)calloc(peopleRowSize, sizeof(int));
    
    int** res = (int**)malloc(sizeof(int*) * peopleRowSize);
    for(int i = 0; i < peopleRowSize; ++i){
        res[i] = (int*)malloc(sizeof(int) * 2);
    }
    
    //selection sort
    for(int i = 0; i < peopleRowSize; ++i){
        idx = i;
        for(j = i + 1; j < peopleRowSize; ++j){
            if(people[j][0] < people[idx][0] || (people[j][0] == people[idx][0] && people[j][1] < people[idx][1])){
                idx = j;
            }
        }
        h = people[idx][0];
        k = people[idx][1];
        
        people[idx][0] = people[i][0];
        people[idx][1] = people[i][1];

        //從小到大塞值
        idx = k;
		j = 0;
		do{
			if (cnt[j] && (res[j][0] != h)) {
				idx++;
			}
		} while (j++ < idx);
        res[idx][0] = h;
        res[idx][1] = k;
        cnt[idx] = 1;
    }
    
    *returnSize = peopleRowSize;
    return res;
}
