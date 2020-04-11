#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 99999;
typedef double Type;

void print(Type **matrix, int n)
{
    cout.setf(ios::fixed);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << fixed << setprecision(2) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Floyd(Type **dis, int n)
{

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

void dataWrite(Type **matrix, int n, string filename)
{
    ifstream file(filename, ios::in);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            file >> matrix[i][j];
        }
    }
    file.close();
}

void Time(Type **time, int n, Type **dis, Type **speed)
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

pair<Type, Type> ASAndSd(Type **matrix, int n)
{
    pair<Type, Type> res;
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
    res.first = attr;

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
    res.second = rtdr;
    return res;
}

int main()
{
    int n = 0;
    cout << "请输入图中顶点数：";
    cin >> n;
    Type **dis = new Type *[n];
    for (int i = 0; i < n; ++i)
        dis[i] = new Type[n];
    dataWrite(dis, n, "dis.txt");
    //print(dis, n);
    Type **speed = new Type *[n];
    for (int i = 0; i < n; ++i)
        speed[i] = new Type[n];
    dataWrite(speed, n, "speed.txt");
    //print(speed, n);
    Type **time = new Type *[n];
    for (int i = 0; i < n; ++i)
        time[i] = new Type[n];
    Time(time, n, dis, speed);
    print(time, n);
    Floyd(time, n);
    print(time, n);
    pair<Type, Type> res = ASAndSd(time, n);
    cout << res.first << endl;
    cout << res.second << endl;
    system("pause");
    return 0;
}