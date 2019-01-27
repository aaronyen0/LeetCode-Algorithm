/**
 * 用標準佇列的push及pop，也就是先進先出
 * 模仿stack的效果
 */
 
/**
 * version1, 0ms, beats 100%
 * 這題寫法大致上就是創造兩個佇列交換使用
 * 我沒有額外寫一套佇列函式
 * 但內部buffer的push、pop是以先進先出的形式
 * 定義佇列中 front == rear 代表為空，可用資料存放在 queue[fonrt : (rear - 1)]
 * (front + 1) % maxSize == rear 代表全滿，不過本題不會有該情況，所以也沒檢查
 * 
 * 另外用兩個queue就沒有必要像另一題stack模仿queue時，用遞迴取代另一個stack的必要
 * 所以Peek及Pop最好還是改成迴圈形式會比較快
 */

typedef struct{
    int front;
    int rear;
    int *data
} Queue;

typedef struct {
    Queue* mainQueue;
    Queue* tmpQueue;
    Queue queue1;
    Queue queue2;
    int maxSize;
} MyStack;

/** Initialize your data structure here. */
MyStack* myStackCreate(int maxSize) {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->maxSize = maxSize + 1;
    
    stack->queue1.front = 0;
    stack->queue1.rear = 0;
    stack->queue1.data = (int*)malloc(sizeof(int) * (maxSize + 1));
    
    stack->queue2.front = 0;
    stack->queue2.rear = 0;
    stack->queue2.data = (int*)malloc(sizeof(int) * (maxSize + 1));
    
    stack->mainQueue = &(stack->queue1);
    stack->tmpQueue = &(stack->queue2);
    
    return stack;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    obj->mainQueue->data[(obj->mainQueue->rear)++] = x;
    if(obj->mainQueue->rear == obj->maxSize){
        obj->mainQueue->rear = 0;
    }
    //printf("Push front = %d, rear = %d\n", (obj->mainQueue->front), (obj->mainQueue->rear));
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    Queue* mainQueue = obj->mainQueue;
    Queue* tmpQueue = obj->tmpQueue;
    
    int val = mainQueue->data[mainQueue->front++];
    if(mainQueue->front == obj->maxSize){
        mainQueue->front = 0;
    }
 
    //printf("Peek front = %d, rear = %d, val = %d\n", (obj->mainQueue->front), (obj->mainQueue->rear), val);
    //程式重點在這，當mainQueue沒資料時，將mainQueue跟tmpQueue的指標交換
    if(mainQueue->front == mainQueue->rear){
        obj->mainQueue = tmpQueue;
        obj->tmpQueue = mainQueue;
        return val;
    }
    tmpQueue->data[tmpQueue->rear++] = val;
    if(tmpQueue->rear == obj->maxSize){
        tmpQueue->rear = 0;
    }
    return myStackPop(obj);
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    Queue* mainQueue = obj->mainQueue;
    Queue* tmpQueue = obj->tmpQueue;
    
    int val = mainQueue->data[mainQueue->front++];
    if(mainQueue->front == obj->maxSize){
        mainQueue->front = 0;
    }
 
    //printf("Peek front = %d, rear = %d, val = %d\n", (obj->mainQueue->front), (obj->mainQueue->rear), val);
    //程式重點在這，當mainQueue沒資料時，將mainQueue跟tmpQueue的指標交換
    if(mainQueue->front == mainQueue->rear){
        tmpQueue->data[tmpQueue->rear++] = val;
        if(tmpQueue->rear == obj->maxSize){
            tmpQueue->rear = 0;
        }
        obj->mainQueue = tmpQueue;
        obj->tmpQueue = mainQueue;
        return val;
    }
    tmpQueue->data[tmpQueue->rear++] = val;
    if(tmpQueue->rear == obj->maxSize){
        tmpQueue->rear = 0;
    }
    return myStackTop(obj);   
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    if(obj->mainQueue->front == obj->mainQueue->rear){
        return true;
    }
    return false;
}

void myStackFree(MyStack* obj) {
    free(obj->queue1.data);
    free(obj->queue2.data);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * struct MyStack* obj = myStackCreate(maxSize);
 * myStackPush(obj, x);
 * int param_2 = myStackPop(obj);
 * int param_3 = myStackTop(obj);
 * bool param_4 = myStackEmpty(obj);
 * myStackFree(obj);
 */
