/**
 * 這題一直到繳交好幾次之後，才真正理解題目意思，英文真的要練習
 * 題目說有兩個字串s和p，問s是否跟p等價
 * p字串有機會出現兩個特殊字元：'.' 及 '*'
 * '.'：可以代替任何字元
 * '*'：代表他的前一個字元可以重複n次，n >= 0
 * 例如："a*bc" = "bc" or "abc" or "aabc" or "aaabc" or ...
 */


/**
 * version 2
 * 發現InRepeating似乎有點多餘
 * 而且還要多重複判斷'.'
 * 於是就整合在一起
 */
bool isMatch(char* s, char* p) {
	int sIdx = 0, pIdx = 0, k;
	char r;
	while (s[sIdx] && p[pIdx]) {
		if (p[pIdx + 1] == '*' ) { //若該字元是可變長度的
			r = p[pIdx];
			//判斷字元是哪個種類，先剪枝排掉重複的，再進入repeat階段逐一檢查
			if (r == '.') {
				do{
					pIdx += 2;
				}while(p[pIdx] != 0 && p[pIdx + 1] == '*');
				do{
					if (isMatch(&s[sIdx], &p[pIdx])) {
						return true;
					}
				}while(s[sIdx++] != 0);
			}else {
				do{
					pIdx += 2;
				}while(p[pIdx] == r && p[pIdx + 1] == '*');
				do{
					if (isMatch(&s[sIdx], &p[pIdx])) {
						return true;
					}
				}while(s[sIdx++] == r);
			}
			return false;
		} else if (s[sIdx] != p[pIdx] && p[pIdx] != '.') { //若該s和p無法配對則離開
			break;
		}
		++sIdx;
		++pIdx;
	}

	//若有剩，把多餘的x*丟棄
	while (p[pIdx] != 0 && p[pIdx + 1] == '*') {
		pIdx += 2;
	}

	//最後發現兩邊都走到底則代表找到解
	return !s[sIdx] && !p[pIdx];
	}


/**
 * version1 , 4ms
 * 這個寫法應該算是DFS，進repeat的時候，對每個case都做檢查
 * 分兩階段處理問題
 * 1.repeat
 * 2.match
 */
 
bool InRepeating(char* s, char* p, char r) ;

bool isMatch(char* s, char* p) {
	int sIdx = 0, pIdx = 0;
	char r;
	while (s[sIdx] && p[pIdx]) {
		if (p[pIdx + 1] == '*' ) { //若該字元是可變長度的
			r = p[pIdx];
			//判斷字元是哪個種類，先剪枝排掉重複的，再進入repeat階段逐一檢查
			if (r == '.') {
				do{
					pIdx += 2;
				}while(p[pIdx] != 0 && p[pIdx + 1] == '*');
			}else {
				do{
					pIdx += 2;
				}while(p[pIdx] == r && p[pIdx + 1] == '*');
			}
			return InRepeating(&s[sIdx], &p[pIdx], r);
		} else if (s[sIdx] != p[pIdx] && p[pIdx] != '.') { //若該s和p無法配對則離開
			break;
		}
		++sIdx;
		++pIdx;
	}

	//若有剩，把多餘的x*丟棄
	while (p[pIdx] != 0 && p[pIdx + 1] == '*') {
		pIdx += 2;
	}

	//最後發現兩邊都走到底則代表找到解
	if (s[sIdx] == 0 && p[pIdx] == 0) {
		return true;
	}
	return false;
}

bool InRepeating(char* s, char* p, char r) {
	int i = 0;

	//讓r依序跟s的某些字元配對
	if (r == '.') {
		do{
			if (isMatch(&s[i], p)) {
				return true;
			}
		}while(s[i++] != 0);
	}else {
		do{
			if (isMatch(&s[i], p)) {
				return true;
			}
		}while(s[i++] == r);
	}
	return false;
}
