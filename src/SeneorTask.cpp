#include"all.h"
class SensorTask{
public:
    virtual void run()=0;
    virtual void callback(int msg)=0;
    void stop(){
        is=false;
    }
    SensorTask() : running(&SensorTask::run,this){},ready(false){};
    virtual ~SensorTask(){
        stop();
        if(running.joinable()){
            running.join();
        }
    }
    int key;
    std::atomic<int>*p_in;
    std::atomic<int>*p_out;
    std::atomic<bool>is{true};
    std::thread running;
    bool ready;
};

class Taskfilter:public SensorTask{
    void run()override{
        while(is){
            if(*p_in!=0){
                std::lock_guard<mutex> lock(mtx);
                *p_out=*p_in+1;
                *p_in=0;
                cout<<"write filter "<<key<<": "<<*p_out<<endl;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }
    void callback(int msg)override{
        *p_in=msg;
    }
    ~Taskfilter()override{
        stop();
        if(running.joinable()){
            running.join();
        }
        if(p_in!=nullptr&&p_out!=nullptr){
            p_in=nullptr;
            p_out=nullptr;
        }
    }
};

class TaskGain:public SensorTask{
    void run()override{
        while(is){
            if(*p_in!=0){
                std::lock_guard<mutex> lock(mtx);
                *p_out=*p_in*k;
                *p_in=0;
                cout<<"wriet gain "<<key<<": "<<*p_out<<endl;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }
    void callback(int msg)override{
        k=msg;
        *p_in=1;
    }
    ~TaskGain()override{
        stop();
        if(running.joinable()){
            running.join();
        }
        if(p_in!=nullptr&&p_out!=nullptr){
            p_in=nullptr;
            p_out=nullptr;
        }
    }
    int k;
};

class TaskDelayBuffer:public SensorTask{
    void run()override{
        while(is){
            if(*p_in!=0){
                std::lock_guard<mutex> lock(mtx);
                int t=*p_in;
                *p_in=0;
                *p_out=t;
                cout<<"write delay "<<key<<": "<<*p_out<<endl;
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                *p_out=t+1;
                cout<<"write delay "<<key<<": "<<*p_out<<endl;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }
    void callback(int msg)override{
        *p_in=msg;
    }
    ~TaskDelayBuffer()override{
        stop();
        if(running.joinable()){
            running.join();
        }
        if(p_in!=nullptr&&p_out!=nullptr){
            p_in=nullptr;
            p_out=nullptr;
        }
    }
};
