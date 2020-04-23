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

class Rear
{
public:
    friend class Handler; //将Handler设置为Rear的友元类，实现H对R内数据的访问和修改
    friend class Front;   //将Front设置为Rear的友元类，实现F对R内数据的访问和修改
    //把本地文件的数据读入程序中的二维数组matrix
    void dataWrite();
    Type **dym_arr(Type **arr);
    Rear() //为各个矩阵申请空间
    {
        dis = dym_arr(dis);
        speed = dym_arr(speed);
        time = dym_arr(time);
        path = dym_arr(path);
        d = new Type[n];
    }
    ~Rear()
    {
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
private:
    Type **dis = NULL;
    Type **speed = NULL;
    Type **time = NULL;
    Type **path = NULL; //path[][]为中介点数组，可以通过它获取最短路径
    Type *d = NULL;     //顶点与集合S的最短距离
};

//把本地文件的数据读入程序中的二维数组matrix
void Rear::dataWrite()
{
    ifstream file1("dis.txt", ios::in); //打开文件指针
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file1 >> dis[i][j]; //将距离数据读入二维数组
    file1.close();                 //关闭文件指针
    ifstream file2("speed.txt", ios::in); //打开文件指针
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file2 >> speed[i][j]; //将速度数据读入二维数组
    file2.close();                 //关闭文件指针
}

Type **Rear::dym_arr(Type **arr)
{
    arr = new Type *[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new Type[n];
    return arr;
}

class Handler
{
public:
    Handler() {}
    void Time(Rear &r); //计算可达时间矩阵
    void floyd(Rear &r);    //对可达时间矩阵进行优化
    //prim（）默认顶点0为出发点，函数返回MST的边权之和及行走路线
    pair<Type, vector<pair<int, int>>> prim(Rear &r); 
    pair<Type, Type> asAndSd(Type **matrix);    //计算平均速度和可达时间标准差
    vector<int> getPath(Rear &r, int s, int t); //将prim（）隐含的中介点找出来
    double mttc(Rear& r, vector<vector<int>>& arr_mttc);//最小环城时间,去掉注释可显示路径
    double evaluate(Rear &r); //计算获得的交通数据的评分
};

void Handler::floyd(Rear &r)
{
    for (int i = 0; i < n; ++i) //初始化中介点矩阵
        for (int j = 0; j < n; ++j)
            r.path[i][j] = i; //中介点为自身说明I,J可直接连通
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (r.time[i][k] != INF && r.time[k][j] != INF && r.time[i][k] + r.time[k][j] < r.time[i][j])
                {
                    r.time[i][j] = r.time[i][k] + r.time[k][j];
                    r.path[i][j] = k; //记录中介点
                }
}

void Handler::Time(Rear &r)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (r.dis[i][j] == INF)
                r.time[i][j] = INF;
            else if (r.dis[i][j] == 0)
                r.time[i][j] = 0;
            else
                r.time[i][j] = r.dis[i][j] / r.speed[i][j];
        }
    }
}

vector<int> Handler::getPath(Rear &r, int s, int t)//将prim（）隐含的中介点找出来
{
    vector<int> res;
    if (s == t)
        return res;        //起点等于终点，返回为空
    res.push_back(t);      //先放入终点
    if (r.path[s][t] == s) //中介点等于起点，说明s与t直接连通
        res.push_back(s);
    else //s到t有中介点
    {
        int mid = r.path[s][t]; //记录下中介点
        while (mid != s)        //中介点等于起点时说明二者直接连通
        {
            res.push_back(mid);
            mid = r.path[s][mid];
        }
        res.push_back(s); //放入起点
    }
    return res;
}



pair<Type, Type> Handler::asAndSd(Type **matrix)
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
    //cout << sum << " " << cnt << endl;
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

