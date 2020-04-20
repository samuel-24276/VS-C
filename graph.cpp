#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int INF = 99999;
static int n = 0; //将顶点数目设为全局变量，则很多函数可以少一个参数
typedef double Type;

class Front
{
public:
    map<int, string> cityMap;
    Front() {}
    ~Front()
    {
        cout << "Front内存已回收" << endl;
    }
    //获取创建图所需的基本信息
    void gra_info(int &n);
    //显示图的标号和实际地区的对应表
    void show_gra_info();
    void print(Type **matrix, int m); //默认参数为顶点个数，也可以自己设置,但m<n
    void showShortestPath(vector<int>& shortestPath, int s, int t);
};

//获取创建图所需的基本信息
void Front::gra_info(int &n)
{
    cout << "请输入图中顶点数：";
    cin >> n;
    cout << "请依次输入顶点标号对应的地区：" << endl;
    for (int i = 0; i < n; ++i)
    {
        string str;
        cout << "  " << i << endl;
        cin >> str;
        cityMap.insert({i, str});
    }
}

//显示图的标号和实际地区的对应表
void Front::show_gra_info()
{
    cout << "顶点标号" << setw(20) << "对应地区" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << i << setw(20) << cityMap[i] << endl;
    }
}

void Front::print(Type **matrix, int m = n) //默认参数为顶点个数，也可以自己设置,但m<n
{
    cout.setf(ios::fixed);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << fixed << setprecision(2) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Front::showShortestPath(vector<int>& shortestPath, int s, int t)
{
    int sP_size = shortestPath.size();
    for (int i = sP_size - 1; i > 0; --i)
    {
        cout << shortestPath[i] << "->";
    }
    cout << shortestPath[0];
}

class Rear
{
public:
    Type **dis = NULL;
    Type **speed = NULL;
    Type **time = NULL;
    Type **path = NULL; //path[][]为中介点数组，可以通过它获取最短路径
    Type *d = NULL; //顶点与集合S的最短距离
    Rear()              //为各个矩阵申请空间
    {
        dis = dym_arr(dis);
        speed = dym_arr(speed);
        time = dym_arr(time);
        path = dym_arr(path);
        d = new Type[n];
    }
    ~Rear()
    {
        cout << "内存已回收" << endl;
        for (int i = 0; i < n; ++i)
        {
            delete[] dis[i];
            delete[] speed[i];
            delete[] time[i];
            delete[] path[i];
        }
        delete[] dis;
        delete[] speed;
        delete[] time;
        delete[] path;
        delete[] d;
    }
    //把本地文件的数据读入程序中的二维数组matrix
    void dataWrite(Type **matrix, string filename);
    Type **dym_arr(Type **arr);
};

//把本地文件的数据读入程序中的二维数组matrix
void Rear::dataWrite(Type **matrix, string filename)
{
    ifstream file(filename, ios::in); //打开文件指针
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> matrix[i][j]; //将文件数据读入二维数组
    file.close();                 //关闭文件指针
}

Type **Rear::dym_arr(Type **arr)
{
    arr = new Type *[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new Type[n];
    return arr;
}

class Handle
{
public:
    Handle(){}
    void Floyd(Type **dis, Type **path);
    void Time(Type **time, Type **dis, Type **speed);
    pair<Type, vector<pair<int, int>>> prim(Type **time, Type *d); //s为初始顶点
    pair<Type, Type> ASAndSd(Type **matrix);    //计算平均速度和可达时间标准差
    vector<int> getPath(Type **path, int s, int t);
};

void Handle::Floyd(Type **dis, Type **path)
{
    for (int i = 0; i < n; ++i) //初始化中介点矩阵
        for (int j = 0; j < n; ++j)
            path[i][j] = i; //中介点为自身说明I,J可直接连通
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = k; //记录中介点
                }
}

void Handle::Time(Type **time, Type **dis, Type **speed)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dis[i][j] == INF)
                time[i][j] = INF;
            else if (dis[i][j] == 0)
                time[i][j] = 0;
            else
                time[i][j] = dis[i][j] / speed[i][j];
        }
    }
}

