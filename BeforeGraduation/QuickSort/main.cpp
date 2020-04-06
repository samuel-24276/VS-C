#include<iostream>

using namespace std;
typedef int ElemType;

int Partition(ElemType A[], int low, int high)
{
    ElemType pivot = A[low];
    while(low<high)
    {
        while(low<high && A[high]>=pivot)
            --high;
        A[low] = A[high];
        while(low<high && A[low]<=pivot)
            ++low;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(ElemType A[], int low, int high)
{
    if(low<high)
    {
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos-1);
        QuickSort(A, high+1, pivotpos);
    }
}

void printA(ElemType A[], int len)
{
    for(int i=0; i<len; i++)
        cout<<A[i]<<"  ";
    cout<<endl;
}

int main()
{
    ElemType A[8] = {53, 17, 78, 9, 45, 65, 87, 32};
    QuickSort(A, 0, 7);
    printA(A, 8);
    return 0;
}


/**
快速排序是交换排序的一种，平均性能最优，时间复杂度O(nlogn)
每次排序会有一个元素放在最终位置上，其递归次数与元素的初始排列有关，
若每次划分后分区比较平衡，则递归次数较少，否则较多。递归过程构成一个递归树，递归深度即树高
不能保证排序后完全有序，一般与其他排序一起使用
2019.09.15
**/
