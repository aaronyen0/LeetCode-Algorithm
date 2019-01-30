/**
 * 給一個字串，字串內只有大中小括號
 * 檢查括號是否為合法的
 */
 
/**
 * version1, 0ms, 100%
 * 明顯的是stack問題
 * stack[4096]是我實測測項才開的大小
 * 完整寫法要先遍歷一次估計堆疊上限
 * 剩下的就是push pop配對問題而已
 * 要小心可能最後string跑完stack還有剩也是不合法的
 */

bool isValid(char* s) {
    char stack[4096], tmp;
    int top = -1, i = 0;
    while(s[i]){
        tmp = s[i++];
        if(tmp == '(' || tmp == '[' || tmp == '{'){
            stack[++top] = tmp;
        }else{
            if(top < 0){
                return false;
            }else if(tmp == ')' && stack[top] != '('){
                return false;
            }else if(tmp == ']' && stack[top] != '['){
                return false;
            }else if(tmp == '}' && stack[top] != '{'){
                return false;
            }
            --top;
        }
    }
    if(top != -1){
        return false;
    }
    return true;
}
