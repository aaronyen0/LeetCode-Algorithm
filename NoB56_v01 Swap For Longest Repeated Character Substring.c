/**
 * 最多只能交換一個數字
 * 找出交換什麼數字，可以構造出最長的重複子字串
 */

/**
 * version2, 0ms, 100%
 * 針對C語言的優化，整體結構沒變
 * - cnt > resLen (減少簡查buffer並修改buffer的次數)
 * - tmpCnt = contMaxLen[i]; (減少進入buffer，並不斷重新呼叫陣列的次數)
 * - for i in ['a'~'z']，發現題目只限定lowercase，大幅減少搜索的buffer量
 */

int maxRepOpt1(char * text){
    int tmpNum, tmpCnt, resLen = 0;
    int counter[256] = {0};
    int spaceMaxLen[256] = {0};
    int contMaxLen[256] = {0};
    int pre1Num = -1, pre1Cnt = 0, pre2Num = -1, pre2Cnt = 0, crtNum = -1, crtCnt = 0;
    
    // 儲存最新的三種數值，並保留對應順序，並將必要資訊寫入hashtable
    for(int i = 0; text[i] != 0; ++i){
        tmpNum = text[i];
        counter[tmpNum]++;
        if(tmpNum == crtNum){
            ++crtCnt;
        }else{
            if(pre2Num != -1){
                if(pre1Cnt == 1 && crtNum == pre2Num){
                    pre2Cnt += crtCnt;
                    if(pre2Cnt > resLen && pre2Cnt > spaceMaxLen[pre2Num]){
                        spaceMaxLen[pre2Num] = pre2Cnt;
                    }
                }else{
                    if(pre2Cnt > resLen && pre2Cnt > contMaxLen[pre2Num]){
                        contMaxLen[pre2Num] = pre2Cnt;
                    }
                }
            }
            pre2Num = pre1Num;
            pre2Cnt = pre1Cnt;
            pre1Num = crtNum;
            pre1Cnt = crtCnt;
            crtNum= tmpNum;
            crtCnt = 1;
        }
    }
    
    // 跳出迴圈後，將剩餘的值寫入hashtable
    if(pre2Num != -1){
        if(pre1Cnt == 1 && crtNum == pre2Num){
            pre2Cnt += crtCnt;
            if(pre2Cnt > resLen && pre2Cnt > spaceMaxLen[pre2Num]){
                spaceMaxLen[pre2Num] = pre2Cnt;
            }
        }else{
            if(pre2Cnt > resLen && pre2Cnt > contMaxLen[pre2Num]){
                contMaxLen[pre2Num] = pre2Cnt;
            }
        }
    }
    
    if(pre1Num != -1){
        if(pre1Cnt > resLen && pre1Cnt > contMaxLen[pre1Num]){
            contMaxLen[pre1Num] = pre1Cnt;
        }
    }
    
    if(crtNum != -1){
        if(crtCnt > resLen && crtCnt > contMaxLen[crtNum]){
            contMaxLen[crtNum] = crtCnt;
        }
    }
    
    // 簡查hashtable，輸出最長的值
    for(int i = 'a'; i <= 'z'; ++i){
        tmpCnt = contMaxLen[i];
        if(tmpCnt < counter[i]){
            tmpCnt++;
        }
        
        if(tmpCnt <= spaceMaxLen[i]){
            if(spaceMaxLen[i] < counter[i]){
                tmpCnt = spaceMaxLen[i] + 1;
            }else{
                tmpCnt = spaceMaxLen[i];
            }
        }
        
        if(tmpCnt > resLen){
            resLen = tmpCnt;
        }
    }
    return resLen;
}



/**
 * version1, 4ms, 80%
 * 用hashtable存一些資訊
 * 另外用三組buffer存最接近的三個數字及對應數量
 */

void PrintNumCnt(char* str, int num, int cnt){
    printf("%s: num = %d, cnt = %d\n", str, num, cnt);
}

int maxRepOpt1(char * text){
    int tmpNum, tmpCnt, resLen = 0;
    int counter[256] = {0};
    int spaceMaxLen[256] = {0};
    int contMaxLen[256] = {0};
    int pre1Num = -1, pre1Cnt = 0, pre2Num = -1, pre2Cnt = 0, crtNum = -1, crtCnt = 0;
    
    for(int i = 0; text[i] != 0; ++i){
        tmpNum = text[i];
        counter[tmpNum]++;
        if(tmpNum == crtNum){
            ++crtCnt;
        }else{
            if(pre2Num != -1){
                if(pre1Cnt == 1 && crtNum == pre2Num){
                    pre2Cnt += crtCnt;
                    if(pre2Cnt > spaceMaxLen[pre2Num]){
                        spaceMaxLen[pre2Num] = pre2Cnt;
                    }
                }else{
                    if(pre2Cnt > contMaxLen[pre2Num]){
                        contMaxLen[pre2Num] = pre2Cnt;
                    }
                }
            }
            pre2Num = pre1Num;
            pre2Cnt = pre1Cnt;
            pre1Num = crtNum;
            pre1Cnt = crtCnt;
            crtNum= tmpNum;
            crtCnt = 1;
        }
        //PrintNumCnt("Pre2", pre2Num, pre2Cnt);
        //PrintNumCnt("Pre1", pre1Num, pre1Cnt);
        //PrintNumCnt("Crt ", crtNum, crtCnt);
    }
    
    if(pre2Num != -1){
        if(pre1Cnt == 1 && crtNum == pre2Num){
            pre2Cnt += crtCnt;
            if(pre2Cnt > spaceMaxLen[pre2Num]){
                spaceMaxLen[pre2Num] = pre2Cnt;
            }
        }else{
            if(pre2Cnt > contMaxLen[pre2Num]){
                contMaxLen[pre2Num] = pre2Cnt;
            }
        }
    }
    
    if(pre1Num != -1){
        if(pre1Cnt > contMaxLen[pre1Num]){
            contMaxLen[pre1Num] = pre1Cnt;
        }
    }
    
    if(crtNum != -1){
        if(crtCnt > contMaxLen[crtNum]){
            contMaxLen[crtNum] = crtCnt;
        }
    }
    
    for(int i = 0; i < 256; ++i){
        if(contMaxLen[i] < counter[i]){
            contMaxLen[i]++;
        }
        
        if(contMaxLen[i] <= spaceMaxLen[i]){
            if(spaceMaxLen[i] < counter[i]){
                contMaxLen[i] = spaceMaxLen[i] + 1;
            }else{
                contMaxLen[i] = spaceMaxLen[i];
            }
        }
        
        if(contMaxLen[i] > resLen){
            resLen = contMaxLen[i];
        }
    }
    return resLen;
}