//默认顶点0为出发点，函数返回MST的边权之和及行走路线
pair<Type, vector<pair<int, int>>> Handler::prim(Rear &r) //s为初始顶点
{
    Type ans = 0;                //存放最小生成树的边权之和
    vector<pair<int, int>> path; //存放最小生成树的路线,第一参数为起点，第二参数为终点
    fill(r.d, r.d + n, INF);     //初始化距离数组d
    r.d[0] = 0;
    int s = 0;
    bool *visit = new bool[n];
    visit[n] = false; //初始化标记数组visit
    for (int i = 0; i < n; ++i)
    {
        int t = -1, Min = INF;
        for (int j = 0; j < n; ++j) //找到未访问顶点中d[]最小的
            if (!visit[j] && r.d[j] < Min)
            {
                t = j;
                Min = r.d[j];
            }
        //找不到小于INF的d[u],则剩下的顶点和集合S不连通
        if (t == -1)
            return make_pair(-1, path);
        visit[t] = true; //标记u为已访问
        ans += r.d[t];   //将与集合距离最小的边加入最小生成树
        path.push_back(make_pair(s, t));
        for (int v = 0; v < n; ++v)
            //顶点v未访问 && t能到达v && 以t为中介点可以使v离集合S更近
            if (visit[v] == false && r.time[t][v] != INF && r.time[t][v] < r.d[v])
            {
                r.d[v] = r.time[t][v];
                s = t;
            }
    }
    return make_pair(ans, path);
}

double Handler::mttc(Rear& r, vector<vector<int>>& arr_mttc)//最小环城时间,去掉注释可显示路径
{
    double mttc = 0;
    int t1 = arr_mttc[0][0], s1 = arr_mttc[0][arr_mttc[0].size()-1];
    mttc += r.time[s1][t1];
    cout << s1 << "->" << t1 << endl;
    for(int i = 1; i < n - 1;++i)
    {
        int t2=arr_mttc[i][0], s2 =arr_mttc[i][arr_mttc[i].size()-1];
        if(s1==s2)
        {
            mttc += r.time[s1][t1];
            cout << t1 << "->" << s1 << endl;  
        }
        else
            s1 = s2; 
        mttc += r.time[s2][t2];  
        cout << s2 << "->" << t2 << endl;      
        t1 = t2;
    }
    return mttc;
}
double Handler::evaluate(Rear &r) //计算获得的交通数据的评分
{
    //===================计算优化后的平均可达时间和可达时间偏差率==================
    floyd(r); //计算attr和rtdr之前保证时间矩阵已优化
    pair<Type, Type> avg_time = asAndSd(r.time);
    //cout << "attr=" << avg_time.first << endl;
    //cout << "rtdr" << avg_time.second << endl;
    //==============从python程序生成的本地文件读取hlrr,mrcr,as,rrsdr的数据===========
    ifstream file("index_info.txt", ios::in); //打开文件指针
    double info[4];
    for (int i = 0; i < 4; i++)
        file >> info[i]; //将文件数据读入二维数组
    file.close();
    double grade = 0;
    //计算平均可达时间attr的得分
    if (avg_time.first > 1)
        grade += 60 * 0.3;
    else if (avg_time.first < 0.5)
        grade += 100 * 0.3;
    else
        grade += 80 * 0.3;
    //加上可达时间偏差率rtdr的得分
    if (avg_time.second > 40)
        grade += 60 * 0.1;
    else if (avg_time.second < 30)
        grade += 100 * 0.1;
    else
        grade += 80 * 0.1;
    //加上高延时运行时间占比hlrr的得分
    if (info[0] > 12)
        grade += 60 * 0.15;
    else if (info[0] < 8)
        grade += 100 * 0.15;
    else
        grade += 80 * 0.15;
    //加上拥堵路段里程比mrcr的得分
    if (info[1] > 2)
        grade += 60 * 0.15;
    else if (info[1] < 2)
        grade += 100 * 0.15;
    else
        grade += 80 * 0.15;
    //加上运行速度偏差率rrsdr的得分
    if (info[2] > 15)
        grade += 60 * 0.1;
    else if (info[2] < 10)
        grade += 100 * 0.1;
    else
        grade += 80 * 0.1;
    //加上平均行驶速度的得分
    if (info[3] > 32)
        grade += 100 * 0.2;
    else if (info[3] < 28)
        grade += 60 * 0.2;
    else
        grade += 80 * 0.2;
    return grade;
}

