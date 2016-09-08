//
// Created by chenlei on 9/8/16.
//

#ifndef TEST_STD_THREADPOOL_H
#define TEST_STD_THREADPOOL_H

#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <condition_variable>
#include <vector>

#include "stdio.h"

using namespace std;

class ThreadPool {

private:

    /**
     * flg
     */
    bool stop;

    /**
     *  cache runnable
     */
    queue<function<void()>> queues;

    /**
     * condition_variable
     */
    condition_variable conditionVariable;

    /**
     *
     */
    vector<thread> works;


    /**
     * mutex
     */
    mutex _mutex;

public:
    /**
     *
     * @param threads
     * @return
     */
    ThreadPool(int threads = 4) : stop(false) {
        for (int i = 0; i < threads; ++i) {
            works.emplace_back(thread(bind(&ThreadPool::run, this)));
        }
    }


    /**
     *
     */
    void run() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> uniqueLock(_mutex);
                if (this->queues.empty() && !stop)conditionVariable.wait(uniqueLock);
                if (stop && queues.empty())return;// not empty

                if(!queues.empty()){
                    task = move(queues.front());
                    queues.pop();
                    task();//
                }

            }

        }
    }


    /**
     *
     * @param task
     */
    void add(const function<void()> &task) {
        unique_lock<mutex> uniqueLock(_mutex);
        queues.push(task);
        conditionVariable.notify_one();
    }


    ~ThreadPool() {

        {
            unique_lock<mutex> uniqueLock(_mutex);
            stop = true;
            conditionVariable.notify_all();
        }

        //wait to done!
        for (auto &th:works) {
            th.join();
        }

    }


};


#endif //TEST_STD_THREADPOOL_H
