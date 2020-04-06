#include<iostream>

using namespace std;
typedef int ElemType;

void ShellSort(ElemType A[], int n)
{
    for(int dk = n/2; dk>=1; dk=dk/2)
    {
        for(int i=dk+1; i<=n; ++i)
        {
            if(A[i]<A[i-dk])
            {
                A[0] = A[i];
                int j;
                for(j=i-dk; j>0&&A[0]<A[j]; j-=dk)
                    A[j+dk] = A[j];
                A[j+dk] = A[0];
            }
        }
    }
}


void printA(ElemType A[], int len)
{
    for(int i=1; i<=len; i++)
        cout<<A[i]<<"  ";
    cout<<endl;
}

int main()
{
    ElemType A[9] = {0, 53, 17, 78, 9, 45, 65, 87, 32};
    ShellSort(A, 8);
    printA(A, 8);
    return 0;
}

/**
ϣ�����򣬲��������һ�֣���ֱ�Ӳ���������ȣ����������޸ģ�
1.ǰ���¼λ�õ�������dk������1��
2.A[0]ֻ���ݴ浥Ԫ�����ǡ��ڱ�������j<=0ʱ������λ���ѵ�

2019.09.15
**/
