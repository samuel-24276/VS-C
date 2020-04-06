#include<iostream>

using namespace std;
typedef int ElemType;
const int MaxSize = 100;

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lch, *rch;
    int ltag, rtag;                 //ȡ0��ʾ��/�Һ��ӣ�ȡ1��ʾǰ��/���
} ThreadNode, *ThreadTree;

void BTCreate1(ThreadTree &T, ElemType a[], int i)
{
    if(a[i-1] != '0' && a[i-1] != 0)
    {
        T = new ThreadNode;
        T->data = a[i-1];
        T->lch = T->rch = NULL;
        T->ltag = T->rtag = 0;
        BTCreate1(T->lch, a, 2*i);
        BTCreate1(T->rch, a, 2*i+1);
    }
}

void BTCreate2(ThreadTree &T)
{
    int size, j=0;
    cout<<"�����������������"<<endl;
    cin>>size;
    int a[size*2+1];
    cout<<"�������������㣺"<<endl;
    for(j=0; j<size; j++)
        cin>>a[j];
    for(j=size; j<size*2+1; j++)
        a[j] = 0;
    BTCreate1(T, a, 1);
}


bool visit(ThreadTree T)
{
    if(T)
    {
        cout<<T->data<<" ";
        return true;
    }
    return false;
}

void InOrder1(ThreadTree T)
{
    if(T)
    {
        InOrder1(T->lch);
        visit(T);
        InOrder1(T->rch);
    }
}

void InThread(ThreadTree &p, ThreadTree &pre)   //preָ��ָ����һ���շ��ʹ��Ľ�㣬���Ա�ʾ�������ʵ�ǰ���ϵ
{
    ///��������Զ������������ĵݹ��㷨
    if(p)
    {
        InThread(p->lch, pre);              //�ݹ飬������������
        if(!p->lch)                         //������Ϊ�գ�����ǰ������
        {
            p->lch = pre;
            p->ltag = 1;
        }
        if(pre && !pre->rch)
        {
            pre->rch = p;                   //����ǰ�����ĺ������
            pre->rtag = 1;
        }
        pre = p;                            //��ǵ�ǰ����Ϊ�շ��ʹ��Ľ��
        InThread(p->rch, pre);              //�ݹ飬������������
    }
}

void CreateInThread(ThreadTree T)
{
    ThreadTree pre = NULL;
    if(T)
    {

        InThread(T, pre);
        pre->rch = NULL;                //������������һ�����
        pre->rtag = 1;
    }
}

///�����������������ͺͲ���ThreadNode *������ThreadTree���棬����Ϊ������/ǰ��/��̽�㣬��ThreadNode *��������
ThreadNode *FirstNode(ThreadNode *p)            //������������������һ�����
{
    while(p->ltag == 0)
        p = p->lch;
    return p;
}

ThreadNode *LastNode(ThreadNode *p)            //�������������������һ�����
{
    while(p->rtag == 0)
        p = p->rch;
    return p;
}


ThreadNode *PreNode(ThreadNode *p)
{
    if(p->ltag == 1)                            //��������ǰ��������ֱ�ӷ���
        return p->lch;
    return LastNode(p->lch);                    //�����������ݣ��������������������һ�����
}

ThreadNode *NextNode(ThreadNode *p)             //��p�ĺ�̽��
{
    if(p->rtag == 0)                            //�����������ݣ����������������ĵ�һ�����
        return FirstNode(p->rch);
    return p->rch;                         //�Ǻ��������ֱ�ӷ���
}

void InOrder(ThreadNode *T)
{
    for(ThreadNode *p = FirstNode(T); p!= NULL; p = NextNode(p))
        visit(p);
}

void ThreadDestroy(ThreadTree T)
{
    ThreadTree p = FirstNode(T), e = LastNode(T), q= NULL;
    while(p != e)
    {
        q = p;
        p = NextNode(p);
        delete q;
    }
    delete p;
}

int main()
{
    ThreadTree T;
    ElemType a[MaxSize] = {1,2,3,4,5,6,7,8};
    BTCreate1(T, a, 1);
    //BTCreate2(T);
    ThreadNode *p;

    cout<<"���������";
    InOrder1(T);
    cout<<endl;
    CreateInThread(T);
    InOrder(T);
    cout<<endl;
    p = FirstNode(T);
    cout<<"�׽�㣺"<<p->data<<endl;
    p = NextNode(p);
    cout<<"�׽���̣�"<<p->data<<endl;
    p = NextNode(p);
    p = PreNode(p);
    cout<<"�׽���̵ĺ�̵�ǰ����"<<p->data<<endl;
    p = LastNode(T);
    cout<<"β��㣺"<<p->data<<endl;
    ThreadDestroy(T);
    return 0;
}

/***
2019.09.05
��������������ͨ��������֮ͬ�����ڶ���������־��ltag,rtag,
ȡ0��ʾ��������ָ��ָ���ӣ�ȡ1��ʾ�޺��ӣ�ָ��ǰ��/��̽��
���ٺ���ThreadDestroy(ThreadTree T)���Ը��ӣ��������ö࣬���иĽ��ռ�
InThread()��CreateInThread()������û����
***/
