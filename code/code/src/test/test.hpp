#include"inc.h"
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include<functional>

#define MAX_EVENTS 10

typedef std::function<void()> CallBackFunc;

void Show(std::string msg){
    std::cout<<msg<<std::endl;
}

class Channel
{
  public:
        Channel(CallBackFunc func):_callBack(func){

        }
        ~Channel(){

        }
        void handleEvent();
  private:
        CallBackFunc _callBack;
};


void Channel::handleEvent(){
    _callBack();
}

void test_clock() {
    Channel *ch = new Channel(std::bind(Show,"345"));
    // 创建定时器文件描述符，使用 CLOCK_REALTIME 时钟，并设置为非阻塞模式
    int timer_fd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if (timer_fd == -1) {
        perror("timerfd_create");
        exit(EXIT_FAILURE);
    }

    // 创建 epoll 实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(timer_fd);
        exit(EXIT_FAILURE);
    }

    // 将定时器文件描述符添加到 epoll 实例中进行监视
    struct epoll_event event;
    event.events = EPOLLIN; // 监听可读事件
    // event.data.fd = timer_fd;
    event.data.ptr = ch;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event) == -1) {
        perror("epoll_ctl");
        close(epoll_fd);
        close(timer_fd);
        exit(EXIT_FAILURE);
    }

    // 设置定时器参数（2秒后开始，每5秒触发一次）
    struct itimerspec timer_spec;
    timer_spec.it_value.tv_sec = 1;
    timer_spec.it_value.tv_nsec = 0;
    timer_spec.it_interval.tv_sec = 5;
    timer_spec.it_interval.tv_nsec = 0;

    // 启动定时器
    if (timerfd_settime(timer_fd, 0, &timer_spec, NULL) == -1) {
        perror("timerfd_settime");
        close(epoll_fd);
        close(timer_fd);
        exit(EXIT_FAILURE);
    }

    // 创建用于接收事件的缓冲区
    struct epoll_event events[MAX_EVENTS];

    // 循环等待事件发生
    while (1) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, 10000);
        if (num_events == -1) {
            perror("epoll_wait");
            close(epoll_fd);
            close(timer_fd);
            exit(EXIT_FAILURE);
        }

        // 处理收到的事件
        for (int i = 0; i < num_events; ++i) {
            // if (events[i].data.fd == timer_fd) 
            {
                // 从定时器文件描述符中读取定时器事件计数
                uint64_t expirations;
                ssize_t ret = read(timer_fd, &expirations, sizeof(expirations));
                if (ret == -1) {
                    perror("read");
                    close(epoll_fd);
                    close(timer_fd);
                    exit(EXIT_FAILURE);
                }
                Channel *callChan = (Channel*)events[i].data.ptr;
                callChan->handleEvent();

                // struct itimerspec timer_spec;
                // timer_spec.it_value.tv_sec = 0;
                // timer_spec.it_value.tv_nsec = 0;
                // timer_spec.it_interval.tv_sec = 0;
                // timer_spec.it_interval.tv_nsec = 0;

                // // 启动定时器
                // if (timerfd_settime(timer_fd, 0, &timer_spec, NULL) == -1)
                // {
                //     perror("timerfd_settime");
                //     close(epoll_fd);
                //     close(timer_fd);
                //     exit(EXIT_FAILURE);
                // }
                printf("Timer expired. Number of expirations: %llu\n", (unsigned long long)expirations);
            }
        }
    }

    // 关闭文件描述符并退出
    close(epoll_fd);
    close(timer_fd);
}


// #include <iostream>
// #include <thread>
// #include <queue>
// #include <vector>
// #include <mutex>
// #include <future>
// #include <chrono>
// #include <numeric>
// #include <algorithm>
// #include<memory>
// #include<map>
// #pragma pack(4)

// using namespace std;
// std::mutex m;
// std::condition_variable cond;
// void func(std::queue<int>& q) {
// 	while (1) {
// 		std::unique_lock<std::mutex> lk(m);
// 		if (!q.empty()) {
// 			cond.wait(lk, [&]() {return !q.empty(); });
// 			int a = q.front();
// 			q.pop();
// 			std::cout << a << std::endl;
// 		}
// 	}
// }

// void func1(std::queue<int>& q) {
// 	for (int i = 1; i < 1000; i++) {
// 		q.push(i);
// 	}
// 	cond.notify_all();
// }


// typedef std::function<void()> FUNC;
// std::vector<FUNC> FuncVec;

// template<typename F, typename... A>
// auto TestFunc(F f, A... argc)->decltype(f(argc...)) {
// 	using FuncType = decltype(f(argc...));
// 	auto tempFunc = std::bind(std::forward<F>(f), std::forward<A>(argc)...);