class Front
{
public:
    friend class Handler;   //将Handler设置为Front的友元函数，便于调用Handler内的函数
    map<int, string> cityMap;
    Front() {}
    ~Front() {}
    void gra_info();         //获取创建图所需的基本信息
    void show_gra_info();   //显示图的标号和实际地区的对应表
    //默认显示time矩阵内的数据,flag=1显示path，2显示dis,3显示speed,m<=n,默认m=n
    void print(Rear& r, int flag, int m);
    void showMid(vector<int> &shortestPath, int s, int t); //显示从s到t包含中介点的最短路径
    //显示从起点0到终点n的最小生成树的最短路径，并将其结果存储在二维数组作为返回值
    vector<vector<int>> showShortestPath(Handler& h, Rear& r, int size, vector<pair<int, int>> res);
};

//获取创建图所需的基本信息
void Front::gra_info()
{
    cout << "请输入图中顶点数：";
    cin >> n;
    cout << "请依次输入顶点标号对应的地区：" << endl;
    for (int i = 0; i < n; ++i)
    {
        string str;
        cout << i << "    ";
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

void Front::print(Rear& r, int flag=0, int m = n) //默认参数为顶点个数，也可以自己设置,但m<n
{
    Type** matrix;
    switch(flag)
    {
        case 1:
            matrix = r.path;
            break;
        case 2:
            matrix = r.dis;
            break;
        case 3:
            matrix = r.speed;
            break;
        default:
            matrix = r.time;
            break;
    }
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

void Front::showMid(vector<int> &shortestPath, int s, int t)//显示从s到t包含中介点的最短路径
{
    int sP_size = shortestPath.size();
    for (int i = sP_size - 1; i > 0; --i)
    {
        cout << shortestPath[i] << "->";
    }
    cout << shortestPath[0]<<endl;
}

//显示从起点0到终点n的最小生成树的最短路径，并将其结果存储在二维数组作为返回值
vector<vector<int>> Front::showShortestPath(Handler& h, Rear& r, int size, vector<pair<int, int>> res)
{
    vector<vector<int>> arr_mttc;
    for (int i = 0; i < size; ++i)
    {
        int s = res[i].first, t = res[i].second;
        if (s == t)
            continue;
        else
        {
            vector<int> shortestPath = h.getPath(r, s, t);
            arr_mttc.push_back(shortestPath);
            showMid(shortestPath, s, t);
            //cout << "->";
        }
    }
    return arr_mttc;
}


int main()
{
    Front f; //前端显示页面
    //=======================获取图的信息===============================
    f.gra_info();
    //=======================读取数据并写入数组========================
    Rear r; //后端存储数据
    r.dataWrite();
    cout << "初始距离矩阵为：" << endl;
    f.print(r, 2);
    cout << "初始速度矩阵为：" << endl;
    f.print(r, 3);
    //===============计算平均可达时间和可达时间偏差率================================
    Handler h; //处理端，对数据进行处理
    h.Time(r);
    cout << "初始可达时间矩阵为：" << endl;
    f.print(r);
    //===================获取最短可达时间并记录中间节点==========================
    h.floyd(r);
    cout << "Floyd算法处理后的可达时间矩阵为：" << endl;
    f.print(r);
    cout << "走过的中间节点矩阵为：" << endl;
    f.print(r, 1);
    //====================展示围绕城市一周走过的路径====================
    pair<Type, vector<pair<int, int>>> res = h.prim(r);
    cout << "最小生成树的边权之和为：" << res.first << endl;
    int size = res.second.size();
    //arr_mttc存储最小生成树的行走路线
    f.show_gra_info();
    cout << "最小生成树的路径为：" << endl;
    vector<vector<int>> arr_mttc = f.showShortestPath(h, r, size, res.second);
    //====================计算最小环城时间和最终得分======================
    cout << "环城路线为:" << endl;
    double mttc = h.mttc(r, arr_mttc);
    cout << "最小环城时间：" << mttc << endl;
    cout << "交通情况的最终得分：" << h.evaluate(r) << endl;
    system("pause");
    return 0;
}

/*
VSCode对于析构函数不输出其内容
*/