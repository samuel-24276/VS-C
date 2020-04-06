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
���������ǽ��������һ�֣�ƽ���������ţ�ʱ�临�Ӷ�O(nlogn)
ÿ���������һ��Ԫ�ط�������λ���ϣ���ݹ������Ԫ�صĳ�ʼ�����йأ�
��ÿ�λ��ֺ�����Ƚ�ƽ�⣬��ݹ�������٣�����϶ࡣ�ݹ���̹���һ���ݹ������ݹ���ȼ�����
���ܱ�֤�������ȫ����һ������������һ��ʹ��
2019.09.15
**/