// 	FuncVec.push_back(tempFunc);
// 	return tempFunc();
// }

// template<typename F, typename... A>
// FUNC FuncPackage(F f, A... argc) {
// 	using FuncType = decltype(f(argc...));
// 	auto tempFunc = std::bind(std::forward<F>(f), std::forward<A>(argc)...);
// 	return tempFunc;
// }

// int func_1(int a, int b) {
// 	cout << "func_1 thread id= " << std::this_thread::get_id() << endl;
// 	return a + b;
// }

// int func_2(int a) {
// 	cout << "func_2  thread id= " << std::this_thread::get_id() << endl;
// 	return a;
// }

// void func_3() {
// 	cout << "func_3  thread id= " << std::this_thread::get_id()<< endl;
// }

// std::queue<FUNC> taskQuene;


// void func_4(std::queue<FUNC>& q) {
// 	while (1) {
// 		{
// 			std::unique_lock<std::mutex> lk(m);
// 			if (!q.empty()) {
// 				//cond.wait(lk, [&]() {return !q.empty(); });
// 				auto func = q.front();
// 				q.pop();
// 				func();
// 			}
// 		}
// 		this_thread::sleep_for(std::chrono::milliseconds(1000));
// 	}
// }


// int main() {
// 	std::vector<char> buff;
// 	buff.resize(1024);
// 	string msg = "111234";
// 	//std::copy(msg.c_str(), msg.c_str() + msg.size(), buff.begin());
// 	std::copy(msg.begin(),msg.end(), buff.begin());
// 	cout << buff[4] << endl;
// 	//auto a = FuncPackage(std::bind(func_2,std::placeholders::_1),1);
// 	//auto b = FuncPackage(func_3);
// 	//auto c = FuncPackage(func_1,11,11);
// 	//taskQuene.push(a);
// 	//taskQuene.push(b);
// 	//taskQuene.push(c);
// 	//cond.notify_all();

// 	//std::thread t1(func_4, std::ref(taskQuene));
// 	//cout <<"t1 id = "<< t1.get_id() << endl;
// 	//std::thread t2(func_4, std::ref(taskQuene));
// 	//cout << "t2 id = " << t2.get_id() << endl;

// 	//t1.join();
// 	//t2.join();

// 	////FuncVec.push_back(b);
// 	//for (auto v : FuncVec) {
// 	//	v();
// 	//}
// 	//std::queue<int> q;
	
// 	//std::vector<std::thread> ts;
// 	//ts.emplace_back(func1, std::ref(q));
// 	//for (int i = 1; i < 10; i++) {
// 	//	ts.emplace_back(func, std::ref(q));
// 	//}
// 	//for (auto& v : ts) { 
// 	//	if (v.joinable()) {
// 	//		v.join();
// 	//	}
// 	//}


// 	//std::promise<int> pm;
// 	//std::future<int> fu = pm.get_future();

// 	//auto tempFunc = [](std::promise<int> pm) {
// 	//	std::vector<int> vec{ 1,3,4,6 };
// 	//	int sunm = std::accumulate(vec.begin(), vec.end(), 0);
// 	//	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// 	//	pm.set_value(sunm);
// 	//};
// 	//
// 	//std::thread t1(tempFunc, std::move(pm));
// 	//cout << "async get " << fu.get() << endl;
// 	//t1.join();

// 	//struct A {
// 	//	~A() {
// 	//		cout << "123" << endl;
// 	//	}
// 	//};

// 	//{
// 	//	//std::shared_ptr<A> s_ptr = std::make_shared<A>();

// 	//}
// 	//std::map<int, std::shared_ptr<A>> temp;

// 	//{
// 	//	std::shared_ptr<A> ss_ptr = std::make_shared<A>();
// 	//	temp[1] = ss_ptr;
// 	//}
// 	//std::cout << "ss use_count = " << ss_ptr.use_count() << endl;

// 	//temp.erase(1);

// 	//std::cout << "ss after use_count = " << ss_ptr.use_count() << endl;



// 	//std::shared_ptr<int> s_ptr = std::make_shared<int>(5);
// 	//std::weak_ptr<int> w_ptr = s_ptr;
// 	///*if (w_ptr.lock()) */{
// 	//	std::shared_ptr<int> s = w_ptr.lock();
// 	//	int* p = s.get();
// 	//	*p = 10;
// 	//	cout << *s << endl;
// 	//}
// 	//std::cout <<"use_count = "<< s_ptr.use_count() << endl;


// }