vector<int> Handle::getPath(Type **path, int s, int t)
{
    vector<int> res;
    if (s == t)
        return res;      //起点等于终点，返回为空
    res.push_back(t);    //先放入终点
    if (path[s][t] == s) //中介点等于起点，说明s与t直接连通
        res.push_back(s);
    else //s到t有中介点
    {
        int mid = path[s][t]; //记录下中介点
        while (mid != s)      //中介点等于起点时说明二者直接连通
        {
            res.push_back(mid);
            mid = path[s][mid];
        }
        res.push_back(s); //放入起点
    }
    return res;
}

pair<Type, Type> Handle::ASAndSd(Type **matrix)
{
    Type sum = 0, attr = 0, mrtv = 0, sdart = 0, rtdr = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            sum += matrix[i][j];
        }
    }
    int cnt = 0, m = n;
    while (m)
        cnt += --m;
    attr = sum / cnt;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            mrtv += pow(matrix[i][j] - attr, 2);
        }
    }
    mrtv /= cnt;
    sdart = sqrt(mrtv);
    rtdr = sdart / attr;
    return make_pair(attr, rtdr);
}

//默认顶点0为出发点，函数返回MST的边权之和行走路线
pair<Type, vector<pair<int, int>>> Handle::prim(Type **time, Type *d) //s为初始顶点
{
    Type ans = 0;                //存放最小生成树的边权之和
    vector<pair<int, int>> path; //存放最小生成树的路线,第一参数为起点，第二参数为终点
    fill(d, d + n, INF);         //初始化距离数组d
    d[0] = 0;
    int s = 0;
    bool *visit = new bool[n];
    visit[n] = false; //初始化标记数组visit
    for (int i = 0; i < n; ++i)
    {
        int t = -1, Min = INF;
        for (int j = 0; j < n; ++j) //找到未访问顶点中d[]最小的
            if (!visit[j] && d[j] < Min)
            {
                t = j;
                Min = d[j];
            }
        //找不到小于INF的d[u],则剩下的顶点和集合S不连通
        if (t == -1)
            return make_pair(-1, path);
        visit[t] = true; //标记u为已访问
        ans += d[t];     //将与集合距离最小的边加入最小生成树
        path.push_back(make_pair(s, t));
        for (int v = 0; v < n; ++v)
            //顶点v未访问 && t能到达v && 以t为中介点可以使v离集合S更近
            if (visit[v] == false && time[t][v] != INF && time[t][v] < d[v])
            {
                d[v] = time[t][v];
                s = t;
            }
    }
    return make_pair(ans, path);
}

int main()
{
    Front f; //前端
    f.gra_info(n);
    f.show_gra_info();
    Rear r;
    //=======================读取数据并写入数组========================
    r.dataWrite(r.dis, "dis.txt");
    //f.print(r.dis, n);
    r.dataWrite(r.speed, "speed.txt");
    //f.print(r.speed, n);
    //===============计算平均可达时间================================
    Handle h;
    h.Time(r.time, r.dis, r.speed);
    cout << "初始化的可达时间矩阵为：" << endl;
    f.print(r.time);
    pair<Type, Type> avg_time = h.ASAndSd(r.time);
    cout << "attr=" << avg_time.first << endl;
    cout << "rtdr" << avg_time.second << endl;
    //===================获取最短可达时间并记录中间节点==========================
    h.Floyd(r.time, r.path);
    cout << "Floyd算法处理后的可达时间矩阵为：" << endl;
    f.print(r.time);
    cout << "走过的中间节点矩阵为：" << endl;
    f.print(r.path);
    
    //====================展示围绕城市一周走过的路径====================
    pair<Type, vector<pair<int, int>>> res = h.prim(r.time, r.d);
    cout << "最小生成树的边权之和为：" << res.first << endl;
    int size = res.second.size();
    for (int i = 0; i < size; ++i)
    {
        int s = res.second[i].first, t = res.second[i].second;
        if (s == t)
            continue;
        else
        {
            vector<int> shortestPath = h.getPath(r.path, s, t);
            f.showShortestPath(shortestPath, s, t);
            cout << endl;
            //cout << "->";
        }
    }
    cout << endl;
    system("pause");
    return 0;
}

/*
VSCode对于析构函数不输出其内容
*/