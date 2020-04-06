#include<iostream>

using namespace std;
typedef int ElemType;

void printA(ElemType A[], int len)
{
    for(int i=1; i<=len; i++)
        cout<<A[i]<<"  ";
    cout<<endl;
}

void InsertSort(ElemType A[], int n)
{
    int i, j;
    for(i=2; i<=n; i++)
    {
        if(A[i]<A[i-1])
        {
            A[0] = A[i];                    ///复制为哨兵，A[0]不存放元素
            for(j = i-1; A[0]!=A[j]; --j)
                A[j+1] = A[j];
            A[j+1] = A[0];
        }
        printA(A, n);
    }
}



int main()
{
    ElemType A[9] = {0, 55, 17, 78, 9, 45, 65, 87, 32};

    InsertSort(A, 8);
    //printA(A, 8);
    return 0;
}


/**
直接插入排序，并不能完全有序，类似快速排序
2019.09.15
**/
