int numSpecialEquivGroups(char** A, int ASize) {
    int strLen = strlen(A[0]);
    
	int evenGroup[ASize][26], oddGroup[ASize][26];
    int evenSum[ASize], oddSum[ASize];
    
	int evenCounter[26], oddCounter[26];
	int groupNum = 0, flag, newData;
	int eSum, oSum;

	for (int i = 0; i < ASize; ++i) {
		memset(evenCounter, 0, sizeof(int) * 26);
		memset(oddCounter, 0, sizeof(int) * 26);
		eSum = 0;
		oSum = 0;
		for (int j = 0; j < strLen; j+=2) {
			evenCounter[A[i][j] - 'a']++;
			eSum += A[i][j];

			oSum += A[i][j + 1];
			if (A[i][j + 1]) {
				oddCounter[A[i][j + 1] - 'a']++;
			}
		}

		newData = 1;
		for (int j = 0; j < groupNum; ++j) {
			flag = 0;
			if (eSum == evenSum[j] && oSum == oddSum[j]) {
				for (int k = 0; k < 26; ++k) {
					if (evenGroup[j][k] != evenCounter[k] || oddGroup[j][k] != oddCounter[k]) {
						flag = 1;
						break;
					}
				}
			}
			else {
				flag = 1;
			}
			
			if (flag == 0) {
				newData = 0;
				break;
			}
		}

		if (newData == 1) {
			for (int k = 0; k < 26; ++k) {
				evenGroup[groupNum][k] = evenCounter[k];
				oddGroup[groupNum][k] = oddCounter[k];
			}
			oddSum[groupNum] = oSum;
			evenSum[groupNum] = eSum;
			++groupNum;
		}

	}
    return groupNum;
}
/*
struct HashTable {
	int groupNum;
	int sum;
	int next;
};

struct HashTable* InitialTable(int tableSize);
int** GenMap(int h, int w);
int InsertTable(struct HashTable* table, int* collisionOffset, unsigned char* str, int strLen, int** evenGroup, int** oddGroup, int* groupOffset);

int numSpecialEquivGroups(char** A, int ASize) {
    int strLen = strlen(A[0]);
    
    int** evenGroup = GenMap(ASize, 26), **oddGroup = GenMap(ASize, 26);
	int groupNum = 0, collisionOffset = 65536;

	struct HashTable *table = InitialTable(65536 + ASize);
    for(int i = 0; i < ASize; ++i){
        InsertTable(table, &collisionOffset, (unsigned char*)A[i], strLen, evenGroup, oddGroup, &groupNum);
    }
    
    return groupNum;
}



struct HashTable* InitialTable(int tableSize) {
	struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable) * tableSize);
	for (int i = 0; i < tableSize; ++i) {
		table[i].groupNum = -1;
		table[i].next = -1;
		table[i].sum = -1;
	}
	return table;
}

int** GenMap(int h, int w) {
	int** ans = (int**)malloc(sizeof(int*) * h);
	for (int i = 0; i < h; ++i) {
		ans[i] = (int*)malloc(sizeof(int) * w);
	}
	return ans;
}

int InsertTable(struct HashTable* table, int* collisionOffset, unsigned char* str, int strLen, int** evenGroup, int** oddGroup, int* groupOffset) {
	unsigned int evenSum = 0, oddSum = 0, hashNum;
	unsigned char evenXor = 0, oddXor = 0;
	int evenCounter[26] = { 0 }, oddCounter[26] = {0};

	//1.掃過整個string，得出一些hash 值
	for (int i = 0; i < strLen; i += 2) {
		evenSum += str[i];
		evenXor ^= str[i];
		evenCounter[str[i] - 'a']++;

		oddSum += str[i + 1];
		oddXor ^= str[i + 1];
        if(str[i + 1]){
		    oddCounter[str[i + 1] - 'a']++;
        }
	}
	hashNum = 256 * evenXor + oddXor;
	evenSum = (evenSum << 8) + oddSum;

	//根據hash值，在table上對應的位置檢查看看是否為新的一筆資料
	int next = table[hashNum].next, flag, groupNum, preHash = -1;
	if (table[hashNum].groupNum == -1) {
		table[hashNum].groupNum = *groupOffset;
		table[hashNum].sum = evenSum;
		for (int i = 0; i < 26; ++i) {
			evenGroup[*groupOffset][i] = evenCounter[i];
			oddGroup[*groupOffset][i] = oddCounter[i];
		}
		(*groupOffset)++;
		return 1;
	}
	else {
		next = hashNum;
		while (next != -1) {
			flag = 0;//0一致；1不一致
			if (table[next].sum == evenSum) {
				groupNum = table[next].groupNum;
				for (int i = 0; i < 26; ++i) {
					if (evenGroup[groupNum][i] != evenCounter[i] && oddGroup[groupNum][i] != oddCounter[i]) {
						flag = 1;
						break;
					}
				}
			}
			else {
				flag = 1;
			}

			if (flag == 1) {
				preHash = next;
				next = table[next].next;
			}
			else {
				return 0;
			}
		}

		table[*collisionOffset].groupNum = *groupOffset;
		table[*collisionOffset].sum = evenSum;
		if (preHash != -1) {
			table[preHash].next = *collisionOffset;
		}
		for (int i = 0; i < 26; ++i) {
			evenGroup[*groupOffset][i] = evenCounter[i];
			oddGroup[*groupOffset][i] = oddCounter[i];
		}
		
		(*groupOffset)++;
		(*collisionOffset)++;
		return 1;
	}
	return -1;
}
