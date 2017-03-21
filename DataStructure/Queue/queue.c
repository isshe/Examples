/**
 * queue-LinkedList
 * 1. init_queue: 初始化，新建一个节点，头尾指针都指向它
 * 2. destroy_queue: 销毁
 * 3. clear_queue: 清空队列
 * 4. is_empty: 判断是否为空
 * 5. top: 返回队列前的元素。
 * 6. push: 入队
 * 7. pop: 出队
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct NODE_S
{
    int val;
    struct NODE_S *next;
}node_s, *pnode_s;


typedef struct LINKQUEUE_S
{
    node_s *front;
    node_s *rear;
    int len;
}linkqueue_s;
 
//init
int init_queue(linkqueue_s *queue)
{
    if (queue == NULL)
    {
        return -1;
    }
    
    queue->front = (node_s *) malloc(sizeof(node_s));
    queue->rear = queue->front;
    if (queue->front == NULL)
    {
        return -1;
    }
    
    queue->front->next = NULL;
    
    //queue->front = NULL;
    //queue->rear = NULL;
    queue->len = 0;
    
    return 0;
}
 
 //destroy
int destroy_queue(linkqueue_s *queue)
{
    while(queue->front != NULL)
    {
        queue->rear = queue->front->next;
        free(queue->front);
        queue->front = queue->rear;
    }
    
    queue->len = 0;
    return 0;
}
 
//clear
int clear_queue(linkqueue_s *queue)
{
    destroy_queue(queue);
    init_queue(queue);
    
    return 0;
}
 
//is empty
int is_empty(linkqueue_s *queue)
{
    if (queue->len == 0 || queue->front == queue->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
 
int get_length(linkqueue_s *queue)
{
    assert(queue != NULL);
    
    return queue->len;
}

//这里应该返回一个值而不是指针，因为返回指针可能被修改！！！
node_s top(linkqueue_s *queue)
{
    assert(queue != NULL);
    
    node_s ret;
    
    ret.val = 0;
    ret.next = NULL;
    if (queue->front == queue->rear)
    {
        return ret;
    }
    
    ret.val = queue->front->next->val;
    
    return ret;
}


int pop(linkqueue_s *queue)
{
    assert(queue != NULL);
    
    if (queue->len == 0 || queue->front == queue->rear)
    {
        return -1;
    }
    
    node_s *p;
    p = queue->front->next;
    queue->front->next = p->next;
    queue->len--;
    
    if (p == queue->rear)
    {
        queue->rear = queue->front;
    }

    free(p);
    return 0; 
}

node_s *push(linkqueue_s *queue, int val)
{
    node_s *new_node = (node_s *)malloc(sizeof(node_s));
    if (new_node == NULL)
    {
        return NULL;
    }
    
    new_node->val = val;
    new_node->next = NULL;
    queue->rear->next = new_node;
    queue->rear = new_node;
    
    queue->len++;
    return new_node;
}

void print_queue(linkqueue_s *queue)
{
    node_s *temp = NULL;
    
    if (queue->front == queue->rear)
    {
        return;
    }
    
    temp = queue->front->next;
    printf("len = %d: ", queue->len);
    for(; temp != NULL; temp = temp->next)
    {
        printf("%d ", temp->val);
    }
    printf("\n");
}


int main(void)
{
    linkqueue_s queue;
    
    init_queue(&queue);
    print_queue(&queue);
    
    push(&queue, 20);
    print_queue(&queue);
    push(&queue, 23);
    print_queue(&queue);
    
    pop(&queue);
    print_queue(&queue);
    
    node_s node;
    node = top(&queue);
    printf("top: %d\n", node.val);
    
    clear_queue(&queue);
    print_queue(&queue);
    
    printf("len = %d\n", queue.len);
    destroy_queue(&queue);
    
    return 0;
}
 
