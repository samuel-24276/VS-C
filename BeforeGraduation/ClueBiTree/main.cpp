#include<iostream>

using namespace std;
typedef int ElemType;
const int MaxSize = 100;

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lch, *rch;
    int ltag, rtag;                 //取0表示左/右孩子，取1表示前驱/后继
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
    cout<<"请输入二叉树结点个数"<<endl;
    cin>>size;
    int a[size*2+1];
    cout<<"请输入二叉树结点："<<endl;
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

void InThread(ThreadTree &p, ThreadTree &pre)   //pre指针指向上一个刚访问过的结点，用以表示各结点访问的前后关系
{
    ///中序遍历对二叉树线索化的递归算法
    if(p)
    {
        InThread(p->lch, pre);              //递归，线索化左子树
        if(!p->lch)                         //左子树为空，建立前驱线索
        {
            p->lch = pre;
            p->ltag = 1;
        }
        if(pre && !pre->rch)
        {
            pre->rch = p;                   //建立前驱结点的后继线索
            pre->rtag = 1;
        }
        pre = p;                            //标记当前结点成为刚访问过的结点
        InThread(p->rch, pre);              //递归，线索化右子树
    }
}

void CreateInThread(ThreadTree T)
{
    ThreadTree pre = NULL;
    if(T)
    {

        InThread(T, pre);
        pre->rch = NULL;                //处理遍历的最后一个结点
        pre->rtag = 1;
    }
}

///以下三个函数的类型和参数ThreadNode *均可用ThreadTree代替，但因为是求首/前驱/后继结点，用ThreadNode *更有意义
ThreadNode *FirstNode(ThreadNode *p)            //求中序线索二叉树第一个结点
{
    while(p->ltag == 0)
        p = p->lch;
    return p;
}

ThreadNode *LastNode(ThreadNode *p)            //求中序线索二叉树最后一个结点
{
    while(p->rtag == 0)
        p = p->rch;
    return p;
}


ThreadNode *PreNode(ThreadNode *p)
{
    if(p->ltag == 1)                            //左子树是前驱线索，直接返回
        return p->lch;
    return LastNode(p->lch);                    //左子树是数据，返回左子树遍历的最后一个结点
}

ThreadNode *NextNode(ThreadNode *p)             //求p的后继结点
{
    if(p->rtag == 0)                            //右子树是数据，返回右子树遍历的第一个结点
        return FirstNode(p->rch);
    return p->rch;                         //是后继线索，直接返回
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

    cout<<"中序遍历：";
    InOrder1(T);
    cout<<endl;
    CreateInThread(T);
    InOrder(T);
    cout<<endl;
    p = FirstNode(T);
    cout<<"首结点："<<p->data<<endl;
    p = NextNode(p);
    cout<<"首结点后继："<<p->data<<endl;
    p = NextNode(p);
    p = PreNode(p);
    cout<<"首结点后继的后继的前驱："<<p->data<<endl;
    p = LastNode(T);
    cout<<"尾结点："<<p->data<<endl;
    ThreadDestroy(T);
    return 0;
}

/***
2019.09.05
线索二叉树与普通二叉树不同之处在于多了两个标志域ltag,rtag,
取0表示自身孩子域指针指向孩子，取1表示无孩子，指向前驱/后继结点
销毁函数ThreadDestroy(ThreadTree T)略显复杂，函数调用多，还有改进空间
InThread()和CreateInThread()函数还没看懂
***/
