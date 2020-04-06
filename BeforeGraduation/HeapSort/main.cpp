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
    //��ӡ�����Ѻ����������
    BuildMaxHeap(A, len);
    printA(A, len);

    //����һ����㣬�����ϵ��㷨AdjustUp()������֤���ڷ�֧��������
    A[++len] = 76;
    AdjustUp(A, len);
    printA(A, len);

    //��������������㷨�ֿ������ڹ۲���
    HeapSort(A, len);
    printA(A, len);


    return 0;
}


/**
������ѡ�������һ��
�ؼ��㷨��AdjustDown(),BuildMaxHeap(),HeapSort()
��Ϊ�Ǵӵ����Ͻ��ѣ����Խ����㷨BuildMaxHeap()������µ��㷨AdjustDown()
����ʱ�临�Ӷ�ΪO(n)�����Ǵ�����ֵ�O(nlogn)����Ϊ�ӵ����Ͻ��ѣ������ϲ�Ԫ��ʱ
ֻ��Ҫͬ�²��һ����֧��Ƚϣ�����ɾ�����ʱ�临�Ӷ�ΪO(logn)��ֻ��Ҫ�������ڷ�֧������
2019.09.15
**/
