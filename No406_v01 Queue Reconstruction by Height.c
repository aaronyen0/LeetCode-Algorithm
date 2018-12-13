/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct LinkedList{
    int val;
    struct LinkedList* next;
};

struct LinkedList* Insert(struct LinkedList* root, int x){
    struct LinkedList *node, *preNode;
    
    struct LinkedList* newNode = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newNode->val = x;
    newNode->next = 0;
    
    preNode = 0;
    node = root;
    while(node && x > node->val){
        preNode = node;
        node = node->next;
    }
    
    if(preNode == 0){
        newNode->next = node;
        return newNode;
    }else{
        preNode->next = newNode;
        newNode->next = node;
    }
    
    return root;
}

int Pop(struct LinkedList** root){
    int x;
    struct LinkedList* tmp = *root;
    if(tmp){
        *root = (tmp->next);
        x = tmp->val;
        free(tmp);
        return x;
        
    }else{
        return -1;
    }
}

int** reconstructQueue(int** people, int peopleRowSize, int peopleColSize, int* returnSize) {
	struct LinkedList** Table = (struct LinkedList**)calloc(peopleRowSize, sizeof(struct LinkedList*));
	int h, k;

	for (int i = 0; i < peopleRowSize; ++i) {
		h = people[i][0];
		k = people[i][1];
		//printf("h = %d, k = %d", h, k);
		Table[k] = Insert(Table[k], h);
	}

	int **ans = (int**)malloc(sizeof(int*) * peopleRowSize);
	for (int i = 0; i < peopleRowSize; ++i) {
		ans[i] = (int*)malloc(sizeof(int) * 2);
	}

	h = Pop(&Table[0]);
	if (h >= 0) {
		ans[0][0] = h;
		ans[0][1] = 0;
		//printf("h = %d, k = %d\n", h, 0);
	}
	int count, x;
	for (int i = 1; i < peopleRowSize; ++i) {

		for (int j = i; j >= 0; --j) {

			if (Table[j]) {
				
				x = Table[j]->val;
				
				count = 0;
				for (int z = 0; z < i; ++z) {
					if (x <= ans[z][0]) {
						++count;
					}
				}
				//printf("2. j = %d, x = %d, count = %d\n", j, x, count);
				if (count == j) {
					h = Pop(&Table[j]);
					ans[i][0] = h;
					ans[i][1] = j;
					//printf("h = %d, k = %d\n", h, j);
					break;
				}
			}


		}
	}

	*returnSize = peopleRowSize;
	return ans;
}
