/**
 * 如題，給一個排序過的LinkedList
 * 刪掉重複的node
 */
 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * version2, 4ms, 97%
 * 後來想想，只要最終的LinkedList數字正確就好了
 * 換個方式設計
 * 不再頻繁的更新preNode, crtNode，以及node間的link的
 * 改為紀錄當前的offset
 * 用後面不重複的數字蓋掉重複的數字
 * 減少一些賦值的花費
 * 因此linkedList的前面的node並沒有被抽換
 * 而是把val蓋掉而已
 * 雖然速度快，但不算好寫法
 * 畢竟多數真實情境的LinkedList
 * val部分不會這麼單純
 */

struct ListNode* deleteDuplicates(struct ListNode* head){
    if(!head){
        return head;
    }
    struct ListNode *dstNode = head, *crtNode = head->next;
    int crtNum = head->val;
    
    while(crtNode){
        if(crtNum != crtNode->val){
            crtNum = crtNode->val;
            dstNode = dstNode->next;
            dstNode->val = crtNum;
        }
        crtNode = crtNode->next;
    }
    dstNode->next = NULL;
    
    return head;
}

/**
 * version1, 8ms, 70%
 * 個人最常用的寫法
 * 紀錄兩個node，如果數字重複
 * 就把前面的preNode->next接到crtNode->next
 */
struct ListNode* deleteDuplicates(struct ListNode* head){
    if(!head){
        return head;
    }
    struct ListNode *preNode = head, *crt = head->next;
    
    int preNum = head->val;
    while(crt){
        if(crt->val == preNum){
            preNode->next = crt->next;
        }else{
            preNode = crt;
            preNum = crt->val;
        }
        crt = crt->next;
    }
    return head;
}
