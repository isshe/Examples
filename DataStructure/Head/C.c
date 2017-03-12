
#include <stdio.h>

#define MAX_LEN 1000

void adjust(int *head, int len);     //len不是数组大小，是堆大小
void print_head(int *head, int len);
void swap(int *head, int i, int j);
void siftup(int *head, int cur_node);
void siftdown(int *head, int head_len, int cur);
void insert(int *head, int *head_len, int innode);
int extract_min(int *head, int *head_len);
void head_sort(int *head, int head_len);

//为了简单、简洁，head的数组就不动态分配了，使用固定了。
int main(void)
{
    int head[MAX_LEN] = {-1, 10,20,5,44,32,150,50,222,342,1,9, 28, 20};        //head[0]不用
    int head_len = 13;

    //调整为最小堆
    adjust(head, head_len);
    print_head(head, head_len);

    insert(head, &head_len, 33);
    print_head(head, head_len);

    extract_min(head, &head_len);
    print_head(head, head_len);

    head_sort(head, head_len);
    return 0;
}


//调整为最小堆
void adjust(int *head, int len)     //len不是数组大小，是堆大小
{
    int n = len / 2;        //取最后一个节点的父节点。
    int min = 0;

    for (int i = n; i > 0; i--)         //第0个不用
    {
        //这里要注意，这里不是只每个父节点调整一次，是递归调整。这里原来写错了。
        siftdown(head, len, i);
    }
}

void print_head(int *head, int len)
{
    for (int i = 0; i <= len; i++)
    {
        printf("%d, ", head[i]);
    }
    printf("\n");
}

void swap(int *head, int i, int j)
{
    int temp = head[i];
    head[i] = head[j];
    head[j] = temp;
}

//siftup为最小堆
void siftup(int *head, int cur_node)
{
    int parent = 0;
    int i = cur_node;

    while(1)
    {
        if (i == 1)
        {
            break;
        }
        parent = i / 2;
        if (head[parent] <= head[i])        //符合规则，不用调整
        {
            break;
        }

        swap(head, parent, i);
        i = parent;
    }
}

//向下调整为最小堆, 如过从根节点开始调整，则cur = 1；
void siftdown(int *head, int head_len, int cur)
{
    int i = cur;
    int child = 0;

    while(1)
    {
        child = i * 2;
        if (child > head_len)      //没有子节点
        {
            break;
        }

        if (child + 1 <= head_len && head[child + 1] < head[child])     //有右节点
        {
            child++;            //指向小的那个
        }

        if (head[i] <= head[child])         //不用调整
        {
            break;
        }
        swap(head, i, child);
        i = child;
    }
}


//插入
void insert(int *head, int *head_len, int innode)
{
    int temp_len = *head_len;
    if (temp_len >= MAX_LEN)
    {
        return;                 //不能再插入了
    }

    head[++temp_len] = innode;
    *head_len = temp_len;
    siftup(head, *head_len);
}

//取最小的数
int extract_min(int *head, int *head_len)
{
    int temp_len = *head_len;
    if (temp_len < 1)
    {
        return -1;              //head empty
    }

    int res = head[1];          //结果
    head[1] = head[temp_len--];
    *head_len = temp_len;
    siftdown(head, *head_len, 1);        //从根节点开始

    return res;
}


void head_sort(int *head, int head_len)
{
    int i = head_len;
    while (i >= 1)
    {
        printf("%d, ", extract_min(head, &i));
    }
    printf("\n");
}
