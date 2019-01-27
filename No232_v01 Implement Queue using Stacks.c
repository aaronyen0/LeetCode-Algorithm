/**
 * 用stack實現queue
 */
 
/**
 * 因為可以用遞迴
 * 基本上就是用遞迴當成第二個stack便能實現queue
 */

typedef struct {
    int top;
    int maxSize;
    int *data;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
    MyQueue* stack = (MyQueue*)malloc(sizeof(MyQueue));
    stack->top = -1;
    stack->maxSize = maxSize;
    stack->data = (int*)malloc(sizeof(int) * maxSize);
    return stack;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    obj->data[++(obj->top)] = x;
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    int tmp = obj->data[obj->top--];
    int val;
    if(obj->top == -1){
        return tmp;
    }
    val = myQueuePop(obj);
    myQueuePush(obj, tmp);
    return val;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    int tmp = obj->data[obj->top--];
    int val;
    if(obj->top == -1){
        myQueuePush(obj, tmp);
        return tmp;
    }
    val = myQueuePeek(obj);
    myQueuePush(obj, tmp);
    return val;  
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if(obj->top == -1){
        return true;
    }
    return false;
}

void myQueueFree(MyQueue* obj) {
    free(obj->data);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * struct MyQueue* obj = myQueueCreate(maxSize);
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */
