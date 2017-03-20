/**
 * 1. 创建：create_linked_list;
 * 2. 查找：search；
 * 3. 插入：insert；
 * 4. 删除：delete；
 * 5. 打印：print；
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_S
{
    int val;
    struct NODE_S *next;
}node_s;

//根据数组创建一个链表
node_s *create_linked_list(int *array, int array_size)
{
    node_s *head = NULL;
    node_s *temp = NULL;
    for(int i = 0; i < array_size; i++)
    {
        temp = (node_s *)malloc(sizeof(node_s));
        if (temp == NULL)
        {
            return NULL;
        }
        
        temp->val = array[i];
        if(head == NULL)
        {
            temp->next = NULL;
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    
    return head;
}

//查找
node_s *search(node_s *head, int val)
{
    for (; head != NULL; head = head->next)
    {
        if (head->val == val)
        {
            break;
        }
    }
    return head;
}

//插入
node_s *insert(node_s **phead, int val)
{
    if (search(*phead, val) != NULL)
    {
        return NULL;
    }
    
    node_s *new_node = (node_s *)malloc(sizeof(node_s));
    if (new_node == NULL)
    {
        return NULL;
    }
    
    new_node->val = val;
    new_node->next = *phead;
    *phead = new_node;
    
    return *phead;
}

//删除
void delete(node_s **phead, int val)
{
    if (*phead == NULL)
    {
        return;
    }
    
    node_s *del_node = NULL;
    node_s *temp_node = NULL;
    
    //第一个
    if ((*phead)->val == val)
    {
        del_node = *phead;
        *phead = del_node->next;
    }
    else
    {
        temp_node = *phead;
        for (; temp_node != NULL; temp_node = temp_node->next)
        {
            del_node = temp_node->next;
            if (del_node != NULL && del_node->val == val)
            {
                temp_node->next = del_node->next;
                break;
            }
        }
    }
    
    free(del_node);
}

//打印
void print(node_s *head)
{
    for (; head != NULL; head = head->next)
    {
        printf("%d ", head->val);
    }
    printf("\n");
}


//测试
int main(void)
{
    int array[] = {10, 20, 9, 3, 17, 32, 49, 11};
    int size = 8;
    
    node_s *linked_list;
    linked_list = create_linked_list(array, size);
    print(linked_list);
    
    node_s *temp_node = search(linked_list, 32);
    if (temp_node != NULL)
    {
        printf("search 32: %d\n", temp_node->val);
    }
    
    printf("insert 31:\n");
    insert(&linked_list, 31);
    print(linked_list);
    
    printf("insert 9:\n");
    insert(&linked_list, 9);
    print(linked_list);
    
    printf("delete 17:\n");
    delete(&linked_list, 17);
    print(linked_list);
    
    printf("delete 10:\n");
    delete(&linked_list, 10);
    print(linked_list);
    
    printf("delete 11:\n");
    delete(&linked_list, 11);
    print(linked_list);
    
    printf("delete 31:\n");
    delete(&linked_list, 31);
    print(linked_list);
    
    return 0;
}


