/**
 * 給兩個sorted linkedlist
 * 合併成一個sorted linkedlist
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *crt = NULL, *root;
    if(!l1){
        return l2;
    }else if(!l2){
        return l1;
    }else{
        if(l1->val < l2->val){
            root = l1;
            l1 = l1->next;
        }else{
            root = l2;
            l2 = l2->next;
        }
    }
    crt = root;
    
    while(l1 && l2){
        //printf("l1 = %d, l2 = %d\n", l1->val, l2->val);
        if(l1->val < l2->val){
            crt->next = l1;
            l1 = l1->next;
        }else{
            crt->next = l2;
            l2 = l2->next;
        }
        crt = crt->next;
        //printf("crt = %d\n", crt->val);
    }
    
    if(l1){
        crt->next = l1;
    }
    if(l2){
        crt->next = l2;
    }
    return root;
}
