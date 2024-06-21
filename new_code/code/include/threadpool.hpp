#pragma once
#include<iostream>
#include<functional>
#include<thread>
#include<atomic>
#include<mutex>
#include<queue>
#include<condition_variable>

void showThreadid(){
    std::cout<<"thread id is = "<<std::this_thread::get_id()<<std::endl;
}

struct Task{
    template<typename Func,typename... Argc>
    Task(Func&& func,Argc&&... argc) : m_func(std::bind(std::forward<Func>(func),std::forward<Argc>(argc)...)){}
    void operator()(){
        m_func();
    }
    std::function<void()> m_func;
};

struct TaskQuene{
    template<typename Func,typename... Argc>
    void addTask(Func&& func,Argc&&... argc){
        m_task_quene.emplace(std::forward<Func>(func),std::forward<Argc>(argc)...);
    }
    void addTask(Task t){
        m_task_quene.push(t);
    }
    void run(){
        while(m_task_quene.empty()){
            auto task = m_task_quene.front();
            m_task_quene.pop();
        }
    }
    std::queue<Task> m_task_quene;
};

struct FuncClass{
    static void test(){
        std::cout<<"test"<<std::endl;
          showThreadid();
    }
    void test2(){
        std::cout<<"test2"<<std::endl;
          showThreadid();
    }
    void test3(int a){
         std::cout<<"test3 "<<a <<std::endl;
           showThreadid();
    }
};

class ThreadPool
{
public:
    ThreadPool(int size = 4){
        addThread(size);
    }
    ~ThreadPool(){
        for (auto &v: m_threads){
            if (v.joinable())
                v.join();
        }
    }
    template<typename Func,typename... Argc>
    void addTask(Func&& func,Argc&&... argc){
        std::lock_guard<std::mutex> m(m_lock);
        m_tasks.addTask(func,argc...);
        m_conditon_var.notify_one();
    }
    void addThread(int size)
    {
        for (int i = 0; i < size; i++)
        {
            m_threads.emplace_back([&]()
                                   {
                    while(m_run){
                        {
                            std::unique_lock<std::mutex> l(m_lock);
                            m_conditon_var.wait(l,[&](){
                                return !m_run || !m_tasks.m_task_quene.empty();
                            });
                            auto task = m_tasks.m_task_quene.front();
                            task();
                            m_tasks.m_task_quene.pop();
                        }
                    } });
        }
    }

private:
    std::atomic<bool> m_run = true;
    std::atomic<int> m_sleep_thread_cn = 0;
    std::vector<std::thread> m_threads;
    std::mutex m_lock;
    TaskQuene m_tasks;
    std::condition_variable m_conditon_var;
};



void test_task(){
     auto func = [](int a){
        std::cout<<"a = "<<a<<std::endl;
        showThreadid();
    };

     auto func1 = [](int a,int b){
        std::cout<<"a + b = "<<a + b<<std::endl;
        showThreadid();
    };
    ThreadPool tp(4);
    tp.addTask(func,1);
    tp.addTask(func1,1,2);
    tp.addTask(&FuncClass::test);
    FuncClass f;
    tp.addTask(&FuncClass::test3,f,99);

    // TaskQuene q;
    // q.addTask(func,1);
    // q.addTask(func1,1,2);
    // q.addTask(&FuncClass::test);
    // FuncClass f;
    // q.addTask(&FuncClass::test3,f,99);
    // q.run();
}