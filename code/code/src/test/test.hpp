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
    timer_spec.it_value.tv_sec = 10;
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
                printf("Timer expired. Number of expirations: %llu\n", (unsigned long long)expirations);
            }
        }
    }

    // 关闭文件描述符并退出
    close(epoll_fd);
    close(timer_fd);
}
