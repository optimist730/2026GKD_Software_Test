#include<stdio.h>
#include<thread>
#include<mutex>
#include<atomic>
#include<vector>
#include<chrono>
#include<iostream>
#include<condition_variable>
#include<string>
using std::cout;
using std::endl;
using std::cin;
using std::thread;
using std::vector;
using std::mutex;
std::condition_variable cv;
mutex mtx;
class SensorTask{
public:
    virtual void run()=0;
    virtual void callback(int msg)=0;
    void stop(){}
    SensorTask() : running(&SensorTask::run,this){},ready(false){};
    virtual ~SensorTask(){}
    int key;
    std::atomic<int>*p_in;
    std::atomic<int>*p_out;
    std::atomic<bool>is{true};
    std::thread running;
    bool ready;
};
class TaskFilter:public SensorTask{
    void run()override{}
    void callback(int msg)override{}
    ~TaskFilter()override{}
};
class TaskGain:public SensorTask{
    void run()override{}
    void callback(int msg)override{}
    ~TaskGain()override{}
};
class TaskDelayBuffer:public SensorTask{
    void run()override{}
    void callback(int msg)override{}
    ~TaskDelayBuffer()override{}
};
class Taskmanager{
public:
    void add(){}
    void pop(){}
    void callbackuse() {}
    std::atomic<int>out{0};
    vector<std::unique_ptr<std::atomic<int>>>b_n;
    vector<SensorTask*>tasklist;
};