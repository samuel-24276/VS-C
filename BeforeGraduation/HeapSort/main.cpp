#include<iostream>

const int MaxSize = 100;
using namespace std;
typedef int ElemType;

void AdjustUp(ElemType A[], int k)
{
    A[0] = A[k];
    int i=k/2;
    while(i>0 && A[i]<A[0])
    {
        A[k] = A[i];
        k = i;
        i = k/2;
    }
    A[k] = A[0];
}

void AdjustDown(ElemType A[], int k, int len)
{
    int i;
    A[0] = A[k];
    for(i=2*k; i<=len; i*=2)
    {
        if(i<len && A[i]<A[i+1])
            i++;
        if(A[0]>=A[i])
            break;
        else
        {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void BuildMaxHeap(ElemType A[], int len)
{
    for(int i = len/2; i>0; i--)
        AdjustDown(A, i, len);
}

void HeapSort(ElemType A[], int len)
{
    //BuildMaxHeap(A, len);
    for(int i=len; i>1; i--)
    {
        swap(A[i], A[1]);
        AdjustDown(A, 1, i-1);
    }
}


//ElemType Add(ElemType A[], int i, ElemType v)
//{
//    A[i] = v;
//    AdjustUp(A, i);
//    return v;
//}
//
//ElemType Del(ElemType A[], int i)
//{
//    swap(A[i], A[1]);
//    AdjustDown(A, 1, i-1);
//    return A[i];
//}

void printA(ElemType A[], int len)
{
    for(int i=1; i<=len; i++)
        cout<<A[i]<<"  ";
    cout<<endl;
}

int main()
{
    ElemType A[MaxSize] = {0, 53, 17, 78, 9, 45, 65, 87, 32};
    int len = 8;
    //打印出建堆后的最大堆序列
    BuildMaxHeap(A, len);
    printA(A, len);

    //插入一个结点，调用上调算法AdjustUp()，仅保证所在分支子树有序
    A[++len] = 76;
    AdjustUp(A, len);
    printA(A, len);

    //将建堆与堆排序算法分开，便于观察结果
    HeapSort(A, len);
    printA(A, len);


    return 0;
}


/**
堆排序，选择排序的一种
关键算法：AdjustDown(),BuildMaxHeap(),HeapSort()
因为是从底往上建堆，所以建堆算法BuildMaxHeap()会调用下调算法AdjustDown()
建堆时间复杂度为O(n)，不是代码呈现的O(nlogn)，因为从底往上建堆，调整上层元素时
只需要同下层的一个分支相比较；插入删除结点时间复杂度为O(logn)，只需要调整所在分支的子树
2019.09.15
**/
