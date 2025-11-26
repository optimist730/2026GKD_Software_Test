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
                cout<<"Taskfilter "<<key<<" "<<*p_out<<endl;
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
