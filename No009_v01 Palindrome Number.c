//數字逆著念是否一致

//一般性的寫法，多用一個input存初始值，然後反轉計算sum之後再去比較初始值就行了
bool isPalindrome(int x) {
    int input = x, sum = 0;
    
    if(x < 0){
        return false;
    }
    
    while(x){
        sum = sum * 10 + (x % 10);
        x /= 10;
    }
    
    return input == sum;
}


//v1，開一個buff去存值最後再比較
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


//v3,很意外用類似概念，改成查表找size整體速度比二分法快(後來實測發現這個方法速度非常不穩定)
bool isPalindrome(int x) {   
    int buff[10] = {-1, 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999};
    int size, sum = 0;
    
    if(x < 0){
        return false;
    }

    for(size = 0; size < 10 && x > buff[size]; ++size);
    
    for(int i = 1; i < size; i += 2){
        sum = sum * 10 + (x%10);
        x /= 10;
    }
    
    if(size & 1){
        x /= 10;
    }
    
    return sum == x;
}


//v2,覺得有趣就寫了一個不用buff互相比較的版本
//概念為先抓出int十進位的長度
//然後後面一半的數字倒著加 = 前面一半的數字
//抓長度的時候還特地使用了二分法，沒想到沒有比較快
bool isPalindrome(int x) {
    if(x < 0){
        return false;
    }
    
    int size, sum = 0;
    if(x > 999999){//>6
        if(x > 99999999){//>8
            if(x > 999999999){
                size = 10;
            }else{
                size = 9;
            }
        }else{
            if(x > 9999999){
                size = 8;
            }else{
                size = 7;
            }
        }
    }else{
        if(x > 999){//>3
            if(x > 99999){//>5
                size = 6;
            }else if(x > 9999){
                size = 5;
            }else{
                size = 4;
            }
        }else{
            if(x > 99){
                size = 3;
            }else if(x > 9){
                size = 2;
            }else{
                size = 1;
            }
        }
    }
    
    for(int i = 1; i < size; i += 2){
        sum = sum * 10 + (x%10);
        x /= 10;
    }
    if(size & 1){
        x /= 10;
    }
    
    if(sum == x){
        return true;
    }
    return false;
}
