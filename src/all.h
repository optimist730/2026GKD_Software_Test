#include<stdio.h>
#include<thread>
#include<mutex>
#include<atomic>
#include<vector>
#include<chrono>
#include<iostream>
#include<condition_variable>
using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::mutex;
std::condition_variable cv;
mutex mtx;