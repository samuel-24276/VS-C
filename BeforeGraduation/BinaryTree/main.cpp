#include<iostream>

const int MaxSize = 100;
using namespace std;

typedef  int ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lch, *rch;
} BiTNode, *BiTree;

bool visit(BiTree T)
{
    if(T)
    {
        cout<<T->data<<" ";
        return true;
    }
    return false;
}

void BTCreate1(BiTree &T, ElemType a[], int i)
{
    if(a[i-1] != '0' && a[i-1] != 0)
    {
        T = new BiTNode;
        T->data = a[i-1];
        T->lch = T->rch = NULL;
        BTCreate1(T->lch, a, 2*i);
        BTCreate1(T->rch, a, 2*i+1);
    }
}

void BTCreate2(BiTree &T)
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


void BTDestroy(BiTree T)
{
    if(T)
    {
        BTDestroy(T->lch);
        BTDestroy(T->rch);
        delete T;
    }
}

///****************递归算法****************

void PreOrder1(BiTree T)
{
    if(T)
    {
        visit(T);
        PreOrder1(T->lch);
        PreOrder1(T->rch);
    }
}

void InOrder1(BiTree T)
{
    if(T)
    {
        InOrder1(T->lch);
        visit(T);
        InOrder1(T->rch);
    }
}

void PostOrder1(BiTree T)
{
    if(T)
    {
        PostOrder1(T->lch);
        PostOrder1(T->rch);
        visit(T);
    }
}

int GetDeepth1(BiTree T)
{
    if(!T)  return 0;
    int m = GetDeepth1(T->lch);
    int n = GetDeepth1(T->rch);
    return m>n?m+1:n+1;
}

int Count(BiTree T)
{
    if(!T)  return 0;
    int m = Count(T->lch);
    int n = Count(T->rch);
    return m+n+1;
}

int LeafCount(BiTree T)
{
    if(!T)  return 0;
    else if(!T->lch && !T->rch)   return 1;
    else
    {
        int m = LeafCount(T->lch);
        int n = LeafCount(T->rch);
        return m+n;
    }
}


///***********非递归

void LevelOrder(BiTree T)
{
    BiTree p;
    BiTree Q[MaxSize];
    int front, rear;
    front = rear = -1;
    Q[++rear] = T;
    while(front != rear)
    {
        p = Q[++front];
        visit(p);
        if(p->lch)
            Q[++rear] = p->lch;
        if(p->rch)
            Q[++rear] = p->rch;
    }
}

void PreOrder2(BiTree T)
{
    BiTree p = T;
    BiTree s[MaxSize];
    int top = -1;
    while(p || top != -1)
    {
        if(p)
        {
            visit(p);
            s[++top] = p;
            p = p->lch;
        }
        else
        {
            p = s[top--];
            p = p->rch;
        }
    }
}

void InOrder2(BiTree T)
{
    BiTree p = T;
    BiTree s[MaxSize];
    int top = -1;
    while(p || top != -1)
    {
        if(p)
        {
            s[++top] = p;
            p = p->lch;
        }
        else
        {
            p = s[top--];
            visit(p);
            p = p->rch;
        }
    }
}

void PostOrder2(BiTree T)
{
    BiTree p = T, r = NULL;             ///r is a helped point which used to point a recently visited node
    BiTree s[MaxSize];
    int top = -1;
    while(p || top != -1)
    {
        if(p)                           //走到最左
        {
            s[++top] = p;
            p = p->lch;
        }
        else                            //开始走右边
        {
            p = s[top];
            if(p->rch && p->rch != r)   //右子树存在且未被访问
            {
                p = p->rch;
                s[++top] = p;
                p = p->lch;
            }
            else                        //已到最右叶子结点或该结点被访问过
            {
                p = s[top--];           //获取该被访问的结点
                visit(p);
                r = p;
                p = NULL;               //重置p指针
            }
        }
    }
}

int GetDeepth2(BiTree T)                    ///采用层次遍历获取深度
{
    if(!T)  return 0;
    int front =-1, rear = -1;
    int last =0, level = 0;                 //last指向下一层第一个结点的位置
    BiTree Q[MaxSize];
    Q[++rear] = T;                          //根结点入队
    BiTree p;
    while(front < rear)
    {
        p = Q[++front];
        if(p->lch)
            Q[++rear] = p->lch;
        if(p->rch)
            Q[++rear] = p->rch;
        if(front == last)                   //处理该层最右结点
        {
            level++;
            last = rear;                    //last指向下层
        }
    }
    return level;
}

int main()
{
    BiTree T;
//    ElemType a[MaxSize] ={1,2,3,4,5,6,0};
//    BTCreate1(T, a, 1);
    BTCreate2(T);
    cout<<"先序遍历：\n";
    PreOrder1(T);
    cout<<endl;
    PreOrder2(T);
    cout<<endl;
    cout<<"中序遍历：\n";
    InOrder1(T);
    cout<<endl;
    InOrder2(T);
    cout<<endl;
    cout<<"后序遍历：\n";
    PostOrder1(T);
    cout<<endl;
    PostOrder2(T);
    cout<<endl;
    cout<<"层次遍历\n";
    LevelOrder(T);
    cout<<endl;
    cout<<"二叉树深度（递归）："<<GetDeepth1(T)<<endl;
    cout<<"二叉树深度（非递归）："<<GetDeepth2(T)<<endl;
    cout<<"二叉树结点总数："<<Count(T)<<endl;
    cout<<"二叉树叶子结点总数："<<LeafCount(T)<<endl;
    BTDestroy(T);
    return 0;
}

///2019.09.04
/**2019.09.05解决构建二叉树(含输入交互)栈溢出问题：是输入出了问题，输入数据要严格按照二叉树层次遍历的顺序输入，
并且应把空结点算入，所以输入n个非空结点，后面应补n+1个空结点
理论来源：n0+n1+n2 = 1+n1+2*n2
**/
