//數字逆著念是否一致

bool isPalindrome(int x) {
    if(x < 0){
        return false;
    }
    int buff[10], i = 0, j = 0;
    while(x){
        buff[j++] = x % 10;
        x /= 10;
    }
    --j;
    while(i < j){
        if(buff[i++] != buff[j--]){
            return false;
        }
    }
    return true;
}
