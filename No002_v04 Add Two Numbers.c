/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * version4, 4ms, 99.97%
 * 發現記憶體一次配置一格時間浮動太大:
 * 所以嘗試一次配一個陣列，如果陣列不夠用再繼續配
 * 雖然時間還是會跳，但是有比較平均了
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int MALLOCSIZE = 16;
    int carry = 0, cnt = 0;
    struct ListNode *crt, *root, *buffer;
    
    buffer = (struct ListNode*)malloc(sizeof(struct ListNode) * MALLOCSIZE);
    
    root = &buffer[cnt];
    buffer[cnt].val = (l1->val + l2->val + carry) % 10;
    carry = (l1->val + l2->val + carry) / 10;
    l1 = l1->next;
    l2 = l2->next;
    crt = root;
    
    while(l1 && l2){
        if(++cnt == MALLOCSIZE){
            buffer = (struct ListNode*)malloc(sizeof(struct ListNode) * MALLOCSIZE);
            cnt = 0;
        }
        crt->next = &buffer[cnt];
        crt = &buffer[cnt];
        buffer[cnt].val = (l1->val + l2->val + carry) % 10;
        carry = (l1->val + l2->val + carry) / 10;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    if(l1 == NULL){
        l1 = l2;
    }
    
    while(l1){
        if(++cnt == MALLOCSIZE){
            buffer = (struct ListNode*)malloc(sizeof(struct ListNode) * MALLOCSIZE);
            cnt = 0;
        }
        crt->next = &buffer[cnt];
        crt = &buffer[cnt];
        buffer[cnt].val = (l1->val + carry) % 10;
        carry = (l1->val + carry) / 10;
        l1 = l1->next;
    }
    
    if(carry){
        if(++cnt == MALLOCSIZE){
            buffer = (struct ListNode*)malloc(sizeof(struct ListNode) * MALLOCSIZE);
            cnt = 0;
        }
        crt->next = &buffer[cnt];
        crt = &buffer[cnt];
        buffer[cnt].val = carry;
    }
    buffer[cnt].next = NULL;
    return root;
}

//多繳交幾次發現，這個版本的時間落差很大，看來leetcode配置記憶體的機制似乎很影響時間。

/**
 * version3, 4ms, 99.97%
 * 改寫:
 * 1. 不使用function去包malloc tree node
 * 2. 只有要離開前在next塞NULL，其他時候都不理會
 * 快這麼很多，有點嚇到。
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    struct ListNode* crt, *root;
    root = NewNode(0);
    crt = root;
    
    while(l1 && l2){
        crt->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        crt = crt->next;
        
        crt->val = (l1->val + l2->val + carry) % 10;
        carry = (l1->val + l2->val + carry) / 10;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    if(l1 == NULL){
        l1 = l2;
    }
    
    while(l1){
        crt->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        crt = crt->next;
        
        crt->val = (l1->val + carry) % 10;
        carry = (l1->val + carry) / 10;
        l1 = l1->next;
    }
    
    if(carry){
        crt->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        crt = crt->next;
        crt->val = carry;
    }
    crt->next = NULL;
    return root->next;
}

/**
 * version2, 12ms, 97%
 * 這是直接看別人的寫法
 * 似乎判斷式的先後順序和數量對運算的影響也蠻深的? @後來實測應該是配記憶體的層級和塞NULL的時機掌握好就可
 * 這種遞迴的寫法其實是我一直很弱的部分
 * 是說除了next = NULL只需要一次之外，感覺運算也不會比非遞迴多
 * 不知道為何可以快這麼多
 */
struct ListNode* addtwoNumswithcarry(struct ListNode* l1, struct ListNode* l2,int carry){
    if(l1 == NULL && l2 == NULL){
        if(carry != 0){
            struct ListNode* res;
            res = (struct ListNode*)malloc(sizeof(struct ListNode));
            res->val = carry;
            res->next = NULL;
            return res;
        }
        else{
            return NULL;
        } 
    }
    
    if(l1 == NULL && l2 != NULL){
        return addtwoNumswithcarry(l2, l1, carry);
    }
    
    //核心在這
    if(l1 != NULL && l2 == NULL){
        struct ListNode* res;
        res = (struct ListNode*)malloc(sizeof(struct ListNode));
        res->val = (l1->val + carry) % 10;
        res->next = addtwoNumswithcarry(l1->next, NULL, (l1->val + carry) / 10);
        return res;
    }
    
    //還有這
    if(l1 != NULL && l2 != NULL)
    {
        struct ListNode* res;
        res = (struct ListNode*)malloc(sizeof(struct ListNode));
        res->val = (l1->val + l2->val + carry) % 10;
        res->next = addtwoNumswithcarry(l1->next, l2->next, (l1->val + l2->val + carry) / 10);
        return res;
    }
    return NULL;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    return addtwoNumswithcarry(l1,l2,0);
}

/**
 * version1, 20ms, 60%
 *寫法類似mergesort的merge操作，但更簡單
 *共分4階段(flag用來判斷需不需要進位)
 *1.若list1和list2都還沒走完時
 *2.list1還有數字但list2走完
 *3.list2還有數字但list1走完
 *4.小心若最後flag表示要進位，記得還有一個數字1要插入
 *
 *題目其實有聲明l1和l2是非空集合，所以if(crt)其實可以拿掉，這樣寫只是希望它看起來更通用
 */


struct ListNode* NewNode(int val){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int sum, flag = 0;
    struct ListNode *crt = NULL, *root = NULL;
    
    while(l1 && l2){
        sum = l1->val + l2->val + flag;
        if(sum > 9){
            flag = 1;
            sum -= 10;
        }else{
            flag = 0;
        }
        
        if(crt){
            crt->next = NewNode(sum);
            crt = crt->next;
        }else{
            crt = NewNode(sum);
            root = crt;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    
    while(l1){
        sum = l1->val + flag;
        if(sum > 9){
            flag = 1;
            sum -= 10;
        }else{
            flag = 0;
        }
        
        if(crt){
            crt->next = NewNode(sum);
            crt = crt->next;
        }else{
            crt = NewNode(sum);
            root = crt;
        }
        l1 = l1->next;

    }
    
    while(l2){
        sum = l2->val + flag;
        if(sum > 9){
            flag = 1;
            sum -= 10;
        }else{
            flag = 0;
        }
        
        if(crt){
            crt->next = NewNode(sum);
            crt = crt->next;
        }else{
            crt = NewNode(sum);
            root = crt;
        }
        l2 = l2->next;
    }
    
    if(flag){
        if(crt){
            crt->next = NewNode(1);
        }else{
            crt = NewNode(1);
            root = crt;
        }
    }
    return root;
}
