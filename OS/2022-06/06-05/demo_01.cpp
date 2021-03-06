/**
 * @file demo_01.cpp
 * @author 杨昌松 (2020051615325@cqnu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2022-06-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define MaxNumber 2710
#define MaxTrackNum 0x64
class Disk
{
private:
    int TrackNum;             // 磁道数
    int StartTrack;           // 开始磁道
    int TrackOrder[MaxTrackNum];   // 初始磁道顺序
    int VisitedOrder[MaxTrackNum]; // 被访问的磁道顺序
    int Sum_Distance;         // 总寻道距离
    int MoveDistance[MaxTrackNum]; // 每个磁道移动距离
    bool IsVisited[MaxTrackNum];   // 是否被访问
    int Average_Distance;     // 平均寻道距离
public:
    Disk();
    ~Disk();
    void Initialize();          // 初始化
    void Enter();               // 输入初始数据
    void Print();               // 打印结果
    int Distance(int a, int b); // 计算距离
    void FCFS();                // 先来先服务
    void SSTF();                // 最短寻道时间优先
    void SCAN();                // 扫描磁道
    void CSCAN();               // 循环扫描
};
Disk::Disk()
{
    cout << "Disk()" << endl;
}
Disk::~Disk()
{
    cout << "~Disk()" << endl;
}
/* 初始化 */
void Disk::Initialize()
{
    for (int i = 0; i < TrackNum; i++)
    {
        MoveDistance[i] = 0;
        VisitedOrder[i] = TrackOrder[i];
        IsVisited[i] = false;
    }
    Sum_Distance = 0;
    Average_Distance = 0;
}
/* 输入 */
void Disk::Enter()
{
    cout << "Entry TrackNum:";
    cin >> TrackNum; // 磁道个数
    cout << "Entry TrackOrder:";
    for (int i = 0; i < TrackNum; i++)
    {
        cin >> TrackOrder[i]; // 输入磁盘队列
    }
    cout << "Entry StartTrack:";
    cin >> StartTrack; // 开始磁道号
}
/* 计算距离 */
int Disk::Distance(int a, int b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}
/* 打印 */
void Disk::Print()
{
    cout << "TrackNum:" << TrackNum << endl;     // 磁道数
    cout << "StartTrack:" << StartTrack << endl; // 开始磁道号
    cout << "TrackOrder:";
    for (int i = 0; i < TrackNum; i++)
    {
        cout << setw(4) << VisitedOrder[i]; // 访问磁道顺序
    }
    cout << endl;
    cout << "MoveDistance:";
    for (int i = 0; i < TrackNum; i++)
    {
        cout << setw(4) << MoveDistance[i]; // 移动距离
    }
    cout << endl;
    // 总距离
    // cout << "Sum_Distance:" << Sum_Distance << endl;
    // 平均寻道距离
    cout << "Average_Distance:" << Average_Distance << endl;
}
/* 先来先服务 */
void Disk::FCFS()
{
    cout << endl;
    cout << "FCFS" << endl;
    for (int i = 0; i < TrackNum; i++)
    {
        Sum_Distance += Distance(StartTrack, TrackOrder[i]);
        MoveDistance[i] = Distance(StartTrack, TrackOrder[i]);
        StartTrack = TrackOrder[i];
    }

    Average_Distance = Sum_Distance * 1.0 / TrackNum;
}
/* 最短寻道时间优先 */
void Disk::SSTF()
{
    cout << endl;
    cout << "SSTF" << endl;
    int CurrentTrack = StartTrack;
    int i, j, pointMin;
    int disTemp[MaxTrackNum];

    for (i = 0; i < TrackNum; i++)
    {
        for (j = 0; j < TrackNum; j++)
        {
            if (!IsVisited[i])
            {
                disTemp[j] = Distance(CurrentTrack, TrackOrder[j]);
            }
            else
            {
                disTemp[j] = MaxNumber;
            }
        }

        pointMin = 0;
        for (j = 0; j < TrackNum; j++)
        {
            if (disTemp[pointMin] > disTemp[j])
                pointMin = j; // 指向最小的位置
        }
        // 给访问序列赋值
        VisitedOrder[i] = TrackOrder[pointMin];
        // 计算移动距离
        MoveDistance[i] = Distance(CurrentTrack, TrackOrder[pointMin]);
        // 累计距离
        Sum_Distance += MoveDistance[i];
        // 更新当前磁道号
        CurrentTrack = TrackOrder[pointMin];
        // 更新访问标志
        IsVisited[pointMin] = true;
    }

    Average_Distance = Sum_Distance * 1.0 / TrackNum;
}
/* 循环隧道 */
void Disk::CSCAN()
{
    bool direction;
    cout << endl;
    cout << "CSCAN" << endl;
    cin >> direction;

    int SortTrackOrder[MaxTrackNum];
    int i, j, temp, tempIndex;
    for (i = 0; i < TrackNum; i++)
    {
        SortTrackOrder[i] = TrackOrder[i];
    }
    // 冒泡排序
    for (i = TrackNum - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (SortTrackOrder[j] >= SortTrackOrder[j + 1])
            {
                temp = SortTrackOrder[j];
                SortTrackOrder[j] = SortTrackOrder[j + 1];
                SortTrackOrder[j + 1] = temp;
            }
        }
    }

    int point = 0;
    while (StartTrack >= SortTrackOrder[point])
    {
        point++;
    }

    int count = 0;
    int currentTrack = StartTrack;
    if (direction == 0)
    {
        cout << "add" << endl;
        for (i = point; i < TrackNum; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[count];
            count++;
        }

        for (i = 0; i < point; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[count];
            count++;
        }
    }
    else if (direction == 1)
    {
        cout << "reduce" << endl;
        for (i = 0; i < point; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[count];
            count++;
        }

        for (i = point; i < TrackNum; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[count];
            count++;
        }
    }
    for (i = 0; i < TrackNum; i++)
    {
        Sum_Distance += MoveDistance[i];
    }
    Average_Distance = Sum_Distance * 1.0 / TrackNum;
}
/* 扫描隧道 */
void Disk::SCAN()
{
    bool direction = 0;
    cout << endl;
    cout << "SCAN" << endl;
    cout << "Choose direction, 0-add, 1-reduce: " << endl;
    cin >> direction;

    int i, j, temp, tempIndex;
    int SortTrackOrder[MaxTrackNum];
    for (i = 0; i < TrackNum; i++)
    {
        SortTrackOrder[i] = TrackOrder[i];
    }

    // 冒泡排序
    for (i = 0; i < TrackNum; i++)
    {
        for (j = i; j < TrackNum; j++)
        {
            if (SortTrackOrder[i] > SortTrackOrder[j])
            {
                temp = SortTrackOrder[i];
                SortTrackOrder[i] = SortTrackOrder[j];
                SortTrackOrder[j] = temp;
            }
        }
    }
    // 找到第一个未访问的磁道

    int point = 0;
    while (StartTrack >= SortTrackOrder[point])
    {
        point++;
    }

    int count = 0;
    int currentTrack = StartTrack;

    if (direction == 0)
    { // 向增大的方向
        cout << "add" << endl;
        for (i = point; i < TrackNum; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[i];
            count++;
        }

        for (i = point - 1; i >= 0; i--)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[i];
            count++;
        }
    }
    else if (direction == 1)
    { // 向减小的方向
        cout << "reduce" << endl;
        for (i = point - 1; i >= 0; i--)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[i];
            count++;
        }

        for (i = point; i < TrackNum; i++)
        {
            VisitedOrder[count] = SortTrackOrder[i];
            MoveDistance[count] = Distance(currentTrack, SortTrackOrder[i]);
            currentTrack = VisitedOrder[i];
            count++;
        }
    }

    for (i = 0; i < TrackNum; i++)
    {
        Sum_Distance += MoveDistance[i];
    }

    Average_Distance = Sum_Distance * 1.0 / TrackNum;
}

int main()
{
    Disk disk;
    disk.Enter();
    disk.Initialize();
    // disk.FCFS();
    // disk.Print();
    // disk.SSTF();
    // disk.Print();
    // disk.SCAN();
    // disk.Print();
    disk.CSCAN();
    disk.Print();
    return 0;
}